#include "matterbox.h"
#include "ui_matterbox.h"

MatterBox::MatterBox(Matter matter, int matterId, MatterHandler* handler, MainWindow* mainWindow, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MatterBox)
    , matter{matter}
    , handler{handler}
    , matterId{matterId}
    , mainWindow{mainWindow}
{
    ui->setupUi(this);

    ui->checkBox->setText(matter.getName());
    auto des = matter.getDescription();
    if (des == "") {
        this->setFixedHeight(40);
        ui->checkBox->setChecked(matter.getState());
        ui->checkBox->adjustSize();
        ui->checkBox->move(QPoint(20, (this->geometry().height() - ui->checkBox->geometry().height()) / 2));
        ui->description->setVisible(false);
    }
    else {
        this->setFixedHeight(60);
        ui->checkBox->setChecked(matter.getState());
        ui->checkBox->adjustSize();
        ui->checkBox->move(QPoint(20, 10));
        ui->description->setText(matter.getDescription());
        ui->description->move(QPoint(40, 35));
        ui->description->adjustSize();
    }
    if (matter.getSetDue()) {
        this->setFixedHeight(this->geometry().height() + 20);
        ui->time->setText(matter.getDueTime().toString("h:mm"));
        ui->time->adjustSize();
        ui->time->move(QPoint(40, this->geometry().height() - 20));
    }
    else if (matter.getDate() < QDate::currentDate()) {
        this->setFixedHeight(this->geometry().height() + 20);
        ui->time->setText(matter.getDate().toString("MM-dd"));
        ui->time->adjustSize();
        ui->time->move(QPoint(40, this->geometry().height() - 20));
    }
    else {
        ui->time->setVisible(false);
    }
    checkTime();
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
    checkTime();
}

void MatterBox::on_underlyingBtn_clicked()
{
    mainWindow->currMatter = matter;
    mainWindow->currMatterId = matterId;
    mainWindow->showRightSide();
}

// Check if the schedule is overdue.
// If so, display the due time in red.
void MatterBox::checkTime() {
    bool cond1 = matter.getDate() < QDate::currentDate();
    bool cond2 = matter.getDate() == QDate::currentDate() && matter.getSetDue() && matter.getDueTime() < QTime::currentTime();;
    if ((cond1 || cond2) && matter.getState() == false) {
        ui->time->setStyleSheet("color:red");
    }
    else {
        ui->time->setStyleSheet("color:black");
        if (matter.getDate() < mainWindow->currDate) {
            this->hide();
        }
    }
}
