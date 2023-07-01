#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QMainWindow>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include "forgot.h"
#include "signup.h"
#include "logout.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushbutton_forget_clicked();

    void on_pushButton_signup_clicked();

    void on_pushButton_login_clicked();

    void on_pushButton_Logout_clicked();

private:
    Ui::MainWindow *ui;
    forgot *forget;
    Signup *signup;
    mainpage *Mainpage1;
    Logout *logout_main;
};
#endif // MAINWINDOW_H
