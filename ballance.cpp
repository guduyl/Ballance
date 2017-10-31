#include "ballance.h"
#include "ui_ballance.h"

Ballance::Ballance(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ballance)
{
    ui->setupUi(this);
}

Ballance::~Ballance()
{
    delete ui;
}
