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
    , isCountdownActive(false)
    , thandler("tree.db")
{
    ui->setupUi(this);
    qDebug()<<"初始化"<<closeflag<<Qt::endl;
    setWindowTitle("Plant Tree");
    // ui->startButton->setStyleSheet("QPushButton {\n	border-radius: 5px; \n	background-color: #c4dae2; \n	border-style: none;\n	color: #333333;\n}\nQPushButton:hover{\n    background-color: #9cb2c7;\n}\nQPushButton:pressed{\n    background-color: #e9edee;\n}");
    /*if(closeflag){
        treePixmap = QPixmap(":/img/died.png");
        ui->treeLabel->setPixmap(treePixmap);
        ui->startButton->setText("思绪之苗枯死了...");
        currentTreeIndex = 1;  // 默认树的索引为1

    }else{
    // 初始化树的图片
        treePixmap = QPixmap(":/img/tree1.png");  // 默认显示第一种树
        currentTreeIndex = 1;  // 默认树的索引为1
        ui->treeLabel->setPixmap(treePixmap);
        ui->startButton->setText("种下一颗思绪之种");
    }*/

    // 设置倒计时选择框

    timeComboBox->addItem("取消", 0);  // 添加取消选项
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


    ui->treeLabel->setAlignment(Qt::AlignCenter);
}

plantTree::~plantTree()
{
    delete ui;
}


void plantTree::closeEvent(QCloseEvent *event) {

    if(isCountdownActive){QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "关闭窗口", "确定要关闭吗？", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        //closeflag=1;

        // 存储取消种树的信息到数据库
        QDate currentDate = QDate::currentDate();
        Tree canceledTree(currentDate, currentTreeIndex, true,0);  // true 表示树已经死了

        // 添加到数据库
        int treeId = thandler.add(canceledTree);

        qDebug() << "Canceled planting tree with ID:" << treeId;
        emit windowClosing();
        emit treeWindowClosed();  // 发出 treeWindowClosed 信号
        QWidget::closeEvent(event);
    }else{
        event->ignore();
    }}
    else{
        emit notInterrupt();
        emit treeWindowClosed();  // 发出 treeWindowClosed 信号
        QWidget::closeEvent(event);
    }
}

void plantTree::showEvent(QShowEvent *event) {
    qDebug() << QGuiApplication::primaryScreen()->geometry();
    this->resize(300, 330);
    this->move(QGuiApplication::primaryScreen()->geometry().width() - 330, 30);
    //updateMatters();
    //ui->timeLabel->setText(QDate::currentDate().toString("MMM d, ddd"));
    if (closeflag==1) {
        treePixmap = QPixmap(":/img/died.png");
        ui->treeLabel->setPixmap(treePixmap);
        ui->startButton->setText("思绪之苗枯死了...");
        currentTreeIndex = 1;  // 默认树的索引为1
    } else if(closeflag==0){
        treePixmap = QPixmap(":/img/tree1.png");  // 默认显示第一种树
        currentTreeIndex = 1;  // 默认树的索引为1
        ui->treeLabel->setPixmap(treePixmap);
        ui->startButton->setText("种下一颗思绪之种");
    }
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
    if (ui->startButton->text() == "种下一颗思绪之种") {
        // 显示倒计时选择框
        timeComboBox->show();
        countdownLabel->hide();

        // 禁用 startButton 以防止再次点击
        ui->lefttree->setEnabled(false);
        ui->righttree->setEnabled(false);

        // 连接选择框的信号槽，用户选择时间后启动倒计时
        connect(timeComboBox, QOverload<int>::of(&QComboBox::activated), this, &plantTree::startCountdown);
    } else if (ui->startButton->text() == "放弃") {
        // 显示确认对话框
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "放弃倒计时", "确定要放弃小苗吗？", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            cancelCountdown();
        }
    } else if (ui->startButton->text() == "思绪之苗枯死了...") {
        treePixmap = QPixmap(QString(":/img/tree%1.png").arg(currentTreeIndex));

        resetUI();
    }else if(ui->startButton->text() == "思绪之树长大啦") {
        resetUI();
    }
}
void plantTree::startCountdown(int index)
{
    countdownTime = timeComboBox->itemData(index).toInt();
    elapsedSeconds = 0;

    isCountdownActive = true;  // 标记倒计时开始

    if (countdownTime == 0) {
        // 取消选择，恢复UI
        resetUI();
        return;
    }

    timeComboBox->hide();
    countdownLabel->show();
    ui->treeLabel->setPixmap(QPixmap(":/img/stage1.png"));

    // 更改 startButton 文本
    ui->startButton->setText("放弃");
    timer->start(1000);
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
        isCountdownActive = false;
        ui->treeLabel->setPixmap(treePixmap);  // 倒计时结束，显示最终树

        // 存储成功种树的信息到数据库
        QDate currentDate = QDate::currentDate();
        Tree plantedTree(currentDate, currentTreeIndex, false,countdownTime);  // false 表示树还活着

        // 添加到数据库
        int treeId = thandler.add(plantedTree);

        qDebug() << "Successfully planted tree with ID:" << treeId;
        ui->startButton->setText("思绪之树长大啦");
        //resetUI();
    } else if (elapsedSeconds >= countdownTime * 2 / 3) {
        ui->treeLabel->setPixmap(QPixmap(":/img/stage3.png"));  // 显示第三阶段图片
    } else if (elapsedSeconds >= countdownTime / 3) {
        ui->treeLabel->setPixmap(QPixmap(":/img/stage2.png"));  // 显示第二阶段图片
    }
}

void plantTree::cancelCountdown()
{
    timer->stop();
    isCountdownActive = false;  // 标记倒计时开始
    ui->treeLabel->setPixmap(QPixmap(":/img/died.png"));  // 显示枯树图片
    ui->startButton->setText("思绪之苗枯死了...");

    // 存储取消种树的信息到数据库
    QDate currentDate = QDate::currentDate();
    Tree canceledTree(currentDate, currentTreeIndex, true,0);  // true 表示树已经死了

    // 添加到数据库
    int treeId = thandler.add(canceledTree);

    qDebug() << "Canceled planting tree with ID:" << treeId;
}


void plantTree::resetUI()
{
    ui->startButton->setEnabled(true);
    closeflag=-1;
    ui->startButton->show();
    countdownLabel->hide();
    timeComboBox->setEnabled(true);
    ui->startButton->setText("种下一颗思绪之种");
    ui->treeLabel->setPixmap(treePixmap);  // 倒计时结束，显示最终树
    ui->lefttree->setEnabled(true);
    ui->righttree->setEnabled(true);
}
