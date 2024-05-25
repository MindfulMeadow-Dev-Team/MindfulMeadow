#ifndef PLANTTREE_H
#define PLANTTREE_H

#include <QWidget>
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

private:
    Ui::plantTree *ui;
    QWidget* mainWindow;
    MatterHandler* handler;


private:
// override closeEvent to hide the window in windows tray
void closeEvent(QCloseEvent* event);
void showEvent(QShowEvent *event);
};

#endif // PLANTTREE_H
