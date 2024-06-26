#include "forest.h"
#include "ui_forest.h"
#include <QVector>
#include <QDebug>

forest::forest(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::forest)
    , thandler("tree.db")
{
    ui->setupUi(this);

    treelb_1 = ui->treelb_1;
    treelb_2 = ui->treelb_2;
    treelb_3 = ui->treelb_3;
    treelb_4 = ui->treelb_4;
    treelb_5 = ui->treelb_5;
    treelb_6 = ui->treelb_6;
    treelb_7 = ui->treelb_7;
    treelb_8 = ui->treelb_8;
    treelb_9 = ui->treelb_9;
    treelb_10 = ui->treelb_10;
    treelb_11 = ui->treelb_11;
    treelb_12 = ui->treelb_12;
    treelb_13 = ui->treelb_13;
    treelb_14 = ui->treelb_14;
    treelb_15 = ui->treelb_15;
    treelb_16 = ui->treelb_16;
    treelb_17 = ui->treelb_17;
    treelb_18 = ui->treelb_18;
    treelb_19 = ui->treelb_19;
    treelb_20 = ui->treelb_20;
    treelb_21 = ui->treelb_21;
    treelb_22 = ui->treelb_22;
    treelb_23 = ui->treelb_23;
    treelb_24 = ui->treelb_24;
    treelb_25 = ui->treelb_25;
    treelb_26 = ui->treelb_26;
    treelb_27 = ui->treelb_27;
    treelb_28 = ui->treelb_28;
    treelb_29 = ui->treelb_29;
    treelb_30 = ui->treelb_30;

    // 显示前30棵树的信息
    showFirstTree();
}

forest::~forest()
{
    delete ui;
    delete treelb_1;
    delete treelb_2;
    delete treelb_3;
    delete treelb_4;
    delete treelb_5;
    delete treelb_6;
    delete treelb_7;
    delete treelb_8;
    delete treelb_9;
    delete treelb_10;
    delete treelb_11;
    delete treelb_12;
    delete treelb_13;
    delete treelb_14;
    delete treelb_15;
    delete treelb_16;
    delete treelb_17;
    delete treelb_18;
    delete treelb_19;
    delete treelb_20;
    delete treelb_21;
    delete treelb_22;
    delete treelb_23;
    delete treelb_24;
    delete treelb_25;
    delete treelb_26;
    delete treelb_27;
    delete treelb_28;
    delete treelb_29;
    delete treelb_30;
}

void forest::showFirstTree()
{
    // 获取数据库中前30棵树的信息
    QVector<Tree> trees = thandler.getTrees(30);  // 获取前30棵树

    QLabel* labels[30] = {
        treelb_1, treelb_2, treelb_3, treelb_4, treelb_5,
        treelb_6, treelb_7, treelb_8, treelb_9, treelb_10,
        treelb_11, treelb_12, treelb_13, treelb_14, treelb_15,
        treelb_16, treelb_17, treelb_18, treelb_19, treelb_20,
        treelb_21, treelb_22, treelb_23, treelb_24, treelb_25,
        treelb_26, treelb_27, treelb_28, treelb_29, treelb_30
    };

    for (int i = 0; i < trees.size(); ++i) {
        Tree tree = trees[i];
        int treeType = tree.getType();
        bool isDead = tree.ifDead();

        if (isDead) {
            labels[i]->setPixmap(QPixmap(":/icon/res/img/died.png"));
        } else {
            QString imagePath = QString(":/icon/res/img/tree%1.png").arg(treeType);
            labels[i]->setPixmap(QPixmap(imagePath));
        }
        labels[i]->setScaledContents(true);  // 缩放图片以适应 QLabel 大小
        labels[i]->setAlignment(Qt::AlignCenter);
    }

    for (int i = trees.size(); i < 30; ++i) {
        // 如果树的数量少于30，显示默认的图片或者空白
        labels[i]->setText("");
    }
}

void forest::closeEvent(QCloseEvent *event) {
    emit forestClosed();  // 发出 forestClosed 信号
    QWidget::closeEvent(event);
}

void forest::on_pushButton_clicked()
{
    // 弹出种植记录对话框
    TreeDetails dialog(&thandler, this);
    dialog.exec();
}
