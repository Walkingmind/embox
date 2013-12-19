#include "emboxvcwindowsurface.h"
#include <QtCore/qdebug.h>
#include <QtGui/private/qapplication_p.h>
#include <QWindowSystemInterface>
#include <QMouseEvent>
#include <kernel/event.h>
#include <util/ring_buff.h>
#include <assert.h>

QT_BEGIN_NAMESPACE

#define MOUSE_EVENT_BUFFER_SIZE 4096
#define KBD_EVENT_BUFFER_SIZE   4096

/* From VNC */
static const struct {
    int keysym;
    int keycode;
} emboxKeyMap[] = {
    { 0x08, Qt::Key_Backspace },
    { 0x09, Qt::Key_Tab       },
    { 0x0d, Qt::Key_Return    },
    { 0x1b, Qt::Key_Escape    },
    { 0x63, Qt::Key_Insert    },
    { 0xff, Qt::Key_Delete    },
    { 0x50, Qt::Key_Home      },
    { 0x57, Qt::Key_End       },
    { 0x55, Qt::Key_PageUp    },
    { 0x56, Qt::Key_PageDown  },
    { 0x51, Qt::Key_Left      },
    { 0x52, Qt::Key_Up        },
    { 0x53, Qt::Key_Right     },
    { 0x54, Qt::Key_Down      },
    { 0xbe, Qt::Key_F1        },
    { 0xbf, Qt::Key_F2        },
    { 0xc0, Qt::Key_F3        },
    { 0xc1, Qt::Key_F4        },
    { 0xc2, Qt::Key_F5        },
    { 0xc3, Qt::Key_F6        },
    { 0xc4, Qt::Key_F7        },
    { 0xc5, Qt::Key_F8        },
    { 0xc6, Qt::Key_F9        },
    { 0xc7, Qt::Key_F10       },
    { 0xc8, Qt::Key_F11       },
    { 0xc9, Qt::Key_F12       },
    { 0xe1, Qt::Key_Shift     },
    { 0xe2, Qt::Key_Shift     },
    { 0xe3, Qt::Key_Control   },
    { 0xe4, Qt::Key_Control   },
    { 0xe7, Qt::Key_Meta      },
    { 0xe8, Qt::Key_Meta      },
    { 0xe9, Qt::Key_Alt       },
    { 0xea, Qt::Key_Alt       },
    { 0, 0 }
};

static QList<QEmboxVCWindowSurface*> __emboxVCcollection;
extern QEmboxVC *globalEmboxVC;
extern void emboxRootWindowShow(int width, int height);

static void flushAll() {
	QRegion region;
	QPoint point;

	for (int i = 0; i < __emboxVCcollection.size(); ++i) {
		__emboxVCcollection.at(i)->flush(0, region, point);
	}
}

static void __emboxVCsetMode(struct vc *vc, int mode) {
	globalEmboxVC->emboxVCvisualized = mode;
}

static void __visualization(struct vc *vc, struct fb_info *info) {
	Q_UNUSED(info);
	const struct fb_var_screeninfo *vinfo = fb_get_var(info);

	QEmboxVCWindowSurface *surf;

	emboxRootWindowShow(vinfo->xres, vinfo->yres);

	__emboxVCsetMode(vc, 1);

	flushAll();

	foreach (QWidget *widget, QApplication::allWidgets()) {
		widget->update();
	}
}

QEmboxVCMouseHandler::QEmboxVCMouseHandler() {
	void *buff, *storage;

	storage = malloc(MOUSE_EVENT_BUFFER_SIZE);
	assert(storage);

	buff = malloc(sizeof(struct ring_buff));
	assert(buff);

    ring_buff_init(buff, 1, MOUSE_EVENT_BUFFER_SIZE, storage);
    ring_buff = buff;

	event_init(&new_data, "mouse_data");

	readDataLoop();
}

QEmboxVCMouseHandler::~QEmboxVCMouseHandler() {
	struct ring_buff *rbuff = (struct ring_buff *) ring_buff;
	free(rbuff->storage);
	free(rbuff);
}

void QEmboxVCMouseHandler::storeData(void *data, int datalen) {
	ring_buff_enqueue(ring_buff, data, datalen);
}

void QEmboxVCMouseHandler::activate() {
	event_notify(&new_data);
}

void *readMouseDataThread(void *arg) {
	(void) arg;

	struct vc *vc;
	struct input_event ev;
	short x, y;
	int bstate;
	QEmboxVC *emvc;
	QEmboxVCMouseHandler *mh = (QEmboxVCMouseHandler *)arg;

	while (EVENT_WAIT(&mh->new_data,
			ring_buff_dequeue(mh->ring_buff, &vc, sizeof(struct vc *)) > 0, SCHED_TIMEOUT_INFINITE) == 0) {

		ring_buff_dequeue(mh->ring_buff, &ev, sizeof(struct input_event));

		emvc = globalEmboxVC;

		bstate = Qt::NoButton;

		if (ev.type & 1) {
			bstate = Qt::LeftButton;
		} else if (ev.type & 2) {
			bstate = Qt::RightButton;
		}

		x = ev.value >> 16;
		y = ev.value & 0xffff;

		emvc->mouseX += x;
		emvc->mouseY += -y;

		int xres = emvc->emboxVC.fb->var.xres;
		int yres = emvc->emboxVC.fb->var.yres;

		emvc->mouseX = emvc->mouseX > 0 ? emvc->mouseX : 0;
		emvc->mouseY = emvc->mouseY > 0 ? emvc->mouseY : 0;

		emvc->mouseX = emvc->mouseX > xres ? xres : emvc->mouseX;
		emvc->mouseY = emvc->mouseY > yres ? yres : emvc->mouseY;

		QWindowSystemInterface::handleMouseEvent(0, QPoint(emvc->mouseX, emvc->mouseY),
				QPoint(emvc->mouseX, emvc->mouseY), Qt::MouseButtons(bstate));

		if (!emvc->emboxVC.fb || !emvc->emboxVCvisualized) {
			assert(0);
			return NULL;
		}

		emvc->cursor->emboxCursorRedraw(emvc->emboxVC.fb, emvc->mouseX, emvc->mouseY);
	}

	assert(0);
	return NULL;
}

void QEmboxVCMouseHandler::readDataLoop() {
	thread_create(0, readMouseDataThread, this);
}

QEmboxVCKeyboardHandler::QEmboxVCKeyboardHandler() {
	void *buff, *storage;

	storage = malloc(KBD_EVENT_BUFFER_SIZE);
	assert(storage);

	buff = malloc(sizeof(struct ring_buff));
	assert(buff);

    ring_buff_init(buff, 1, KBD_EVENT_BUFFER_SIZE, storage);

    ring_buff = buff;

	event_init(&new_data, "kbd_data");

	readDataLoop();
}

QEmboxVCKeyboardHandler::~QEmboxVCKeyboardHandler() {
	struct ring_buff *rbuff = (struct ring_buff *) ring_buff;
	free(rbuff->storage);
	free(rbuff);
}

void QEmboxVCKeyboardHandler::storeData(void *data, int datalen) {
	ring_buff_enqueue(ring_buff, data, datalen);
}

void QEmboxVCKeyboardHandler::activate() {
	event_notify(&new_data);
}

void *readKbdThread(void *arg) {
	(void) arg;

	struct vc *vc;
	struct input_event ev;
	QEmboxVCKeyboardHandler *kh = (QEmboxVCKeyboardHandler *)arg;

	while (EVENT_WAIT(&kh->new_data,
			ring_buff_dequeue(kh->ring_buff, &vc, sizeof(struct vc *)) > 0, SCHED_TIMEOUT_INFINITE) == 0) {
		QEvent::Type type;
		unsigned char ascii[4];
		int key;
		int i = 0;
		Qt::KeyboardModifiers modifier = 0;

		ring_buff_dequeue(kh->ring_buff, &ev, sizeof(struct input_event));

		type = ev.type & KEY_PRESSED ? QEvent::KeyPress : QEvent::KeyRelease;

		if (ev.value & SHIFT_PRESSED) {
			modifier = Qt::ShiftModifier;
		} else if (ev.value & ALT_PRESSED) {
			modifier = Qt::AltModifier;
		} else if (ev.value & CTRL_PRESSED) {
			modifier = Qt::ControlModifier;
		}

		int len = keymap_to_ascii(&ev, ascii);

		while (emboxKeyMap[i].keysym != 0) {
			if (emboxKeyMap[i].keysym == ascii[i]) {
				key = emboxKeyMap[i].keycode;
				break;
			}
			i++;
		}

		QWindowSystemInterface::handleKeyEvent(0, type, key, modifier, QString(QChar(ascii[0])));
	}

	assert(0);
	return NULL;
}

void QEmboxVCKeyboardHandler::readDataLoop() {
	thread_create(0, readKbdThread, this);
}

static void __handle_input_event(struct vc *vc, struct input_event *ev) {
	QEmboxVC *emvc = globalEmboxVC;

	if (ev->devtype == INPUT_DEV_MOUSE) {
		emvc->mouseHandler->storeData(&vc, sizeof(struct vc *));
		emvc->mouseHandler->storeData(ev, sizeof(struct input_event));
		emvc->mouseHandler->activate();
	} else if (ev->devtype == INPUT_DEV_KBD) {
		emvc->keyboardHandler->storeData(&vc, sizeof(struct vc *));
		emvc->keyboardHandler->storeData(ev, sizeof(struct input_event));
		emvc->keyboardHandler->activate();
	}
}

static void __scheduleDevisualization(struct vc *vc) {
	printf(">>__scheduleDevisualization\n");
	__emboxVCsetMode(vc, 0);

	mpx_devisualized(vc);
}

QEmboxVC::QEmboxVC()
    : emboxVCvisualized(0), mouseX(0), mouseY(0)
{
	cursor = new QEmboxCursor();

	mouseHandler = new QEmboxVCMouseHandler();
	keyboardHandler = new QEmboxVCKeyboardHandler();

	emboxVCcallbacks.visualized = __visualization;
	emboxVCcallbacks.schedule_devisualization = __scheduleDevisualization;
	emboxVCcallbacks.handle_input_event = __handle_input_event;

	emboxVC.callbacks = &emboxVCcallbacks;
	emboxVC.name = "emboxvc";

	mpx_register_vc(&emboxVC);
}

QEmboxVC::~QEmboxVC() {
}

QEmboxVCWindowSurface::QEmboxVCWindowSurface(QWidget *window)
    : QWindowSurface(window)
{
	mImage = QImage(QSize(window->width(), window->height()), QImage::Format_RGB16);

	vc = globalEmboxVC;

	__emboxVCcollection.append(this);
}

QEmboxVCWindowSurface::~QEmboxVCWindowSurface()
{
	__emboxVCcollection.removeAll(this);
}

QPaintDevice *QEmboxVCWindowSurface::paintDevice()
{
    return &mImage;
}

void QEmboxVCWindowSurface::flush(QWidget *widget, const QRegion &region, const QPoint &offset)
{
    Q_UNUSED(region);
    Q_UNUSED(offset);

    int i, shift;

    int x = widget->pos().x();
    int y = widget->pos().y();
    int width = widget->width();
    int height = widget->height();

    if (!vc->emboxVC.fb || !vc->emboxVCvisualized) {
    	return;
    }

    int bpp = vc->emboxVC.fb->var.bits_per_pixel / 8;
    char *begin = vc->emboxVC.fb->screen_base + (y * vc->emboxVC.fb->var.xres + x) * bpp;

    /* Draw image */
    for (i = 0, shift = 0; i < mImage.height(); i++ , shift += vc->emboxVC.fb->var.xres * bpp) {
    	memcpy(begin + shift, (const void *)mImage.constScanLine(i), mImage.bytesPerLine());
    }

    /* Reset cursor on new image and redraw */
    vc->cursor->emboxCursorReset(vc->emboxVC.fb);
    vc->cursor->emboxCursorRedraw(vc->emboxVC.fb, vc->mouseX, vc->mouseY);
}

void QEmboxVCWindowSurface::resize(const QSize &size)
{
    //qDebug() << "QMinimalWindowSurface::setGeometry:" << (long)this << rect;
    //base resize below somehow prevent wallpaper flush. Have no idea how.
    //QWindowSurface::resize(size);
    if (mImage.size() != size)
	mImage = QImage(size, QImage::Format_RGB16);
}

QEmboxVCPlatformWindow::QEmboxVCPlatformWindow(QWidget *widget)
: QPlatformWindow(widget)
{
}

QEmboxVCPlatformWindow::~QEmboxVCPlatformWindow()
{
}

WId QEmboxVCPlatformWindow::winId() const {
	return WId(1);
}

void QEmboxVCPlatformWindow::setParent(const QPlatformWindow *window) {
	//if (widget() && window->widget()) {
	//	widget()->setParent(window->widget());
	//}
}

void QEmboxVCPlatformWindow::setGeometry(const QRect &rect) {

    QWindowSystemInterface::handleGeometryChange(this->widget(), rect);
    QPlatformWindow::setGeometry(rect);

}
QT_END_NAMESPACE