#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QLineEdit>

class myLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    myLineEdit(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *);

signals:
    void mySignal(void* pthis);
};

#endif // MYLINEEDIT_H
