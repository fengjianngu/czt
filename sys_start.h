#ifndef SYS_START_H
#define SYS_START_H

#include <QWidget>

namespace Ui {
class sys_start;
}

class sys_start : public QWidget
{
    Q_OBJECT

public:
    explicit sys_start(QWidget *parent = 0);
    ~sys_start();

private:
    Ui::sys_start *ui;
};

#endif // SYS_START_H
