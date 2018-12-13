#ifndef SYS_SET_H
#define SYS_SET_H

#include <QWidget>
#include "csys_login.h"
#include "qxkeypad/QxKeyBoard.h"
#include "mylineedit.h"

namespace Ui {
class Sys_set;
}

class Sys_set : public QWidget
{
    Q_OBJECT

public:
    explicit Sys_set(QWidget *parent = 0);
    ~Sys_set();

private slots:
    void on_pushButton_2_clicked();
    void KeyBoardShow(void *pthis);


private:
    Ui::Sys_set *ui;
    CsysLogin *xlogin;

};

#endif // SYS_SET_H
