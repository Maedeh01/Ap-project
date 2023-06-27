#include "mainpage.h"
#include "ui_mainpage.h"

mainpage::mainpage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainpage)
{
    ui->setupUi(this);
}

mainpage::~mainpage()
{
    delete ui;
}

void mainpage::on_actionLogout_triggered()
{
    hide();
    logout = new Logout(this);
    logout ->show();
    logout->exec();
}

