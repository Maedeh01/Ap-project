#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include "mainpage.h"
#include "forgot.h"

namespace Ui {
class Signup;
}

class Signup : public QDialog
{
    Q_OBJECT

public:
    explicit Signup(QWidget *parent = nullptr);
    ~Signup();

private slots:
    void on_pushButton_ok_Signup_clicked();

private:
    Ui::Signup *ui;
    mainpage *Mainpage;
    forgot *forget2;
};

#endif // SIGNUP_H
