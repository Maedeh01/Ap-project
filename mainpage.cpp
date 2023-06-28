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


void mainpage::on_actionJoin_2_triggered()
{
    hide();
    Join2 = new join(this,"Group");
    Join2->show();
    Join2->exec();
}


void mainpage::on_actionJoin_triggered()
{
    hide();
    Join2 = new join (this,"Channel");
    Join2->show();
    Join2->exec();
}

