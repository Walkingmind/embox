#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QStringList>
#include <QDebug>
#include <QtGui>

/*!
 *Makes class LoginDialog a child to its parent, QDialog
 */
class LoginDialog : public QDialog
{
/*!
 *Turns Login Dialog into a QObject
 */
    Q_OBJECT

private:
    /*!
      * A label for the username component.
      */
    QLabel* labelUsername;

    /*!
      * A label for the password.
      */
    QLabel* labelPassword;

    /*!
      * An editable combo box for allowing the user
      * to enter his username or select it from a list.
      */
    QComboBox* comboUsername;

    /*!
      * A field to let the user enters his password.
      */
    QLineEdit* editPassword;

    /*!
      * The standard dialog button box.
      */
    QDialogButtonBox* buttons;

    /*!
      * A method to set up all dialog components and
      * initialize them.
      */
    void setUpGUI();

public:
    explicit LoginDialog(QWidget *parent = 0);

    /*!
      * Sets the proposed username, that can come for instance
      * from a shared setting.
      *\param username the string that represents the current username
      * to display
      */
    void setUsername( QString& username );

    /*!
      * Sets the current password to propose to the user for the login.
      * \param password the password to fill into the dialog form
      */
    void setPassword( QString& password );

    /*!
      * Sets a list of allowed usernames from which the user
      * can pick one if he does not want to directly edit it.
      *\param usernames a list of usernames
      */
    void setUsernamesList( const QStringList& usernames );

    QMdiSubWindow *subwindow;

signals:

    /*!
      * A signal emitted when the login is performed.
      * \param username the username entered in the dialog
      * \param password the password entered in the dialog
      * \param index the number of the username selected in the combobox
      */
    void acceptLogin( QString& username, QString& password, int& indexNumber );

public slots:
    /*!
      * A lot to adjust the emitting of the signal.
      */
    void slotAcceptLogin();
};
