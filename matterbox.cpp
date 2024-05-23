#include "matterbox.h"
#include "ui_matterbox.h"

MatterBox::MatterBox(Matter matter, int matterId, int kind,
                     MatterHandler* handler, MainWindow* mainWindow, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MatterBox)
    , matter{matter}
    , handler{handler}
    , matterId{matterId}
    , kind{kind}
    , mainWindow{mainWindow}
{
    ui->setupUi(this);
    // show the name of the matter
    ui->checkBox->setText(matter.getName());
    auto des = matter.getDescription();
    // If the description is not empty, show it.
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
    // In matterScrollArea2, the date is always shown.
    if (kind == 1) {
        this->setFixedHeight(this->geometry().height() + 20);
        // If the year is not this year, show it.
        if (matter.getDate().year() != QDate::currentDate().year()) {
            ui->time->setText(matter.getDate().toString("yyyy-MM-dd "));
        }
        else {
            ui->time->setText(matter.getDate().toString("MM-dd "));
        }
        if (matter.getSetDue()) {
            ui->time->setText(ui->time->text() + matter.getDueTime().toString("h:mm"));
        }
        ui->time->adjustSize();
        ui->time->move(QPoint(40, this->geometry().height() - 20));
    }
    else if (matter.getSetDue()) {
        this->setFixedHeight(this->geometry().height() + 20);
        ui->time->setText(matter.getDueTime().toString("h:mm"));
        ui->time->adjustSize();
        ui->time->move(QPoint(40, this->geometry().height() - 20));
    }
    // else if (matter.getDate() < mainWindow->currDate) {
    //     this->setFixedHeight(this->geometry().height() + 20);
    //     ui->time->setText(matter.getDate().toString("MM-dd"));
    //     ui->time->adjustSize();
    //     ui->time->move(QPoint(40, this->geometry().height() - 20));
    // }
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

void MatterBox::on_underlyingBtn_clicked()
{
    if (kind == 0) {
        mainWindow->currMatter = matter;
        mainWindow->currMatterId = matterId;
        mainWindow->showRightSide();
    }
}

// Check if the schedule is overdue.
// If so, display the due time in red.
void MatterBox::checkTime() {
    bool cond1 = matter.getDate() < QDate::currentDate();
    bool cond2 = matter.getDate() == QDate::currentDate() && matter.getSetDue() && matter.getDueTime() < QTime::currentTime();;
    // if (cond1 && matter.getState() == false) {
    //     ui->time->setStyleSheet("color:red");
    //     if (kind == 1) {
    //         return;
    //     }
    //     if (matter.getDate() != mainWindow->currDate) {
    //         ui->time->setText(matter.getDate().toString("MM-dd"));
    //         // If the year is not this year, show it.
    //         if (matter.getDate().year() != QDate::currentDate().year()) {
    //             ui->time->setText(matter.getDate().year() + "-" + ui->time->text());
    //         }
    //         if (matter.getSetDue()) {
    //             ui->time->setText(ui->time->text() + " " + matter.getDueTime().toString("h:mm"));
    //         }
    //     }
    //     else if (matter.getSetDue()){
    //         ui->time->setText(matter.getDueTime().toString("h:mm"));
    //     }
    // }
    // else if (cond2 && matter.getState() == false) {
    //     ui->time->setStyleSheet("color:red");
    // }
    // else {
    //     ui->time->setStyleSheet("color:black");
    // }
    if ((cond1 || cond2) && matter.getState() == false) {
        ui->time->setStyleSheet("color:red");
    }
    else {
        ui->time->setStyleSheet("color:black");
    }
    ui->time->adjustSize();
}

// SIGNAL(clicked) is emitted only when user clicked the box.
// In other words, the signal will not be emitted by code.
void MatterBox::on_checkBox_clicked(bool checked)
{
    if (checked) {
        matter.changeState(1);
    }
    else {
        matter.changeState(0);
    }
    handler->updateMatter(matterId, matter);
    if (kind == 1) {
        mainWindow->updateMatters2();
    }
    else if (kind == 0){
        mainWindow->updateMatters();
    }
    else {
        checkTime();
    }
}

