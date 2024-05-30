#include "forest.h"
#include "ui_forest.h"
#include <QVector>

forest::forest(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::forest)
    , thandler("tree.db")
{
    ui->setupUi(this);

    // 初始化 QLabel，这里使用的是在 forest.ui 中设计好的 QLabel
    treelb_1 = ui->treelb_1;

    // 显示第一棵树的信息
    showFirstTree();
}

forest::~forest()
{
    delete ui;
}
void forest::showFirstTree()
{
    // 获取数据库中第一棵树的信息
    QVector<Tree> trees = thandler.getTrees(1);  // 获取最早的一棵树

    if (!trees.isEmpty()) {
        Tree firstTree = trees.first();

        // 根据树的 type 和 isDead 显示对应的图片
        int treeType = firstTree.getType();
        bool isDead = firstTree.ifDead();

        if (isDead) {
            treelb_1->setPixmap(QPixmap(":/img/died.png"));
        } else {
            QString imagePath = QString(":/img/tree%1.png").arg(treeType);
            treelb_1->setPixmap(QPixmap(imagePath));
        }

        treelb_1->setScaledContents(true);  // 缩放图片以适应 QLabel 大小
        treelb_1->setAlignment(Qt::AlignCenter);
    } else {
        // 如果没有树，显示默认的图片或者空白
        treelb_1->setText("No tree planted yet.");
    }
}
