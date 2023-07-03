#include "forgot.h"
#include "ui_forgot.h"

forgot::forgot(QWidget *parent,QString titletext,QString massagetext) :
    QDialog(parent),
    ui(new Ui::forgot)
{
    ui->setupUi(this);
    setWindowTitle("forgot password");
    ui->label_title->setText(titletext);
    ui->label_massage->setText(massagetext);
}

forgot::~forgot()
{
    delete ui;
}
