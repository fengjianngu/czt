#ifndef SET_WAIT_H
#define SET_WAIT_H

#include <QWidget>

namespace Ui {
class Set_Wait;
}

class Set_Wait : public QWidget
{
    Q_OBJECT

public:
    explicit Set_Wait(QWidget *parent = 0);
    ~Set_Wait();

private:
    Ui::Set_Wait *ui;
};

#endif // SET_WAIT_H
