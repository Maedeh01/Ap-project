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
//        connect(timer,SIGNAL(timeout()),this,SLOT(update()));
//        timer->start(5000);
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

//void update(){
//    if (type=="Cotact name:"){

//        dst=ui->lineEdit_name_to_join->text();
//        QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
//        QNetworkRequest req( QUrl( QString("http://api.barafardayebehtar.ml:8080/getuserchats?token="+token+"&dst="+dst) ) );
//        QNetworkReply *reply = mgr.get(req);
//        eventLoop.exec(); // blocks stack until "finished()" has been called

//        if (reply->error() == QNetworkReply::NoError) {

//            QString strReply = (QString)reply->readAll();

//            //parse json
//            qDebug() << "Response:" << strReply;
//            QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());

//            QJsonObject jsonObj = jsonResponse.object();
//            code = jsonObj["code"].toString();
//            message = jsonObj["message"].toString();
//            body=jsonObj["body"].toString();
//            src=jsonObj["src"].toString();
//            QString number_g;
//            for(int i=11;message[i]!='-';i++){


//                number_g+=message[i];

//            }
//            int number;
//            number=number_g.toInt();
//            number--;
//            QString p="";

//            while(number!=-1){
//                QJsonValue val=jsonObj.value(QString("block "+QString::number(number)));
//                QJsonObject item=val.toObject();
//                QJsonValue subobj=item["src"];
//                QString src=subobj.toString();
//                QJsonValue subobj_b=item["body"];
//                QJsonValue subobj_ds=item["dst"];
//                QJsonValue subobj_da=item["date"];
//                QString dst2=subobj_ds.toString();
//                QString body=subobj_b.toString();
//                QString date=subobj_da.toString();
//                p+=dst2+":"+body+"\n"+"in date"+"\n"+date+"\n";
//                number--;
//            }
//            msg=new show_message(this,message,p);
//            msg->show();
//            msg->exec();
//        }
//}
