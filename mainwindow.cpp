#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    ui->statusbar->setVisible(false);

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

    // set up tray icon
    tray = new QSystemTrayIcon();
    // TODO: change the icon
    tray->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::EditDelete));
    trayShow = new QAction("MindfulMeadow", this);
    connect(trayShow, SIGNAL(triggered(bool)), this, SLOT(show()));
    trayExit = new QAction("退出", this);
    connect(trayExit, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    trayMenu = new QMenu(this);
    trayMenu->addAction(trayShow);
    trayMenu->addAction(trayExit);
    tray->setContextMenu(trayMenu);
    tray->show();


    // set up the timer
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
    timer->start(1000 * 60);

    // set currDate
    currDate = QDate::currentDate();
    ui->mainDateEdit->setDate(currDate);

    // add layout to matterScrollArea
    ui->matterScrollArea->widget()->setLayout(new QVBoxLayout());
    ui->matterScrollArea->horizontalScrollBar()->hide();
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
    // if the right side menu is already hidden, do nothing
    if (rightSideHidden == false) {
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
}

// If the right side is hidden, show it.
// If the right side is already shown, update the contents.
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
        // move the scroll area
        matterScrollAreaAnm->setStartValue(ui->matterScrollArea->geometry());
        matterScrollAreaAnm->setEndValue(QRect(ui->matterScrollArea->x(), ui->matterScrollArea->y(),
                                           ui->mainDateEdit->width(), ui->matterScrollArea->height()));
        matterScrollAreaAnm->start();
        rightSideHidden = false;
    }
    // update contents on the right side menu
    // name
    ui->nameEdit->setText(currMatter.getName());
    // date
    ui->dateEdit->setDate(currMatter.getDate());
    // description
    ui->descriptionEdit->setText(currMatter.getDescription());
    // check box
    if (currMatter.getSetDue()) {
        ui->setDueCheckbox->setChecked(true);
        ui->timeEdit->setTime(currMatter.getDueTime());
    }
    else {
        ui->setDueCheckbox->setChecked(false);
        ui->timeEdit->setVisible(false);
    }
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

// update matters in the matter scroll area
void MainWindow::updateMatters() {
    auto [matters, ids] = handler->getMatters(currDate);
    int size = matters.size();
    auto layout = ui->matterScrollArea->widget()->layout();
    if (!layout) {
        qDebug() << "no layout error\n";
        return;
    }
    layout->setSpacing(10);
    while (layout->count()) {
        auto widget = layout->itemAt(0)->widget();
        widget->setParent(nullptr);
        layout->removeWidget(widget);
        delete widget;
    }
    for (int i = 0; i < size; ++i) {
        MatterBox* box = new MatterBox(matters[i], ids[i], handler.get(), this);
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

// Called when the user change the date other than code.
void MainWindow::on_mainDateEdit_userDateChanged(const QDate &date)
{
    currMatter.changeDate(ui->dateEdit->date());
    handler->updateMatter(currMatterId, currMatter);
    updateMatters();
}


void MainWindow::on_page1_Button_clicked()
{
    hideRightSide();
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_page2_Button_clicked()
{
    hideRightSide();
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_deleteBtn_clicked()
{
    handler->deleteMatter(currMatterId);
    updateMatters();
    hideRightSide();
}


void MainWindow::on_setDueCheckbox_clicked(bool checked)
{
    if (checked) {
        currMatter.changeSetDue(1);
        ui->timeEdit->setVisible(true);
    }
    else {
        currMatter.changeSetDue(0);
        ui->timeEdit->setVisible(false);
    }
    handler->updateMatter(currMatterId, currMatter);
    updateMatters();
}

void MainWindow::on_timeEdit_userTimeChanged(const QTime &time)
{
    currMatter.changeDueTime(time);
    handler->updateMatter(currMatterId, currMatter);
    updateMatters();
}


void MainWindow::on_dateEdit_userDateChanged(const QDate &date)
{
    currMatter.changeDate(date);
    handler->updateMatter(currMatterId, currMatter);
    updateMatters();
}

// Slot function for SIGNAL(QTimer::timeout()).
// To display the windows notice when a schedule is dued.
void MainWindow::on_timeout() {
    auto currTime = QTime::currentTime().toString("h:mm");
    auto [matters, ids] = handler->getMatters(QDate::currentDate());
    for (const auto& matter: matters) {
        if (matter.getSetDue() && matter.getState() == false && matter.getDueTime().toString("h:mm") == currTime) {
            qDebug() << "show message of matter with name " << matter.getName() << Qt::endl;
            tray->showMessage(matter.getName(), "时间到啦！");
        }
    }
}

// override function closeEvent for system tray icon.
void MainWindow::closeEvent(QCloseEvent *event) {
    if (tray->isVisible()) {
        this->hide();
        tray->showMessage("MindfulMeadow", "应用已缩小到托盘区");
        event->ignore();
    }
    else {
        event->accept();
    }
}

