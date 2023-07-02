#ifndef GETGROUPLIST_H
#define GETGROUPLIST_H

#include <QDialog>
#include"forgot.h"
namespace Ui {
class getgrouplist;
}

class getgrouplist : public QDialog
{
    Q_OBJECT

public:
    explicit getgrouplist(QWidget *parent = nullptr);
    ~getgrouplist();

private:
    Ui::getgrouplist *ui;
    forgot*forget7;
};

#endif // GETGROUPLIST_H
