#include "hs_sb.h"
#include "ui_hs_sb.h"

Hs_sb::Hs_sb(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hs_sb)
{
    ui->setupUi(this);
}

Hs_sb::~Hs_sb()
{
    delete ui;
}
