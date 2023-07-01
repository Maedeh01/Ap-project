#ifndef CREATEGROUP_H
#define CREATEGROUP_H

#include <QDialog>
#include"forgot.h"
namespace Ui {
class creategroup;
}

class creategroup : public QDialog
{
    Q_OBJECT

public:
    explicit creategroup(QWidget *parent = nullptr);
    ~creategroup();

private slots:
    void on_pushButton_create_group_clicked();

private:
    Ui::creategroup *ui;
    forgot*forget6;
};

#endif // CREATEGROUP_H
