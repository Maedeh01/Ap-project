#include "signup.h"
#include "ui_signup.h"
#include "mainwindow.h"

extern QString username,firstname,lastname,password;
extern QNetworkAccessManager * manager;
extern QNetworkRequest request;
Signup::Signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Signup)
{
    ui->setupUi(this);
}

Signup::~Signup()
{
    delete ui;
}

void Signup::on_pushButton_ok_Signup_clicked()
{
    firstname=ui->lineEdit_firstname->text();
    lastname=ui->lineEdit_lastname->text();
    username=ui->lineEdit_username->text();
    password=ui->lineEdit_password->text();
    request.setUrl(QUrl("http://api.barafardayebehtar.ml:8080/signup?username="
                        +username+"&password="+password+"&firstname="+firstname+"&lastname="+lastname));
    QByteArray data = manager->get(request)->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();
    double code = jsonObj.value("code").toDouble();
    qDebug() << code;
    if( code == 200 ){
        //go to mainpage of mesenger
        hide();
        Mainpage = new mainpage(this);
        Mainpage ->show();
        //Mainpage ->exec();
    }
    else{
        QString mass = jsonObj.value("message").toString();
        hide();
        forget2 = new forgot(this,"Error","User Exist Try Another!");
        forget2->show();
        forget2->exec();
    }
}

