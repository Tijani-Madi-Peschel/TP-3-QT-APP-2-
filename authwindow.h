#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <QWidget>

class QLineEdit;
class QCheckBox;
class QPushButton;
class QLabel;

class AuthWindow : public QWidget {
    Q_OBJECT

public:
    AuthWindow(QWidget *parent = nullptr);

private slots:
    void checkCredentials();
    void toggleIdVisibility(bool checked);
    void togglePasswordVisibility(bool checked);

private:
    QLineEdit *idLineEdit;
    QLineEdit *passwordLineEdit;
    QCheckBox *showIdCheckBox;
    QCheckBox *showPasswordCheckBox;
    QPushButton *loginButton;
    QLabel *statusLabel;
    int attempts;

    const QString correctId = "123456789";
    const QString correctPassword = "tijanimadi";
};

#endif // AUTHWINDOW_H
