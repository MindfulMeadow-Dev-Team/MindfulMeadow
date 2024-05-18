#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // this->setWindowFlag(Qt::FramelessWindowHint);

    // set matter handler
    handler = std::make_unique<MatterHandler>("matters.db");

    // hide and initialize right scroll area
    ui->rightScrollArea->move(this->width(), 0);
    rightSideAnm = new QPropertyAnimation(ui->rightScrollArea, "geometry");
    rightSideAnm->setEasingCurve(QEasingCurve::InOutSine);
    rightSideAnm->setDuration(800);
    rightSideHidden = true;
    // other animation initializations
    matterScrollAreaAnm = new QPropertyAnimation(ui->matterScrollArea, "geometry");
    matterScrollAreaAnm->setEasingCurve(QEasingCurve::InOutSine);
    matterScrollAreaAnm->setDuration(800);
    mainNameEditAnm = new QPropertyAnimation(ui->mainNameEdit, "geometry");
    mainNameEditAnm->setEasingCurve(QEasingCurve::InOutSine);
    mainNameEditAnm->setDuration(800);

    // set currDate
    currDate = QDate::currentDate();
    ui->mainDateEdit->setDate(currDate);

    // add layout to matterScrollArea
    ui->matterScrollArea->widget()->setLayout(new QGridLayout());
    updateMatters();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_hideButton_clicked()
{
    hideRightSide();
}

void MainWindow::hideRightSide() {
    rightSideAnm->setEndValue(QRect(this->width(), 0, ui->rightScrollArea->width(), ui->rightScrollArea->height()));
    rightSideAnm->setStartValue(QRect(this->width() - ui->rightScrollArea->width(), 0, ui->rightScrollArea->width(), ui->rightScrollArea->height()));
    rightSideAnm->start();

    mainNameEditAnm->setStartValue(ui->mainNameEdit->geometry());
    mainNameEditAnm->setEndValue(QRect(ui->mainNameEdit->x(), ui->mainNameEdit->y(),
                                       561, ui->mainDateEdit->height()));
    mainNameEditAnm->start();
    matterScrollAreaAnm->setStartValue(ui->matterScrollArea->geometry());
    matterScrollAreaAnm->setEndValue(QRect(ui->matterScrollArea->x(), ui->matterScrollArea->y(),
                                           561, ui->matterScrollArea->height()));
    matterScrollAreaAnm->start();
    rightSideHidden = true;
}

void MainWindow::showRightSide() {
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
        matterScrollAreaAnm->setStartValue(ui->matterScrollArea->geometry());
        matterScrollAreaAnm->setEndValue(QRect(ui->matterScrollArea->x(), ui->matterScrollArea->y(),
                                           ui->mainDateEdit->width(), ui->matterScrollArea->height()));
        matterScrollAreaAnm->start();
        rightSideHidden = false;
    }
    // update contents on the right side menu
    ui->nameEdit->setText(currMatter.getName());
    ui->dateEdit->setDate(currDate);
    ui->descriptionEdit->setText(currMatter.getDescription());
}

void MainWindow::on_mainNameEdit_returnPressed()
{
    auto name = ui->mainNameEdit->text();
    currMatter = Matter(name, "", currDate, "");
    currMatterId = handler->addNew(currMatter);
    updateMatters();
    showRightSide();
    ui->mainNameEdit->setText("");
}


void MainWindow::on_mainDateEdit_dateChanged(const QDate &date)
{
    currDate = date;
    updateMatters();
}

void MainWindow::updateMatters() {
    // TODO: update matters in the matter scroll area
    auto [matters, ids] = handler->getMatters(currDate);
    int size = matters.size();
    auto layout = ui->matterScrollArea->widget()->layout();
    if (!layout) {
        qDebug() << "no layout error\n";
        return;
    }
    while (layout->count()) {
        auto widget = layout->itemAt(0)->widget();
        widget->setParent(nullptr);
        layout->removeWidget(widget);
        delete widget;
    }
    for (int i = 0; i < size; ++i) {
        MatterBox* box = new MatterBox(matters[i], ids[i], handler.get(), this);
        box->setMinimumHeight(60);
        layout->addWidget(box);
    }
    ui->matterScrollArea->verticalScrollBar()->setValue(0);
}


void MainWindow::on_nameEdit_editingFinished()
{
    currMatter.changeName(ui->nameEdit->text());
    handler->updateMatter(currMatterId, currMatter);
    updateMatters();
}


void MainWindow::on_descriptionEdit_editingFinished()
{
    currMatter.changeDescription(ui->descriptionEdit->text());
    handler->updateMatter(currMatterId, currMatter);
    updateMatters();
}


void MainWindow::on_dateEdit_dateChanged(const QDate &date)
{
    currMatter.changeDate(ui->dateEdit->date());
    handler->updateMatter(currMatterId, currMatter);
    updateMatters();
}


void MainWindow::on_page1_Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_page2_Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_deleteBtn_clicked()
{
    handler->deleteMatter(currMatterId);
    updateMatters();
    hideRightSide();
}

