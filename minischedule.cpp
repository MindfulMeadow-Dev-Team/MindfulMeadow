#include "minischedule.h"
#include "ui_minischedule.h"

MiniSchedule::MiniSchedule(MatterHandler* handler, QWidget* mainWindow, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MiniSchedule)
    , handler{handler}
    , mainWindow(mainWindow)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::WindowCloseButtonHint | Qt::SubWindow);
    ui->timeLabel->setText(QDate::currentDate().toString("MMM d, ddd"));
    ui->scrollArea->widget()->setLayout(new QVBoxLayout());
    ui->scrollArea->horizontalScrollBar()->hide();
    ui->scrollArea->widget()->layout()->setContentsMargins(0, 10, 10, 10);
    ui->scrollArea->widget()->layout()->setSpacing(0);
    ui->scrollArea->widget()->layout()->setAlignment(Qt::AlignTop);
    ui->scrollArea->widget()->setObjectName("scrollAreaContent");
    updateMatters();
}

MiniSchedule::~MiniSchedule()
{
    delete ui;
    // DO NOT delete handler!
}

void MiniSchedule::on_maxBtn_clicked()
{
    this->hide();
    mainWindow->show();
}

void MiniSchedule::updateMatters() {
    auto [matters, ids] = handler->getMatters(QDate::currentDate());
    int size = matters.size();
    auto layout = ui->scrollArea->widget()->layout();
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
        ui->scrollArea->widget()->setStyleSheet("QWidget#scrollAreaContent {background-image: url(:/icon/res/img/miniNoMatter.png);background-size: cover;background-position: center center; background-size: 100px;}");
        return;
    }
    for (int i = 0; i < size; ++i) {
        MatterBox* box = new MatterBox(matters[i], ids[i], 2, handler);
        layout->addWidget(box);
    }
    ui->scrollArea->widget()->setStyleSheet("");
    ui->scrollArea->verticalScrollBar()->setValue(0);
}

void MiniSchedule::closeEvent(QCloseEvent *event) {
    mainWindow->show();
    this->hide();
    QWidget::closeEvent(event);
}

void MiniSchedule::showEvent(QShowEvent *event) {
    qDebug() << QGuiApplication::primaryScreen()->geometry();
    this->resize(300, 300);
    this->move(QGuiApplication::primaryScreen()->geometry().width() - 330, 30);
    updateMatters();
    ui->timeLabel->setText(QDate::currentDate().toString("MMM d, ddd"));
    QWidget::showEvent(event);
}
