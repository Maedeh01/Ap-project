#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QMainWindow>
#include "logout.h"

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

private:
    Ui::mainpage *ui;
    Logout *logout;
};

#endif // MAINPAGE_H
