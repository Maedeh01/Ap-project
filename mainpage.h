#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QMainWindow>
#include "logout.h"
#include "join.h"
#include "send_message.h"
#include "createchannel.h"

namespace Ui {
class mainpage;
}

class mainpage : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainpage(QWidget *parent = nullptr);
    ~mainpage();

private slots:
    void on_actionLogout_triggered();

    void on_actionJoin_2_triggered();

    void on_actionJoin_triggered();

    void on_actionContacts_send_triggered();

    void on_actionSend_message_triggered();

    void on_actionSend_message_2_triggered();

    void on_actionCreate_triggered();

private:
    Ui::mainpage *ui;
    Logout *logout;
    join *Join2;
    Send_message *send_message;
    createchannel*Createchannel;
};

#endif // MAINPAGE_H
