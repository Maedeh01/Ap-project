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
getuserlist::getuserlist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::getuserlist)
{
    ui->setupUi(this);
    QString code,message;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkRequest req( QUrl( QString("http://api.barafardayebehtar.ml:8080/getuserlist?token="+token) ) );
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
       ui->label_user_list_message->setText(message);
        QString number_g;
       for(int i=13;message[i]!='-';i++){


               number_g+=message[i];

       }
       int number;
       number=number_g.toInt();

while(number!=0){
    QJsonValue val=jsonObj.value(QString("block"+QString::number(number)));
    QJsonObject item=val.toObject();
    QJsonValue subobj=item["src"];
    QString chat=subobj.toString();
     ui->label_user_list_chat->setText(chat);
    number--;
}






    }
    else {
        //failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;

        QString new_add="c:/main_file_Qt/users/list.txt";
        QFile file2(new_add);
        file2.open(QFile::ReadOnly|QFile::Text);
        QTextStream in(&file2);
        QString line=in.readLine();
        ui->label_user_list_message->setText("failure");
        while(!line.isNull()){
            ui->label_user_list_chat->setText(line);
            line=in.readLine();
    }
}

}

getuserlist::~getuserlist()
{
    delete ui;
}




