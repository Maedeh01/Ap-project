#include "show_message.h"
#include "ui_show_message.h"

show_message::show_message(QWidget *parent,QString name,QString msgbox) :
    QDialog(parent),
    ui(new Ui::show_message)
{
    ui->setupUi(this);
    setWindowTitle("your message");
    ui->name->setText(name);
    ui->msg_box->setText(msgbox);
}

show_message::~show_message()
{
    delete ui;
}
