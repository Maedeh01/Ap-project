#ifndef FORGOT_H
#define FORGOT_H

#include <QDialog>

namespace Ui {
class forgot;
}

class forgot : public QDialog
{
    Q_OBJECT

public:
    explicit forgot(QWidget *parent = nullptr);
    ~forgot();

private:
    Ui::forgot *ui;
};

#endif // FORGOT_H
