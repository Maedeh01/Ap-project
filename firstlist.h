#ifndef FIRSTLIST_H
#define FIRSTLIST_H

#include <QDialog>

namespace Ui {
class firstList;
}

class firstList : public QDialog
{
    Q_OBJECT

public:
    explicit firstList(QWidget *parent = nullptr);
    ~firstList();

private:
    Ui::firstList *ui;
};

#endif // FIRSTLIST_H
