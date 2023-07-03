#ifndef GETCHANNELLIST_H
#define GETCHANNELLIST_H

#include <QDialog>

namespace Ui {
class getchannellist;
}

class getchannellist : public QDialog
{
    Q_OBJECT

public:
    explicit getchannellist(QWidget *parent = nullptr);
    ~getchannellist();

private:
    Ui::getchannellist *ui;
};

#endif // GETCHANNELLIST_H
