#ifndef PLANTTREE_H
#define PLANTTREE_H

#include <QWidget>
#include <QPixmap>
#include <QTimer>
#include <QComboBox>
#include <QLabel>
#include <QMessageBox>  // 添加此头文件以使用消息框

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

    void on_startButton_clicked();

    void updateCountdown();

    void cancelCountdown();  // 取消倒计时
private:
    Ui::plantTree *ui;
    QWidget* mainWindow;
    MatterHandler* handler;
    QPixmap treePixmap;  // 用于存储当前树的图片
    int currentTreeIndex;  // 当前显示的树的索引

    void updateTreeLabel();  // 更新显示树的 QLabel
    void startCountdown(int duration);
    void updateTreeStage();
    void resetUI();


    QTimer *timer;
    QLabel *countdownLabel;
    QComboBox *timeComboBox;


    int countdownTime;
    int elapsedSeconds;

private:
// override closeEvent to hide the window in windows tray
    void closeEvent(QCloseEvent* event);
    void showEvent(QShowEvent *event);
};

#endif // PLANTTREE_H
