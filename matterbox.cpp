#include "matterbox.h"
#include "ui_matterbox.h"

MatterBox::MatterBox(Matter* matter, MatterHandler* handler, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MatterBox)
    , matter{matter}
    , handler{handler}
{
    ui->setupUi(this);

    ui->name->setText(matter->getName());
    ui->description->setText(matter->getDescription());
}

MatterBox::~MatterBox()
{
    delete ui;
}
