#include "treedetails.h"
#include "ui_treedetails.h"

TreeDetails::TreeDetails(TreeHandler* handler, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::treeDetails),
    handler(new TreeHandler("tree.db"))
{
    ui->setupUi(this);
    displayRecords();

}

TreeDetails::~TreeDetails()
{
    delete ui;
}

void TreeDetails::displayRecords()
{
    QVector<Tree> trees = handler->getTrees(30);  // 获取前30棵树

    qDebug() << "Number of trees retrieved:" << trees.size();
    ui->listWidget->clear();
    int lineNumber = 1;
    for (const Tree& tree : trees) {
        QString treeTypeString;
        switch (tree.getType()) {
        case 1:
            treeTypeString = "绿冠";
            break;
        case 2:
            treeTypeString = "花树";
            break;
        case 3:
            treeTypeString = "果树";
            break;
        case 4:
            treeTypeString = "粉冠";
            break;
        default:
            treeTypeString = QString("未知类型 (%1)").arg(tree.getType());
            break;
        }

        QString statusString = tree.ifDead() ? "已枯萎" : QString("生长时长: %1分钟").arg(tree.getDuration()/60);

        QString record = QString("%1.  种树日期: %2,    树种: %3,    %4")
                             .arg(lineNumber)
                             .arg(tree.getDate().toString("yyyy-MM-dd"))
                             .arg(treeTypeString)
                             .arg(statusString);

        ui->listWidget->addItem(record);

        ++lineNumber;
    }
}
