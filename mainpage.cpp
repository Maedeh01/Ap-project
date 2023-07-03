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
    //hide();
    logout = new Logout(this,"Username:","Password:");
    logout ->show();
    logout->exec();
}


void mainpage::on_actionJoin_2_triggered()
{
   // hide();
    Join2 = new join(this,"Group");
    Join2->show();
    Join2->exec();
}


void mainpage::on_actionJoin_triggered()
{
    //hide();
    Join2 = new join (this,"Channel");
    Join2->show();
    Join2->exec();
}


void mainpage::on_actionContacts_send_triggered()
{
    //hide();
    send_message = new Send_message(this,"user");
    send_message->show();
    send_message->exec();
}


void mainpage::on_actionSend_message_triggered()
{
   // hide();
    send_message = new Send_message(this,"channel");
    send_message->show();
    send_message->exec();
}


void mainpage::on_actionSend_message_2_triggered()
{
    hide();
    send_message = new Send_message(this,"group");
    send_message->show();
    send_message->exec();
}


void mainpage::on_actionCreate_triggered()
{
    Createchannel=new createchannel(this);
    Createchannel->show();
    Createchannel->exec();
}


void mainpage::on_actionCreate_2_triggered()
{
    Creategroup=new creategroup(this);
    Creategroup->show();
    Creategroup->exec();
}
//////////////////////////////////////////////////////////////////

void mainpage::on_actionShow_my_chat_triggered()
{
    c_messege=new join(this,"Cotact name:");
    c_messege->show();
    c_messege->exec();
}


void mainpage::on_actionChannel_messages_triggered()
{
    ch_messege=new join(this,"Channel name:");
    ch_messege->show();
    ch_messege->exec();
}


void mainpage::on_actionMy_group_messages_triggered()
{
    g_messege=new join(this,"Group name:");
    g_messege->show();
    g_messege->exec();
}
///////////////////////////////////////////////////////////////////

void mainpage::on_actionShow_my_users_triggered()
{
    Getuserlist=new getuserlist(this);
    Getuserlist->show();
    Getuserlist->exec();
}


void mainpage::on_actionMy_groups_triggered()
{
    Getgrouplist=new getgrouplist(this);
    Getgrouplist->show();
    Getgrouplist->exec();
}

