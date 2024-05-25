#include "planttree.h"
#include "ui_planttree.h"
#include <QGuiApplication>
#include <QScreen>
#include <QCloseEvent>
#include <QDebug>



plantTree::plantTree(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::plantTree)
    , timer(new QTimer(this))
    , countdownLabel(new QLabel(this))
    , timeComboBox(new QComboBox(this))
    , countdownTime(0)
    , elapsedSeconds(0)
{
    ui->setupUi(this);

    setWindowTitle("Plant Tree");

    // 初始化树的图片
    treePixmap = QPixmap(":/img/tree1.png");  // 默认显示第一种树
    currentTreeIndex = 1;  // 默认树的索引为1

    // 设置倒计时选择框
    for (int i = 10; i <= 180; i += 10) {
        timeComboBox->addItem(QString("%1 分钟").arg(i), i * 60);  // 以秒为单位存储
    }
    ui->verticalLayout_3->addWidget(timeComboBox);
    timeComboBox->hide();  // 初始化时隐藏

    // 设置倒计时标签
    countdownLabel->setAlignment(Qt::AlignCenter);
    ui->verticalLayout_3->addWidget(countdownLabel);
    countdownLabel->hide();  // 初始化时隐藏


    connect(timer, &QTimer::timeout, this, &plantTree::updateCountdown);


    ui->treeLabel->setPixmap(treePixmap);
    ui->treeLabel->setAlignment(Qt::AlignCenter);
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
    this->resize(300, 330);
    this->move(QGuiApplication::primaryScreen()->geometry().width() - 330, 30);
    //updateMatters();
    //ui->timeLabel->setText(QDate::currentDate().toString("MMM d, ddd"));
    QWidget::showEvent(event);
}


void plantTree::on_lefttree_clicked()
{
    // 切换到左边的树
    if (currentTreeIndex > 1) {
        currentTreeIndex--;
        treePixmap = QPixmap(QString(":/img/tree%1.png").arg(currentTreeIndex));
        updateTreeLabel();
    }else{
        currentTreeIndex=4;
        treePixmap = QPixmap(QString(":/img/tree%1.png").arg(currentTreeIndex));
        updateTreeLabel();
    }
}

void plantTree::on_righttree_clicked()
{
    // 切换到右边的树
    if (currentTreeIndex < 4) {
        currentTreeIndex++;
        treePixmap = QPixmap(QString(":/img/tree%1.png").arg(currentTreeIndex));
        updateTreeLabel();
    }else{
        currentTreeIndex=1;
        treePixmap = QPixmap(QString(":/img/tree%1.png").arg(currentTreeIndex));
        updateTreeLabel();
    }
}
void plantTree::updateTreeLabel()
{
    ui->treeLabel->setPixmap(treePixmap);
}

void plantTree::on_startButton_clicked()
{
    // 显示倒计时选择框
    timeComboBox->show();
    countdownLabel->hide();

    // 禁用 startButton 以防止再次点击
    ui->startButton->setEnabled(false);
    ui->lefttree->setEnabled(false);
    ui->righttree->setEnabled(false);

    // 连接选择框的信号槽，用户选择时间后启动倒计时
    connect(timeComboBox, QOverload<int>::of(&QComboBox::activated), this, &plantTree::startCountdown);
}

void plantTree::startCountdown(int index)
{
    countdownTime = timeComboBox->itemData(index).toInt();
    elapsedSeconds = 0;

    // 隐藏倒计时选择框并显示倒计时标签
    timeComboBox->hide();
    countdownLabel->show();
    ui->treeLabel->setPixmap(QPixmap(":/img/stage1.png"));  // 显示第一阶段图片

    // 更改 startButton 文本
    ui->startButton->setText("加油吧！");
    timer->start(1000);  // 每秒触发一次
}

void plantTree::updateCountdown()
{
    elapsedSeconds++;

    int remainingSeconds = countdownTime - elapsedSeconds;
    int minutes = remainingSeconds / 60;
    int seconds = remainingSeconds % 60;

    countdownLabel->setText(QString("%1:%2").arg(minutes, 2, 10, QLatin1Char('0')).arg(seconds, 2, 10, QLatin1Char('0')));

    if (elapsedSeconds >= countdownTime) {
        timer->stop();
        ui->treeLabel->setPixmap(treePixmap);  // 倒计时结束，显示最终树
        resetUI();
    } else if (elapsedSeconds >= countdownTime * 2 / 3) {
        ui->treeLabel->setPixmap(QPixmap(":/img/stage3.png"));  // 显示第三阶段图片
    } else if (elapsedSeconds >= countdownTime / 3) {
        ui->treeLabel->setPixmap(QPixmap(":/img/stage2.png"));  // 显示第二阶段图片
    }
}



void plantTree::resetUI()
{
    ui->startButton->setEnabled(true);
    ui->startButton->show();
    countdownLabel->hide();
    timeComboBox->setEnabled(true);
    ui->startButton->setText("种下一颗思绪之种");
}
