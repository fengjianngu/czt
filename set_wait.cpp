#include "set_wait.h"
#include "ui_set_wait.h"

Set_Wait::Set_Wait(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Set_Wait)
{
    ui->setupUi(this);
}

Set_Wait::~Set_Wait()
{
    delete ui;
}
