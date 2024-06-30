#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusbar->setVisible(false);

    // set up matter handler
    handler = std::make_unique<MatterHandler>("matters.db");

    // hide and initialize right scroll area and its animation
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

    // initialize miniwindow
    mini = new MiniSchedule(handler.get(), this);

    // set up white noise window
    whiteNoise = new WhiteNoiseWindow();

    // set up tray icon
    tray = new QSystemTrayIcon();
    tray->setIcon(QIcon(":/icon/img/mainIcon.png"));
    auto trayShow = new QAction("MindfulMeadow", this);
    connect(trayShow, SIGNAL(triggered(bool)), this, SLOT(show()));
    auto trayMini = new QAction("悬浮窗口", this);
    connect(trayMini, SIGNAL(triggered(bool)), mini, SLOT(show()));
    auto trayPlayMusic = new QAction("播放/暂停白噪声", this);
    connect(trayPlayMusic, SIGNAL(triggered(bool)), whiteNoise, SLOT(playMusic()));
    auto trayExit = new QAction("退出", this);
    connect(trayExit, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    trayMenu = new QMenu(this);
    trayMenu->addAction(trayShow);
    trayMenu->addSeparator();
    trayMenu->addAction(trayMini);
    trayMenu->addAction(trayPlayMusic);
    trayMenu->addSeparator();
    trayMenu->addAction(trayExit);
    tray->setContextMenu(trayMenu);
    tray->show();
    connect(tray, &QSystemTrayIcon::activated, this, &MainWindow::on_activatedSysTrayIcon);

    // set up the timer
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
    timer->start(1000 * 60);

    // set currDate
    currDate = QDate::currentDate();
    ui->mainDateEdit->setDate(currDate);

    // add layout to matterScrollAreas
    ui->matterScrollArea->widget()->setLayout(new QVBoxLayout());
    ui->matterScrollArea->horizontalScrollBar()->hide();
    ui->matterScrollArea->widget()->layout()->setContentsMargins(0, 10, 10, 10);
    ui->matterScrollArea->widget()->layout()->setSpacing(0);
    ui->matterScrollArea->widget()->layout()->setAlignment(Qt::AlignTop);
    ui->matterScrollArea->widget()->setObjectName("scrollAreaContent");
    updateMatters();
    ui->matterScrollArea2->widget()->setLayout(new QVBoxLayout());
    ui->matterScrollArea2->widget()->layout()->setContentsMargins(0, 10, 10, 10);
    ui->matterScrollArea2->widget()->layout()->setSpacing(0);
    ui->matterScrollArea2->widget()->layout()->setAlignment(Qt::AlignTop);
    ui->matterScrollArea2->horizontalScrollBar()->hide();
    ui->matterScrollArea2->widget()->setObjectName("scrollAreaContent2");
    updateRecentMatters();

    // set up the forest window
    ptree=nullptr;
    frst=nullptr;
    connect(ui->plantButton, &QPushButton::clicked, this, &MainWindow::on_treeButton_clicked);
    closeflag = 0;

    // set the stacked widget to page 1
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete rightSideAnm;
    delete mainNameEditAnm;
    delete matterScrollAreaAnm;
    delete tray;
    delete trayMenu;
    delete timer;
    delete mini;
    delete ptree;
    delete frst;
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
                                           590, 40));
        mainNameEditAnm->start();
        matterScrollAreaAnm->setStartValue(ui->matterScrollArea->geometry());
        matterScrollAreaAnm->setEndValue(QRect(ui->matterScrollArea->x(), ui->matterScrollArea->y(),
                                               590, ui->matterScrollArea->height()));
        matterScrollAreaAnm->start();
        rightSideHidden = true;
    }
}

// If the right side is hidden, show it.
// If the right side is already shown, update the contents.
void MainWindow::showRightSide() {
    if (ui->stackedWidget->currentIndex() == 1)
        return;
    if (rightSideHidden) {
        rightSideAnm->setStartValue(QRect(this->width(), 0, ui->rightScrollArea->width(), ui->rightScrollArea->height()));
        rightSideAnm->setEndValue(QRect(this->width() - ui->rightScrollArea->width(), 0, ui->rightScrollArea->width(), ui->rightScrollArea->height()));
        rightSideAnm->start();
        // move the mainNameEdit widget
        mainNameEditAnm->setStartValue(ui->mainNameEdit->geometry());
        mainNameEditAnm->setEndValue(QRect(ui->mainNameEdit->x(), ui->mainNameEdit->y(),
                                           400, 40));
        mainNameEditAnm->start();
        // move the scroll area
        matterScrollAreaAnm->setStartValue(ui->matterScrollArea->geometry());
        matterScrollAreaAnm->setEndValue(QRect(ui->matterScrollArea->x(), ui->matterScrollArea->y(),
                                                400, ui->matterScrollArea->height()));
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
        ui->timeEdit->setVisible(true);
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
    while (layout->count()) {
        auto widget = layout->itemAt(0)->widget();
        widget->setParent(nullptr);
        layout->removeWidget(widget);
        delete widget;
    }
    if (size == 0) {
        ui->matterScrollArea->widget()->setStyleSheet("QWidget#scrollAreaContent {background-image: url(:/img/noMatter.png);background-size: cover;background-position: center center; background-size: 100px;}");
        return;
    }
    for (int i = 0; i < size; ++i) {
        MatterBox* box = new MatterBox(matters[i], ids[i], 0, handler.get(), this);
        layout->addWidget(box);
    }
    ui->matterScrollArea->widget()->setStyleSheet("");
    ui->matterScrollArea->verticalScrollBar()->setValue(0);
}

void MainWindow::updateRecentMatters() {
    auto [matters, ids] = handler->getMattersSince(QDate::currentDate(), 10);
    int size = matters.size();
    qDebug() << size << Qt::endl;
    auto layout = ui->matterScrollArea2->widget()->layout();
    if (!layout) {
        qDebug() << "no layout error\n";
        return;
    }
    // layout->setSpacing(10);
    while (layout->count()) {
        auto widget = layout->itemAt(0)->widget();
        widget->setParent(nullptr);
        layout->removeWidget(widget);
        delete widget;
    }
    if (size == 0) {
        ui->matterScrollArea2->widget()->setStyleSheet("QWidget#scrollAreaContent2 {background-image: url(://img/noMatter.png);background-size: cover;background-position: center center; background-size: 100px;}");
        return;
    }
    for (int i = 0; i < size; ++i) {
        MatterBox* box = new MatterBox(matters[i], ids[i], 1, handler.get(), this);
        layout->addWidget(box);
    }
    ui->matterScrollArea2->widget()->setStyleSheet("");
    ui->matterScrollArea2->verticalScrollBar()->setValue(0);
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
    updateMatters();
    if(frst){
        frst->close();
        frst=nullptr;
    }
}


void MainWindow::on_page2_Button_clicked()
{
    hideRightSide();
    ui->stackedWidget->setCurrentIndex(1);
    updateRecentMatters();
    if(frst){
        frst->close();
        frst=nullptr;
    }
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
        ui->timeEdit->setTime(QTime::currentTime());
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
// if white noise window is visible, hide it
void MainWindow::closeEvent(QCloseEvent *event) {
    if (tray->isVisible()) {
        this->hide();
        tray->showMessage("MindfulMeadow", "应用已缩小到托盘区");
        event->ignore();
    }
    else {
        event->accept();
    }
    if (whiteNoise->isVisible()) {
        whiteNoise->hide();
    }
}

void MainWindow::on_miniButton_clicked()
{
    mini->show();
    this->hide();
}

// Each time the main window is shown, flash the matter scroll area.
void MainWindow::showEvent(QShowEvent *event) {
    updateMatters();
    updateRecentMatters();
    QMainWindow::showEvent(event);
}

void MainWindow::on_whiteNoiseButton_clicked()
{
    whiteNoise->show();
    whiteNoise->move(this->x() + 503, this->y() + 290);
}

// If mouse clicked on the main window, hide the white noise window.
void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (whiteNoise->isVisible()) {
        whiteNoise->hide();
    }
    QMainWindow::mousePressEvent(event);
}

void MainWindow::on_treeButton_clicked()
{
    if (!ptree) {
        ptree = new plantTree(nullptr);
        connect(ptree, &plantTree::treeWindowClosed, this, [this]() {
            ptree = nullptr;
        });

        connect(ptree, &plantTree::windowClosing, this, &MainWindow::onTreeWindowClosing);

        connect(ptree, &plantTree::notInterrupt, this, &MainWindow::notDied);
        ptree->closeflag = closeflag;  // 设置 closeflag
        qDebug()<<"closeflag="<<ptree->closeflag<<Qt::endl;
        ptree->show();
    }
}

void MainWindow::onTreeWindowClosing() {
    closeflag = 1;
}

void MainWindow::notDied() {
    closeflag = 0;
}

void MainWindow::on_page4_Button_clicked()
{
    if (!frst) {
        frst = new forest(this);
        connect(frst, &forest::forestClosed, this, [this]() {
            frst = nullptr;
        });
        frst->move(180,0);
        frst->show();
    }
}

void MainWindow::on_page3_Button_clicked()
{
    MySchedule *newschedule = new MySchedule();
    newschedule->move(180, 0);
    newschedule->show();
}

void MainWindow::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
        case QSystemTrayIcon::Trigger:
            break;
        case QSystemTrayIcon::DoubleClick:
            if (this->isVisible() == false)
                this->show();
            break;
        default:
            break;
    }
}
