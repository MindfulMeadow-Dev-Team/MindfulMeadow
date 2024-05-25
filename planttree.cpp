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

    // 初始化树的图片
    treePixmap = QPixmap(":/img/tree1.png");  // 默认显示第一种树
    currentTreeIndex = 1;  // 默认树的索引为1


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
    this->resize(300, 300);
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
    }
}

void plantTree::on_righttree_clicked()
{
    // 切换到右边的树
    if (currentTreeIndex < 4) {
        currentTreeIndex++;
        treePixmap = QPixmap(QString(":/img/tree%1.png").arg(currentTreeIndex));
        updateTreeLabel();
    }
}
void plantTree::updateTreeLabel()
{
    ui->treeLabel->setPixmap(treePixmap);
}

