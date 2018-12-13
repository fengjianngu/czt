#ifndef POWER_OFF_H
#define POWER_OFF_H

#include <QWidget>

namespace Ui {
class Power_Off;
}

class Power_Off : public QWidget
{
    Q_OBJECT

public:
    explicit Power_Off(QWidget *parent = 0);
    ~Power_Off();

private:
    Ui::Power_Off *ui;
};

#endif // POWER_OFF_H
