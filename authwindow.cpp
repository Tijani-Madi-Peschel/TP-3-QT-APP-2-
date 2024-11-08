#include "authwindow.h"
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

AuthWindow::AuthWindow(QWidget *parent)
    : QWidget(parent), attempts(0) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    idLineEdit = new QLineEdit(this);
    idLineEdit->setPlaceholderText("Identifiant (9 chiffres)");
    idLineEdit->setMaxLength(9);

    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setPlaceholderText("Mot de passe");
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    showIdCheckBox = new QCheckBox("Afficher l'Identifiant", this);
    showPasswordCheckBox = new QCheckBox("Afficher le Mot de passe", this);

    loginButton = new QPushButton("Connexion", this);
    statusLabel = new QLabel(this);

    QHBoxLayout *idLayout = new QHBoxLayout;
    idLayout->addWidget(idLineEdit);
    idLayout->addWidget(showIdCheckBox);

    QHBoxLayout *passwordLayout = new QHBoxLayout;
    passwordLayout->addWidget(passwordLineEdit);
    passwordLayout->addWidget(showPasswordCheckBox);

    mainLayout->addLayout(idLayout);
    mainLayout->addLayout(passwordLayout);
    mainLayout->addWidget(loginButton);
    mainLayout->addWidget(statusLabel);

    connect(showIdCheckBox, &QCheckBox::toggled, this, &AuthWindow::toggleIdVisibility);
    connect(showPasswordCheckBox, &QCheckBox::toggled, this, &AuthWindow::togglePasswordVisibility);
    connect(loginButton, &QPushButton::clicked, this, &AuthWindow::checkCredentials);
}

void AuthWindow::toggleIdVisibility(bool checked) {
    idLineEdit->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
}

void AuthWindow::togglePasswordVisibility(bool checked) {
    passwordLineEdit->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
}

void AuthWindow::checkCredentials() {
    QString id = idLineEdit->text();
    QString password = passwordLineEdit->text();

    if (id.length() != 9 || id != correctId) {
        statusLabel->setText("Identifiant incorrect.");
        return;
    }

    if (password == correctPassword) {
        statusLabel->setText("Authentification réussie!");
        loginButton->setStyleSheet("background-color: green");
    } else {
        attempts++;
        statusLabel->setText(QString("Mot de passe incorrect. Tentatives restantes: %1").arg(3 - attempts));
        loginButton->setStyleSheet("background-color: red");

        if (attempts >= 3) {
            close();
        }
    }
}
