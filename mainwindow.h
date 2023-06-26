#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "forgot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushbutton_forget_clicked();

    void on_pushButton_signup_clicked();

private:
    Ui::MainWindow *ui;
    forgot *forget;
};
#endif // MAINWINDOW_H
