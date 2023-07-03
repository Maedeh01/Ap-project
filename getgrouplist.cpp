#include "getgrouplist.h"
#include "ui_getgrouplist.h"
#include "getuserlist.h"
#include "ui_getuserlist.h"
#include "creategroup.h"
#include "ui_creategroup.h"
#include "createchannel.h"
#include "ui_createchannel.h"
#include "mainwindow.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include<QDir>
#include<qfileinfo.h>
extern QString token;
extern QEventLoop eventLoop;//new
extern QNetworkAccessManager mgr;//new
getgrouplist::getgrouplist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::getgrouplist)
{
    ui->setupUi(this);
    setWindowTitle("getting group list");
    QString code,message;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkRequest req( QUrl( QString("http://api.barafardayebehtar.ml:8080/getgrouplist?token="+token) ) );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // blocks stack until "finished()" has been called=

    if (reply->error() == QNetworkReply::NoError) {

        QString strReply = (QString)reply->readAll();

        //parse json
        qDebug() << "Response:" << strReply;
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());

        QJsonObject jsonObj = jsonResponse.object();
        code = jsonObj["code"].toString();
        message = jsonObj["message"].toString();

        ui->label_group_list_message->setText(message);
         QString number_g="";
        for(int i=12;message[i]!='-';i++){
            number_g+=message[i];

        }
        int number;
        number=number_g.toInt();
QString p="";
number--;
 QString chat;
 while(number!=-1){
     QJsonValue val=jsonObj.value(QString("block "+QString::number(number)));
     QJsonObject item=val.toObject();
     QJsonValue subobj=item["group_name"];
      chat=subobj.toString();
      p+=chat+"\n";
     //qDebug()<<chat<<"\n";

     number--;

 }
 ui->label_group_list_chat->setText(p);


;

    }
    else {
        //failure

        qDebug() <<"Failure"<<reply->errorString();
        delete reply;
        //forget6 = new forgot(this, "creategroup","failure");
        //forget6->show();
        //forget6->exec();
        QString new_add="c:/main_file_Qt/groups/groupname.txt";
        QFile file2(new_add);
        file2.open(QFile::ReadOnly|QFile::Text);
        QTextStream in(&file2);
        QString line=in.readLine();
        ui->label_group_list_message->setText("failure");
        while(!line.isNull()){
            ui->label_group_list_chat->setText(line);
            line=in.readLine();
    }
}
}

getgrouplist::~getgrouplist()
{
    delete ui;
}
