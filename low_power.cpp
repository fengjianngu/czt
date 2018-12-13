#include "low_power.h"
#include "ui_low_power.h"

Low_Power::Low_Power(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Low_Power)
{
    ui->setupUi(this);
}

Low_Power::~Low_Power()
{
    delete ui;
}
