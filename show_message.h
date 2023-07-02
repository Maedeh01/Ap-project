#ifndef SHOW_MESSAGE_H
#define SHOW_MESSAGE_H

#include <QDialog>

namespace Ui {
class show_message;
}

class show_message : public QDialog
{
    Q_OBJECT

public:
    explicit show_message(QWidget *parent = nullptr,QString name="name",QString msgbox="Empty!");
    ~show_message();

private:
    Ui::show_message *ui;
};

#endif // SHOW_MESSAGE_H
