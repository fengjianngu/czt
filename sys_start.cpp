#include "sys_start.h"
#include "ui_sys_start.h"

sys_start::sys_start(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sys_start)
{
    ui->setupUi(this);
}

sys_start::~sys_start()
{
    delete ui;
}
