#include "join.h"
#include "ui_join.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>

extern QString username,password,token,dst;
extern QEventLoop eventLoop;//new
extern QNetworkAccessManager mgr;//new
extern QString code,message,body,src;

join::join(QWidget *parent, QString lable) :
    QDialog(parent),
    ui(new Ui::join)
{
    ui->setupUi(this);

    ui->label_group_or_channel->setText(lable);
    type = lable;
}

join::~join()
{
    delete ui;
}

void join::on_pushButton_join_clicked()
{
    QString code,message;
    if( type == "Group"){
        QString name_group = ui->lineEdit_name_to_join->text();
        QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
        QNetworkRequest req( QUrl( QString("http://api.barafardayebehtar.ml:8080/joingroup?token=" +token +"&group_name="+name_group) ) );
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
        if ( code == "200"){
            QFile file("c:/main_file_Qt/groups/"+ name_group);
        }
        hide();
        forget3 = new forgot(this, "Join",message);
        forget3->show();
        forget3->exec();
        hide();
    }
   else if( type == "Channel"){
        QString name_channel = ui->lineEdit_name_to_join->text();
        QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
        QNetworkRequest req( QUrl( QString("http://api.barafardayebehtar.ml:8080/joinchannel?token=" + token + "&channel_name="+ name_channel) ) );
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
        }
        else {
            //failure
            qDebug() << "Failure" <<reply->errorString();
        }
        if ( code == "200"){
            QFile file("c:/main_file_Qt/channels/"+ name_channel);
        }
        hide();
        forget3 = new forgot(this, "Join",message);
        forget3->show();
        forget3->exec();
        hide();
    }

        //show channel messages
        else if(type=="Channel name:"){

            dst=ui->lineEdit_name_to_join->text();
            QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
            QNetworkRequest req( QUrl( QString("http://api.barafardayebehtar.ml:8080/getchannelchats?token="+token+"&dst="+dst) ) );
            QNetworkReply *reply = mgr.get(req);
            eventLoop.exec(); // blocks stack until "finished()" has been called

            if (reply->error() == QNetworkReply::NoError) {

                QString strReply = (QString)reply->readAll();

                //parse json
                qDebug() << "Response:" << strReply;
                QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());

                QJsonObject jsonObj = jsonResponse.object();
                code= jsonObj["code"].toString();
                message= jsonObj["message"].toString();
                body=jsonObj["body"].toString();
                src=jsonObj["src"].toString();

            }
            else if (reply->errorString()=="Host api.barafardayebehtar.ml not found") {
                //ofline mode
                qDebug() <<" You are offline!";
                QFile file("c:/main_file_Qt/channels/"+dst);
                if (file.open(QFile::ReadOnly|QFile::Text)){
                    body=file.readAll();
                    ///////////////////////////////////////////////////////////////////should have a loop
                    hide();
                    msg=new show_message(this,"Channel "+dst,src+"\n"+body);
                    msg->show();
                    msg->exec();
                }

            }
            else {
                //failure
                qDebug() << "Failure" <<reply->errorString();
                delete reply;
            }
            if( code == "200" ){
                hide();
                msg=new show_message(this,"Channel "+dst,src+"\n"+body);
                msg->show();
                msg->exec();

            }
            othercodes(code,message);
        }

   //}
    //show group messege
      else if(type=="Group name:"){
        dst=ui->lineEdit_name_to_join->text();
        QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
        QNetworkRequest req( QUrl( QString("http://api.barafardayebehtar.ml:8080/getgroupchats?token="+token+"&dst="+dst) ) );
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
            body=jsonObj["body"].toString();
            src=jsonObj["src"].toString();
        }
        else if (reply->errorString()=="Host api.barafardayebehtar.ml not found") {
            //ofline mode
            qDebug() <<" You are offline!";
            QFile file("c:/main_file_Qt/groups/"+dst);
            if (file.open(QFile::ReadOnly|QFile::Text)){
                body=file.readAll();
                hide();
                msg=new show_message(this,"Group "+dst,src+"\n"+body);
                msg->show();
                msg->exec();
            }}
            else {
                //failure
                qDebug() << "Failure" <<reply->errorString();
                delete reply;
            }
            if( code == "200" ){
                hide();
                msg=new show_message(this,"Group "+dst,src+"\n"+body);
                msg->show();
                msg->exec();
                ///////////////////////////////////////////
            }
            othercodes(code,message);

    }

    //show contact message
    else if (type=="Cotact name:"){

        dst=ui->lineEdit_name_to_join->text();
        QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
        QNetworkRequest req( QUrl( QString("http://api.barafardayebehtar.ml:8080/getuserchats?token="+token+"&dst="+dst) ) );
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
            body=jsonObj["body"].toString();
            src=jsonObj["src"].toString();
        }
        else if (reply->errorString()=="Host api.barafardayebehtar.ml not found") {
            //ofline mode
            qDebug() <<" You are offline!";
            QFile file("c:/main_file_Qt/users/" + dst);
            if (file.open(QFile::ReadOnly|QFile::Text)){
                body=file.readAll();
                hide();
                msg=new show_message(this,"User "+dst,src+"\n"+body);
                msg->show();
                msg->exec();
            }
        }
        else {
            //failure
            qDebug() << "Failure" <<reply->errorString();
            delete reply;
        }
        if( code == "200" ){
            hide();
            msg=new show_message(this,"User "+dst,src+"\n"+body);
            msg->show();
            msg->exec();

        }
        othercodes(code,message);
    }
    }
