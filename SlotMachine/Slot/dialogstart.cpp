#include "dialogstart.hh"
#include "ui_dialogstart.h"

DialogStart::DialogStart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogStart)
{
    ui->setupUi(this);
}

DialogStart::~DialogStart()
{
    delete ui;
}

int DialogStart::getMoney()
{
    return _money;
}

void DialogStart::configMoney()
{
    _money = ui->spinBox->value();
}
