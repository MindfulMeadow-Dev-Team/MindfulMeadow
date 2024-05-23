#include "minischedule.h"
#include "ui_minischedule.h"

MiniSchedule::MiniSchedule(MatterHandler* handler, QWidget* mainWindow, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MiniSchedule)
    , handler{handler}
    , mainWindow(mainWindow)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::WindowCloseButtonHint);
    ui->timeLabel->setText(QDate::currentDate().toString("MMM d, ddd"));
    ui->scrollArea->widget()->setLayout(new QVBoxLayout());
    ui->scrollArea->horizontalScrollBar()->hide();
    updateMatters();
}

MiniSchedule::~MiniSchedule()
{
    delete ui;
    // DO NOT delete handler!
}

void MiniSchedule::on_maxBtn_clicked()
{
    this->close();
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
    layout->setSpacing(10);
    while (layout->count()) {
        auto widget = layout->itemAt(0)->widget();
        widget->setParent(nullptr);
        layout->removeWidget(widget);
        delete widget;
    }
    for (int i = 0; i < size; ++i) {
        MatterBox* box = new MatterBox(matters[i], ids[i], 2, handler);
        layout->addWidget(box);
    }
    ui->scrollArea->verticalScrollBar()->setValue(0);
}

void MiniSchedule::closeEvent(QCloseEvent *event) {
    mainWindow->show();
    this->close();
}

void MiniSchedule::showEvent(QShowEvent *event) {
    qDebug() << QGuiApplication::primaryScreen()->geometry();
    this->move(QGuiApplication::primaryScreen()->geometry().width() - 330, 30);
    updateMatters();
}
