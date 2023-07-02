#ifndef LOGOUT_H
#define LOGOUT_H

#include <QDialog>
#include "forgot.h"
#include "show_message.h"

namespace Ui {
class Logout;
}

class Logout : public QDialog
{
    Q_OBJECT
    QString type;
public:
   // explicit Logout(QWidget *parent = nullptr);
    explicit Logout(QWidget *parent = nullptr,QString ftxt="text",QString stxt="text");
    ~Logout();

private slots:

    void on_push_Button_clicked();

private:
    Ui::Logout *ui;
    forgot *Forgot;
    show_message *msg;
    forgot *warning;


};

#endif // LOGOUT_H
