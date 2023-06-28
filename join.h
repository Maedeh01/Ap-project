#ifndef JOIN_H
#define JOIN_H

#include <QDialog>
#include "forgot.h"

namespace Ui {
class join;
}

class join : public QDialog
{
    Q_OBJECT
    QString type;
public:
    explicit join(QWidget *parent = nullptr,QString lable=nullptr);
    ~join();

private slots:
    void on_pushButton_join_clicked();

private:
    Ui::join *ui;
    forgot *forget3;
};

#endif // JOIN_H
