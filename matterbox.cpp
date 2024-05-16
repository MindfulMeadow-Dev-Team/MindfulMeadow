#include "matterbox.h"
#include "ui_matterbox.h"

MatterBox::MatterBox(Matter matter, int matterId, MatterHandler* handler, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MatterBox)
    , matter{matter}
    , handler{handler}
    , matterId{matterId}
{
    ui->setupUi(this);

    ui->checkBox->setText(matter.getName());
    ui->description->setText(matter.getDescription());
    ui->checkBox->setChecked(matter.getState());
}

MatterBox::~MatterBox()
{
    delete ui;
    // DO NOT delete handler!
}

void MatterBox::on_checkBox_stateChanged(int state)
{
    if (state == Qt::Unchecked) {
        matter.changeState(0);
    }
    else {
        matter.changeState(1);
    }
    handler->updateMatter(matterId, matter);
}
