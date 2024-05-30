#ifndef FOREST_H
#define FOREST_H

#include <QWidget>
#include <QLabel>
#include "treehandler.h"
namespace Ui {
class forest;
}

class forest : public QWidget
{
    Q_OBJECT

public:
    explicit forest(QWidget *parent = nullptr);
    ~forest();

private:
    Ui::forest *ui;
    TreeHandler thandler;  // 树处理器，用于从数据库中获取树信息
    QLabel *treelb_1;
    QLabel *treelb_2;
    QLabel *treelb_3;
    QLabel *treelb_4;
    QLabel *treelb_5;
    QLabel *treelb_6;
    QLabel *treelb_7;
    QLabel *treelb_8;
    QLabel *treelb_9;
    QLabel *treelb_10;
    QLabel *treelb_11;
    QLabel *treelb_12;
    QLabel *treelb_13;
    QLabel *treelb_14;
    QLabel *treelb_15;
    QLabel *treelb_16;
    QLabel *treelb_17;
    QLabel *treelb_18;
    QLabel *treelb_19;
    QLabel *treelb_20;
    QLabel *treelb_21;
    QLabel *treelb_22;
    QLabel *treelb_23;
    QLabel *treelb_24;
    QLabel *treelb_25;
    QLabel *treelb_26;
    QLabel *treelb_27;
    QLabel *treelb_28;
    QLabel *treelb_29;
    QLabel *treelb_30;

    void closeEvent(QCloseEvent* event);


signals:
    void forestClosed();
private slots:
    void showFirstTree();  // 显示第一棵树
};

#endif // FOREST_H
