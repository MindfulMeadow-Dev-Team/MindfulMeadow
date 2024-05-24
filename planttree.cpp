#include "planttree.h"
#include "ui_planttree.h"

plantTree::plantTree(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::plantTree)
{
    ui->setupUi(this);

    setWindowTitle("Plant Tree");
}

plantTree::~plantTree()
{
    delete ui;
}
