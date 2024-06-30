#ifndef TREEDETAILS_H
#define TREEDETAILS_H

#include <QDialog>
#include "treehandler.h"

namespace Ui {
class treeDetails; // 确保这里的类名与 ui_treedetails.h 中的一致
}

class TreeDetails : public QDialog // 修改类名为 TreeDetails
{
    Q_OBJECT

public:
    explicit TreeDetails(TreeHandler* handler, QWidget *parent = nullptr);
    ~TreeDetails();

private:
    Ui::treeDetails *ui; // 修改类名为 Ui::treeDetails
    TreeHandler* handler;

    void displayRecords();
};

#endif // TREEDETAILS_H
