#ifndef JOIN_H
#define JOIN_H

#include <QDialog>
#include "forgot.h"
#include "show_message.h"

namespace Ui {
class join;
}

class join : public QDialog
{
    Q_OBJECT
    QString type;
public:
    explicit join(QWidget *parent = nullptr,QString lable=nullptr);
    //void othercodes(QString code);
    void othercodes(QString code,QString message){

        //if other json codes

        //show_message *msg;
        if (code == "401" ){
            //hide();
            warning = new forgot(this,"Error",message);
            warning->show();
            warning->exec();
        }
        else if (code == "404" ){
            hide();
            warning = new forgot(this,"Error",message);
            warning->show();
            warning->exec();
        }
        else if (code=="204"){
            hide();
            warning = new forgot(this,"Error",message);
            warning->show();
            warning->exec();
        }
    }
    ~join();

private slots:
    void on_pushButton_join_clicked();

private:
    Ui::join *ui;
    forgot *forget3;
    show_message *msg;
    forgot *warning;
};

#endif // JOIN_H
