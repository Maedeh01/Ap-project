#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QMainWindow>
#include "logout.h"
#include "join.h"

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

private:
    Ui::mainpage *ui;
    Logout *logout;
    join *Join2;
};

#endif // MAINPAGE_H
