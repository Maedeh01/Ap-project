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

extern QString username,firstname,lastname,password,token;
extern QNetworkAccessManager * manager;
extern QNetworkRequest request;

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
    if( type == "Group"){
    QString name_group = ui->lineEdit_name_to_join->text();
    request.setUrl(QUrl("http://api.barafardayebehtar.ml:8080/joingroup?token="+ token +"&group_name="+name_group));
    QByteArray data = manager->get(request)->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();
    double code = jsonObj.value("code").toDouble();
    QString massage = jsonObj.value("massage").toString();
    hide();
    forget3 = new forgot(this, "Join",massage);
    forget3->show();
    forget3->exec();
    hide();
    }
    if( type == "Channel"){
    QString name_channel = ui->lineEdit_name_to_join->text();
    request.setUrl(QUrl("http://api.barafardayebehtar.ml:8080/joinchannel?token=" + token + "&channel_name="+ name_channel));
    QByteArray data = manager->get(request)->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();
    double code = jsonObj.value("code").toDouble();
    QString massage = jsonObj.value("massage").toString();
    hide();
    forget3 = new forgot(this, "Join",massage);
    forget3->show();
    forget3->exec();
    hide();
    }
}

