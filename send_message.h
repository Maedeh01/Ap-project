#ifndef SEND_MESSAGE_H
#define SEND_MESSAGE_H

#include <QDialog>
#include "forgot.h"

namespace Ui {
class Send_message;
}

class Send_message : public QDialog
{
    Q_OBJECT
    QString type;

public:
    explicit Send_message(QWidget *parent = nullptr,QString t = nullptr);
    ~Send_message();

private slots:
    void on_pushButton_ok_send_clicked();

private:
    Ui::Send_message *ui;
    forgot *forgot_send;
};

#endif // SEND_MESSAGE_H
