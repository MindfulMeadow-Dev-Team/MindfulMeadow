#ifndef PLANTTREE_H
#define PLANTTREE_H

#include <QWidget>
#include <QPixmap>

#include "matterhandler.h"
#include "matterhandler.h"
namespace Ui {
class plantTree;
}

class plantTree : public QWidget
{
    Q_OBJECT

public:
    explicit plantTree(QWidget *parent = nullptr);
    ~plantTree();


private slots:
    void on_lefttree_clicked();

    void on_righttree_clicked();

private:
    Ui::plantTree *ui;
    QWidget* mainWindow;
    MatterHandler* handler;
    QPixmap treePixmap;  // 用于存储当前树的图片
    int currentTreeIndex;  // 当前显示的树的索引

    void updateTreeLabel();  // 更新显示树的 QLabel


private:
// override closeEvent to hide the window in windows tray
void closeEvent(QCloseEvent* event);
void showEvent(QShowEvent *event);
};

#endif // PLANTTREE_H
