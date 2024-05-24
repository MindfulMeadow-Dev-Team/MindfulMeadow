#ifndef PLANTTREE_H
#define PLANTTREE_H

#include <QWidget>

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
};

#endif // PLANTTREE_H
