#ifndef TREEDETAILS_H
#define TREEDETAILS_H

#include <QDialog>
#include "treehandler.h"

namespace Ui {
class treeDetails;
}

class TreeDetails : public QDialog
{
    Q_OBJECT

public:
    explicit TreeDetails(TreeHandler* handler, QWidget *parent = nullptr);
    ~TreeDetails();

private:
    Ui::treeDetails *ui;
    TreeHandler* handler;


    void displayRecords();
};

#endif // TREEDETAILS_H
