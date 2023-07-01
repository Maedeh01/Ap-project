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
}

getuserlist::~getuserlist()
{
    delete ui;
}

void getuserlist::on_pushButton_show_userlist_clicked()
{
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
         QString chat=jsonObj["src"].toString();

       ui->label->setText(message);
       ui->label_user_2->setText(chat);
forget6=new forgot(this,message,chat);
forget6->show();
forget6->exec();

    }
    else {
        //failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
        forget6 = new forgot(this, "creategroup","failure");
        forget6->show();
        forget6->exec();
    }
    hide();


}

