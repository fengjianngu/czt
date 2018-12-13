#ifndef LOW_POWER_H
#define LOW_POWER_H

#include <QWidget>

namespace Ui {
class Low_Power;
}

class Low_Power : public QWidget
{
    Q_OBJECT

public:
    explicit Low_Power(QWidget *parent = 0);
    ~Low_Power();

private:
    Ui::Low_Power *ui;
};

#endif // LOW_POWER_H
