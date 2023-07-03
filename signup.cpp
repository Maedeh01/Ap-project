#include "signup.h"
#include "ui_signup.h"
#include "mainwindow.h"

extern QString username,firstname,lastname,password;
extern QEventLoop eventLoop;//new
extern QNetworkAccessManager mgr;//new

Signup::Signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Signup)
{
    ui->setupUi(this);
    setWindowTitle("signup");
}

Signup::~Signup()
{
    delete ui;
}
void Signup::on_pushButton_ok_Signup_clicked()
{
    QString code,message;
    firstname=ui->lineEdit_firstname->text();
    lastname=ui->lineEdit_lastname->text();
    username=ui->lineEdit_username->text();
    password=ui->lineEdit_password->text();
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkRequest req( QUrl( QString("http://api.barafardayebehtar.ml:8080/signup?username="+username+"&password="+password+"&firstname="+firstname+"&lastname="+lastname) ) );
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

    if( code == "200" ){
        //go to mainpage of mesenger
        hide();
        Mainpage = new mainpage(this);
        Mainpage ->show();
        //Mainpage ->exec();
    }
    else{
        hide();
        forget2 = new forgot(this,"Error",message);
        forget2->show();
        forget2->exec();
    }
}

