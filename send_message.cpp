#include "send_message.h"
#include "ui_send_message.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

extern QString token;
extern QEventLoop eventLoop;//new
extern QNetworkAccessManager mgr;//new

Send_message::Send_message(QWidget *parent, QString t) :
    QDialog(parent),
    ui(new Ui::Send_message)
{
    ui->setupUi(this);
    type = t;
    ui->label_type_send->setText(t);
}

Send_message::~Send_message()
{
    delete ui;
}

void Send_message::on_pushButton_ok_send_clicked()
{
    QString code,message;
    QNetworkReply *reply;
    QString dst = ui->lineEdit_dst->text();
    QString body = ui->textEdit_body->toPlainText();
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    if(type == "user"){
        QNetworkRequest req( QUrl( QString("http://api.barafardayebehtar.ml:8080/sendmessageuser?token="+ token +"&dst="+dst +"&body="+ body) ) );
        reply = mgr.get(req);
    }
    else if (type == "group"){
        QNetworkRequest req( QUrl( QString("http://api.barafardayebehtar.ml:8080/sendmessagegroup?token=" + token +"&dst=" + dst +"&body="+ body) ) );
        reply = mgr.get(req);
    }
    else if (type == "channel"){
        QNetworkRequest req( QUrl( QString("http://api.barafardayebehtar.ml:8080/sendmessagechannel?token=" + token +"&dst=" + dst +"&body="+ body) ) );
        reply = mgr.get(req);
    }
//    QNetworkReply *reply = mgr.get(req);
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
    hide();
    forgot_send = new forgot(this,"send message user",message);
    forgot_send->show();
    forgot_send->exec();


}

