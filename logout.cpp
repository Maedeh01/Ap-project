#include "logout.h"
#include "ui_logout.h"
#include "mainwindow.h"
#include <QApplication>


extern QString username,password,token;
extern QEventLoop eventLoop;//new
extern QNetworkAccessManager mgr;//new

Logout::Logout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Logout)
{
    ui->setupUi(this);
}

Logout::~Logout()
{
    delete ui;
}
void Logout::on_logout_pushButton_clicked()
{
    QString code,message;
    username=ui->LO_username_lineEdit->text();
    password=ui->LO_password_lineEdit->text();
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkRequest req( QUrl( QString("http://api.barafardayebehtar.ml:8080/logout?username="+username+"&password="+password) ) );
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
        token = nullptr;
        delete reply;
        hide();
        Forgot = new forgot(this,"Logout",message);
        Forgot->show();
        Forgot->exec();
    }
    else {
        //failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
    }
    if( code == "200" ){
        // log out
        hide();
        //go to new mainwindow
    }
}

