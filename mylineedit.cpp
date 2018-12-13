#include "mylineedit.h"

myLineEdit::myLineEdit( QWidget *parent):QLineEdit(parent)
{

}

void myLineEdit::mousePressEvent(QMouseEvent *event)
{
    emit mySignal( this);
    QLineEdit::mousePressEvent( event);
}
