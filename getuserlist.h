#ifndef GETUSERLIST_H
#define GETUSERLIST_H

#include <QDialog>
#include"forgot.h"
namespace Ui {
class getuserlist;
}

class getuserlist : public QDialog
{
    Q_OBJECT

public:
    explicit getuserlist(QWidget *parent = nullptr);
    ~getuserlist();

private slots:
    void on_pushButton_show_userlist_clicked();

private:
    Ui::getuserlist *ui;
    forgot*forget6;
};

#endif // GETUSERLIST_H
