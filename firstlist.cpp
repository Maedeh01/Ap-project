#include "firstlist.h"
#include "ui_firstlist.h"

firstList::firstList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::firstList)
{
    ui->setupUi(this);
}

firstList::~firstList()
{
    delete ui;
}
