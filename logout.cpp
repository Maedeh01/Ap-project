#include "logout.h"
#include "ui_logout.h"
#include "mainwindow.h"
#include <QApplication>


extern QString username,password;
extern QNetworkAccessManager * manager;
extern QNetworkRequest request;

Logout::Logout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Logout)
{
    ui->setupUi(this);
}

Logout::~Logout()
{
    delete ui;
}

void Logout::on_logout_pushButton_clicked()
{
    username=ui->LO_username_lineEdit->text();
    password=ui->LO_password_lineEdit->text();

    request.setUrl(QUrl("http://api.barafardayebehtar.ml:8080/logout?username="+username+"&password="+password));

    QByteArray data = manager->get(request)->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();
    double code = jsonObj.value("code").toDouble();
    qDebug() << code;
    if( code == 200 ){
        // log out
        hide();
        //go to new mainwindow
    }
}

