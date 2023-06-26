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
QNetworkAccessManager * manager;
QNetworkRequest request;
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
    forget = new forgot(this);
    forget->show();
    forget->exec();
}


void MainWindow::on_pushButton_signup_clicked()
{
    request.setUrl(QUrl("http://api.barafardayebehtar.ml:8080/signup?username=sara&password=1234&firstname=sara&lastname=baradaran"));
        manager->get(request);
}

