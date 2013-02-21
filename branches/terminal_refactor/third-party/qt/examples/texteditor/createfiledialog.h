#ifndef CREATEFILEDIALOG_H
#define CREATEFILEDIALOG_H

#include <QtGui>

class CreateFileDialog : public QWidget
{
    Q_OBJECT
public:
    explicit CreateFileDialog(QTextEdit *textEdit, QString *fileName, QMainWindow *mainWindow);
    
private slots:
    void createFile();

private:
    QPushButton *createButton(const QString &text, const char *member);

    QLineEdit *fileNameEdit;

    QLabel *fileNameLabel;

    QPushButton *okButton;
    QPushButton *cancelButton;
    QDir currentDir;
    QTextEdit *textEdit;
    QString *fileName;
    QMainWindow *mainWindow;
};

#endif // CREATEFILEDIALOG_H
