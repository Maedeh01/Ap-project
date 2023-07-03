#include "logout.h"
#include "ui_logout.h"
#include "mainwindow.h"
#include <QApplication>


extern QString username,password,token,dst,date;
extern QEventLoop eventLoop;//new
extern QNetworkAccessManager mgr;//new
QString code,message,body,src;

Logout::Logout(QWidget *parent,QString ftxt,QString stxt) :
    QDialog(parent),
    ui(new Ui::Logout)
{
    ui->setupUi(this);
    ui->firstl_label->setText(ftxt);
    ui->second_label->setText(stxt);
    type=ftxt;
}

Logout::~Logout()
{
    delete ui;
}
void Logout::on_push_Button_clicked()
{

    //page for log out
    if(type=="Username:"){

        username=ui->first_lineEdit->text();
        password=ui->second_lineEdit->text();
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
        else if (code == "401" ){
            hide();
            warning = new forgot(this,"Error",message);
            warning->show();
            warning->exec();
        }
        else if (code == "404" ){
            hide();
            warning = new forgot(this,"Error",message);
            warning->show();
            warning->exec();
        }
        else if (code=="204"){
            hide();
            warning = new forgot(this,"Error",message);
            warning->show();
            warning->exec();
        }
    }
}



