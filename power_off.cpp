#include "power_off.h"
#include "ui_power_off.h"

Power_Off::Power_Off(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Power_Off)
{
    ui->setupUi(this);
}

Power_Off::~Power_Off()
{
    delete ui;
}
