
#include <QApplication>
#include <QTextEdit>
#include <QtGui>
#include <QTextCodec>
#include "mainwindow.h"
#include "login.h"
#include "desktopimage.h"
#include "mdi_background.h"

#include <kernel/manual_event.h>
#include <kernel/event.h>
#include <fcntl.h>
#include <framework/mod/options.h>
#include <module/third_party/qt/texteditor.h>

#define DEFAULT_WIDTH \
		OPTION_MODULE_GET(third_party__qt__texteditor, NUMBER, root_window_width)

#define DEFAULT_HEIGHT \
		OPTION_MODULE_GET(third_party__qt__texteditor, NUMBER, root_window_height)

#define FSIZE 64
#define SEP ':'

static QString defaultImagePath = ":/images/default.png";

QMdiAreaWBackground *emarea;
static DesktopImageDialog *wallpaperDialog;
static QStringList desktopImagesList;
static QApplication *__qt_app;
static QMenu *__qt_menu;

static struct manual_event inited_event;
static int curuid;

static void emboxQtShowLoginForm();

class EmboxRootWindow : public QMainWindow
{
    Q_OBJECT

    public:
	
	QAction *closeAllEditorsAction;
	EmboxRootWindow() {
	fileMenu = new QMenu(QString("&Пуск"), this);
	menuBar()->addMenu(fileMenu);

	__qt_menu = fileMenu;

	textEditorAction = new QAction(QString("&Текстовый редактор"), this);
	fileMenu->addAction(textEditorAction);
	connect(textEditorAction, SIGNAL(triggered()), this, SLOT(textEditorRun()));

	closeAllEditorsAction = new QAction(QString("&Закрыть все окна"), this);
	fileMenu->addAction(closeAllEditorsAction);
	connect(closeAllEditorsAction, SIGNAL(triggered()), this, SLOT(closeAllEditors()));

	logoutAction = new QAction(QString("&Завершение сеанса"), this);
	fileMenu->addAction(logoutAction);
	connect(logoutAction, SIGNAL(triggered()), this, SLOT(logout()));

	saveAction = new QAction(QString("&Сохранить конфигурацию"), this);
	fileMenu->addAction(saveAction);
	connect(saveAction, SIGNAL(triggered()), this, SLOT(savedefault()));

	wallpaperAction = new QAction(QString("&Графические настройки"), this);
	fileMenu->addAction(wallpaperAction);
	connect(wallpaperAction, SIGNAL(triggered()), this, SLOT(wallpaper()));
    }

    private slots:
	void textEditorRun() {
		TextEditor *textEditor = new TextEditor(emarea);
		textEditor->show();
	}

	void closeAllEditors() {
		TextEditor::closeAllEditors();
	}

	void logout() {
		emboxQtHideDesktop();
		emboxQtShowLoginForm();
	}

	void wallpaper() {
		wallpaperDialog = new DesktopImageDialog(desktopImagesList);
		wallpaperDialog->show();
	}

	void savedefault() {

	}

    private:
	QAction *logoutAction;
	QAction *textEditorAction;
	QAction *wallpaperAction;
	QAction *saveAction;
	QMenu *fileMenu;
};

static EmboxRootWindow *emroot;

static char *parse(char **buf) {
	char *ret = *buf;
	char *ch;

	if ((ch = strchr(*buf, SEP))) {
		*ch++ = '\0';
	}
	
	*buf = ch;

	return ret;
}

void emboxQtSetfont(const QString &fontFamily, int fontPt) {
	QFont serifFont(fontFamily, fontPt);
	__qt_app->setFont(serifFont);
	__qt_menu->setFont(serifFont);
}

static void load_pref(void) {
	int fd, ret;
	char cbuf[FSIZE];
	const char *wall = "default.png";
	const char *font = "Times";
	int font_pt = 10;

	snprintf(cbuf, FSIZE, "/mnt/pref_%d", curuid);
	fd = open(cbuf, O_RDONLY, 0755);

	if (fd == -1)
		goto set_default;

	lseek(fd, 0, 0);
	if (0 < (ret = read(fd, cbuf, FSIZE))) {
		char *buf = cbuf;

		buf[ret] = '\0';

		wall = parse(&buf);
		font = parse(&buf);
		font_pt = atoi(parse(&buf));
	}
	close(fd);

	QString imagePath = QString(":/images/").append(QString(wall));
	emarea->setBackgroundPath(imagePath);

	emboxQtSetfont(font, font_pt);

}

void emboxQtSavePref(char *wall, char *font, int font_pt) {
	int fd, len;
	char cbuf[FSIZE];
	
	snprintf(cbuf, FSIZE, "/mnt/pref_%d", curuid);

	fd = creat(cbuf, 0755);

	len = snprintf(cbuf, FSIZE, "%s:%s:%d", wall, font, font_pt);

	write(fd, cbuf, len);

	ftruncate(fd, len);

	close(fd);
}

void emboxQtShowDesktop(uid_t uid) {
	int fd = -1;
	bool enabled = uid ? false : true;

	curuid = uid;
	emroot->menuBar()->show();
	emroot->closeAllEditorsAction->setEnabled(enabled);

	load_pref();
}

void emboxQtHideDesktop() {
	emarea->closeAllSubWindows();
	emroot->menuBar()->hide();
}

void emboxRootWindowShow(int width, int height) {

	emroot->setGeometry(QRect(0,0, width, height));
	manual_event_set_and_notify(&inited_event);
}

static void emboxQtShowLoginForm() {
	LoginDialog *loginDialog = new LoginDialog(0, emarea);
	loginDialog->show();

	emarea->setBackgroundPath(defaultImagePath);
}

int main(int argv, char **args)
{
	//Q_INIT_RESOURCE(texteditor);

	manual_event_init(&inited_event, 0);

	QApplication app(argv, args);

	__qt_app = &app;

	QFont serifFont("Times", 10);
	app.setFont(serifFont);
	qDebug() << "Supported formats:" << QImageReader::supportedImageFormats();
	desktopImagesList << "cats.jpg" << "default.png" << "abstract.jpg";

	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

	emroot = new EmboxRootWindow();
	emarea = new QMdiAreaWBackground(defaultImagePath);

	emroot->setCentralWidget(emarea);

	if (DEFAULT_WIDTH == 0 || DEFAULT_HEIGHT == 0) {
		manual_event_wait(&inited_event, EVENT_TIMEOUT_INFINITE); /* EMBOXVC plugin*/
	} else {
		emroot->setGeometry(QRect(0,0, DEFAULT_WIDTH, DEFAULT_HEIGHT)); /* VNC plugin */
	}

	emroot->show();

	emboxQtHideDesktop();

	emboxQtShowLoginForm();

	return app.exec();
}

#include "main.moc"
