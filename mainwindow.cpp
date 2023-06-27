#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "QNetworkAccessManager"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
QString username,firstname,lastname,password;

QNetworkAccessManager * manager;
QNetworkRequest request;
//QNetworkReply *reply = manage; // Send GET request

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager();
       QObject::connect(manager, &QNetworkAccessManager::finished,
           this, [=](QNetworkReply *reply) {
               if (reply->error()) {
                   qDebug() << reply->errorString();
                   return;
               }

               QString answer = reply->readAll();

               qDebug() << answer;
           }
       );
}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
}


void MainWindow::on_pushbutton_forget_clicked()
{
    hide();
    forget = new forgot(this,"forget your password?","Hahahahahahaha sooooorryyyyy!!!!!!");
    forget->show();
    forget->exec();
}


void MainWindow::on_pushButton_signup_clicked()
{
    hide();
    signup=new Signup(this);
    signup->show();
    signup->exec();
}


void MainWindow::on_pushButton_login_clicked()
{
    username=ui->LINEDIT_USERNAME->text();
    password=ui->linedit_password->text();
    request.setUrl(QUrl("http://api.barafardayebehtar.ml:8080/login?username="+username+"&password="+password));
    QByteArray data = manager->get(request)->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();
    double code = jsonObj.value("code").toDouble();
    qDebug() << code;
    if( code == 200 ){
        //go to list.
        hide();
      Mainpage1 = new mainpage(this);
        Mainpage1 ->show();
        //Mainpage1 ->exec();
    }
    else if (code==401){
        QString mass = jsonObj.value("message").toString();
        hide();
        forget = new forgot(this,"Error","The information you've entered is wrong!");
        forget->show();
        forget->exec();
    }
    else if (code==404){
        QString mass = jsonObj.value("message").toString();
        hide();
        forget = new forgot(this,"Error","This user was'nt found!");
        forget->show();
        forget->exec();
    }
}

