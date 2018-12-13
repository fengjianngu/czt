#include "sys_set.h"
#include "ui_sys_set.h"

Sys_set::Sys_set(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sys_set)
{
    ui->setupUi(this);




    xlogin = new CsysLogin(this);
    xlogin->setWindowFlags(Qt::FramelessWindowHint);
    xlogin->move(0, 42);
    xlogin->hide();

    connect(xlogin, SIGNAL(mySignal(void*)), this, SLOT(KeyBoardShow(void*)));





}

Sys_set::~Sys_set()
{
    delete ui;
}

void Sys_set::on_pushButton_2_clicked()
{

    xlogin->usr_show(2);
    xlogin->setFocus();

}

void  Sys_set::KeyBoardShow(void *pthis)
{

     //qDebug()<<"ok44444！！！"<<endl;
//
  //  if( pthis == ui->lineEdit)
      //  xkeypad->show( (myLineEdit *)pthis, "设备编号");

   // else
     //   xkeypad->show( (myLineEdit *)pthis, "登录");
}
