#ifndef CREATECHANNEL_H
#define CREATECHANNEL_H

#include <QDialog>
#include "forgot.h"
namespace Ui {
class createchannel;
}

class createchannel : public QDialog
{
    Q_OBJECT

public:
    explicit createchannel(QWidget *parent = nullptr);
    ~createchannel();

private slots:
    void on_pushButton_create_channel_clicked();

private:
    Ui::createchannel *ui;
    forgot*forget5;
};

#endif // CREATECHANNEL_H
