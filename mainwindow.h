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
#include "forgot.h"
#include "signup.h"

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

private:
    Ui::MainWindow *ui;
    forgot *forget;
    Signup *signup;
      mainpage *Mainpage1;
};
#endif // MAINWINDOW_H
