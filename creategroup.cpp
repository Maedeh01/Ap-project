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

extern QString username,firstname,lastname,password,token;
extern QEventLoop eventLoop;//new
extern QNetworkAccessManager mgr;//new
creategroup::creategroup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::creategroup)
{
    ui->setupUi(this);
}

creategroup::~creategroup()
{
    delete ui;
}

void creategroup::on_pushButton_create_group_clicked()
{
    QString group_name,group_title;
    int number_of_groups=0;
    group_name=ui->lineEdit_group_name->text();
    group_title=ui->lineEdit_group_title->text();
    QString code,message;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkRequest req( QUrl( QString("http://api.barafardayebehtar.ml:8080/creategroup?token="+token+"&group_name="+group_name+"&group_title="+group_title) ) );
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
        delete reply;
        forget6 = new forgot(this, "creategroup","failure");
        forget6->show();
        forget6->exec();
    }

if(code=="200"){
    number_of_groups++;
    QString address ="c:/main_file_Qt/groups/" + group_name + ".txt";
    QFile file(address);
    file.open(QIODevice::WriteOnly | QIODevice::Text |QIODevice::Append);
    QTextStream out(&file);

    file.close();
    QString new_add="c:/main_file_Qt/groups/groupname.txt";
    QFile file2(new_add);
    file2.open(QIODevice::WriteOnly | QIODevice::Text |QIODevice::Append);
    QTextStream out2(&file2);
    out2<<group_name<<"\n";
    file2.flush();
    file2.close();
}
    hide();
    forget6 = new forgot(this, "creategroup",message);
    forget6->show();
    forget6->exec();
    hide();
}

