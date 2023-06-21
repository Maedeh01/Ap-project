#include "forgot.h"
#include "ui_forgot.h"

forgot::forgot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::forgot)
{
    ui->setupUi(this);
}

forgot::~forgot()
{
    delete ui;
}
