#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // this->setWindowFlag(Qt::FramelessWindowHint);

    // hide and initialize right scroll area
    ui->rightScrollArea->move(this->width(), 0);
    rightSideAnm = new QPropertyAnimation(ui->rightScrollArea, "geometry");
    rightSideAnm->setEasingCurve(QEasingCurve::InOutSine);
    rightSideAnm->setDuration(800);
    rightSideHidden = true;
    // other animation initializations
    matterScrollAreaAnm = new QPropertyAnimation(ui->matterScrolArea, "geometry");
    matterScrollAreaAnm->setEasingCurve(QEasingCurve::InOutSine);
    matterScrollAreaAnm->setDuration(800);
    mainNameEditAnm = new QPropertyAnimation(ui->mainNameEdit, "geometry");
    mainNameEditAnm->setEasingCurve(QEasingCurve::InOutSine);
    mainNameEditAnm->setDuration(800);
    // set submatters widgets in the right scroll area

    // set currDate
    currDate = QDate::currentDate();
    ui->mainDateEdit->setDate(currDate);

    // set matter handler
    handler = std::make_unique<MatterHandler>("matters.db");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_hideButton_clicked()
{
    rightSideAnm->setEndValue(QRect(this->width(), 0, ui->rightScrollArea->width(), ui->rightScrollArea->height()));
    rightSideAnm->setStartValue(QRect(this->width() - ui->rightScrollArea->width(), 0, ui->rightScrollArea->width(), ui->rightScrollArea->height()));
    rightSideAnm->start();

    mainNameEditAnm->setStartValue(ui->mainNameEdit->geometry());
    mainNameEditAnm->setEndValue(QRect(ui->mainNameEdit->x(), ui->mainNameEdit->y(),
                                       561, ui->mainDateEdit->height()));
    mainNameEditAnm->start();
    rightSideHidden = true;
}

void MainWindow::showRightSide(const Matter& matter) {
    if (rightSideHidden) {
        rightSideAnm->setStartValue(QRect(this->width(), 0, ui->rightScrollArea->width(), ui->rightScrollArea->height()));
        rightSideAnm->setEndValue(QRect(this->width() - ui->rightScrollArea->width(), 0, ui->rightScrollArea->width(), ui->rightScrollArea->height()));
        rightSideAnm->start();
        // move the mainNameEdit widget
        mainNameEditAnm->setStartValue(ui->mainNameEdit->geometry());
        mainNameEditAnm->setEndValue(QRect(ui->mainNameEdit->x(), ui->mainNameEdit->y(),
                                               ui->mainDateEdit->width(), ui->mainDateEdit->height()));
        mainNameEditAnm->start();
        // TODO: move the matterScrollArea

        rightSideHidden = false;
    }
    // update contents on the right side menu
    ui->nameEdit->setText(matter.getName());
    ui->dateEdit->setDate(currDate);
    ui->descriptionEdit->setText(matter.getDescription());
}

void MainWindow::on_mainNameEdit_returnPressed()
{
    auto name = ui->mainNameEdit->text();
    currMatter = Matter(name, "", currDate, "");
    currMatterId = handler->addNew(currMatter);
    updateMatters();
    showRightSide(currMatter);
    ui->mainNameEdit->setText("");
}


void MainWindow::on_mainDateEdit_dateChanged(const QDate &date)
{
    currDate = date;
    updateMatters();
}

void MainWindow::updateMatters() {
    // TODO: update matters in the matter scroll area


}


void MainWindow::on_nameEdit_editingFinished()
{
    currMatter.changeName(ui->nameEdit->text());
    updateMatters();
    handler->updateMatter(currMatterId, currMatter);
}


void MainWindow::on_descriptionEdit_editingFinished()
{
    currMatter.changeDescription(ui->descriptionEdit->text());
    updateMatters();
    handler->updateMatter(currMatterId, currMatter);
}


void MainWindow::on_dateEdit_dateChanged(const QDate &date)
{
    currMatter.changeDate(ui->dateEdit->date());
    updateMatters();
    handler->updateMatter(currMatterId, currMatter);
}


void MainWindow::on_page1_Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_page2_Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

