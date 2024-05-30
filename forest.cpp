#include "forest.h"
#include "ui_forest.h"

forest::forest(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::forest)
{
    ui->setupUi(this);
}

forest::~forest()
{
    delete ui;
}
