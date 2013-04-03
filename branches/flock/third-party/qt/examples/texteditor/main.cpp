#include <QApplication>
#include <QTextEdit>
#include <QtGui>
#include <QTextCodec>
#include "mainwindow.h"

QGraphicsView *emboxView;
TextEditor *textEditor;
QGraphicsScene *emscene;

class Button : public QWidget
{
    Q_OBJECT
public:
    Button(const QPixmap &pixmap)
        : QWidget(), _pix(pixmap)
    {
	//setAcceptHoverEvents(true);
	//setCacheMode(DeviceCoordinateCache);
    }

    QRectF boundingRect() const
    {
	int w = _pix.width();
	int h = _pix.height();
	return QRectF(0, 0, w + 10, h + 10);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
    {
        bool down = option->state & QStyle::State_Sunken;
	int w = _pix.width();
	int h = _pix.height();
	painter->drawPixmap(0, 0, _pix);
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *)
    {
       // update();
        //emscene->addWidget(textEditor, textEditor->windowType());
        textEditor->show();
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *)
    {
	update();
    }
private:
    QPixmap _pix;
};

QMdiArea *emarea;
QMainWindow *win;

int main(int argv, char **args)
{
    //Q_INIT_RESOURCE(texteditor);

    QApplication app(argv, args);

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    emscene = new QGraphicsScene(0, 0, 1024, 768);

    QImage desktopImage = QImage(":/default.png").convertToFormat(QImage::Format_RGB16);
    QPixmap bgPix = QPixmap::fromImage(desktopImage);
    //emboxView = new QGraphicsView(emscene);
    //emboxView->setBackgroundBrush(bgPix);
    //emboxView->resize(1024, 768);

    //Button *texteditorButton = new Button(QPixmap(":/icon.png"));
    //texteditorButton->resize(128,128);

    //emscene->addItem(texteditorButton);
    //texteditorButton->setPos(64, 64);

    //emboxView->show();
    textEditor = new TextEditor();

    //win = new QMainWindow();

    //QWidget *w = new QWidget(win);
    //QPushButton *p = new QPushButton("New Sub-window", win);
    //area = new QMdiArea(win);

    //QVBoxLayout *l = new QVBoxLayout(w);
    //l->addWidget(p);
    //l->addWidget(area);
    //w->setLayout(l);
    //win->setCentralWidget(w);


    emarea = new QMdiArea();
    emarea->setBackground(bgPix);
    emarea->resize(1024, 768);
    //area->addSubWindow(emboxView, emboxView->windowType());
    emarea->addSubWindow(textEditor, textEditor->windowType());
    emarea->show();

    return app.exec();
}

#include "main.moc"
