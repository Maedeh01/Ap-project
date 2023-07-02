#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QNetworkAccessManager"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

QDir G,C,U,main;
QString username,firstname,lastname,password,token,dst,date;
QEventLoop eventLoop;//new
QNetworkAccessManager mgr;//new

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    main.mkpath("c:/main_file_Qt");
    G.mkpath("c:/main_file_Qt/groups");
    C.mkpath("c:/main_file_Qt/channels");
    U.mkpath("c:/main_file_Qt/users");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushbutton_forget_clicked()
{
    hide();
    forget = new forgot(this,"/Forget your password?","Hahahahahahaha sooooorryyyyy!!!!!!");
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
    QString code,message;
    username=ui->LINEDIT_USERNAME->text();
    password=ui->linedit_password->text();
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkRequest req( QUrl( QString("http://api.barafardayebehtar.ml:8080/login?username="+username+"&password="+password) ) );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    if (reply->error() == QNetworkReply::NoError) {

        QString strReply = (QString)reply->readAll();

        //parse json
        qDebug() << "Response:" << strReply;
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());

        QJsonObject jsonObj = jsonResponse.object();
        code = jsonObj["code"].toString();
        message = jsonObj["message"].toString();
        token = jsonObj["token"].toString();
        qDebug() << "token:" << token;
        delete reply;
    }
    else if (reply->errorString()=="Host api.barafardayebehtar.ml not found") {
      //ofline mode
        qDebug() <<" You are offline!";
        //if user exists:
       {
            //go to list.
            hide();
            Mainpage1 = new mainpage(this);
            Mainpage1 ->show();
        }
    }
    else {
        //failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
    }

    if( code == "200" && username != "" ){
        //go to list.
        hide();
        Mainpage1 = new mainpage(this);
        Mainpage1 ->show();
        //Mainpage1 ->exec();
        timer = new QTimer();
        connect(timer,SIGNAL(timeout()),this,SLOT(update_user()));
        timer->start(5000);
    }
    else if (code == "200" && username == "" ){
       // hide();
        forget = new forgot(this,"Error","Enter your\nusername and password.");
        forget->show();
        forget->exec();
    }
    else if (code == "401" ){
        //hide();
        forget = new forgot(this,"Error",message);
        forget->show();
        forget->exec();
    }
    else if (code == "404" ){
       // hide();
        forget = new forgot(this,"Error",message);
        forget->show();
        forget->exec();
    }
    else if (code=="204"){
        //hide();
        forget = new forgot(this,"Error",message);
        forget->show();
        forget->exec();
    }

}
void MainWindow::on_pushButton_Logout_clicked()
{
    logout_main = new Logout(this,"Username:","Password:");
    logout_main->show();
    logout_main->exec();

}

void update_user(){
    QString code,message;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkRequest req( QUrl( QString("http://api.barafardayebehtar.ml:8080/getuserchats?token="+token+"&dst="+dst+"&date=20230701010101") ) );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // blocks stack until "finished()" has been called
    if (reply->error() == QNetworkReply::NoError) {

        QString strReply = (QString)reply->readAll();

        //parse json
        qDebug() << "Response:" << strReply;
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());

        QJsonObject jsonObj = jsonResponse.object();
        code = jsonObj["code"].toString();
        message = jsonObj["message"].toString();
        delete reply;
    }
    else {
        //failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
    }
}
