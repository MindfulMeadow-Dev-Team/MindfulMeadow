#include "planttree.h"
#include "ui_planttree.h"
#include <QGuiApplication>
#include <QScreen>
#include <QCloseEvent>

plantTree::plantTree(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::plantTree)
{
    ui->setupUi(this);

    setWindowTitle("Plant Tree");
}

plantTree::~plantTree()
{
    delete ui;
}

/*void plantTree::closeEvent(QCloseEvent *event) {
    mainWindow->show();
    this->hide();
    QWidget::closeEvent(event);

}*/
void plantTree::closeEvent(QCloseEvent *event) {
    this->hide();  // 仅隐藏窗口，不关闭应用程序
    event->ignore();  // 忽略关闭事件
}


void plantTree::showEvent(QShowEvent *event) {
    qDebug() << QGuiApplication::primaryScreen()->geometry();
    this->resize(300, 300);
    this->move(QGuiApplication::primaryScreen()->geometry().width() - 330, 30);
    //updateMatters();
    //ui->timeLabel->setText(QDate::currentDate().toString("MMM d, ddd"));
    QWidget::showEvent(event);
}
