
#ifndef TREE_H
#define TREE_H

#include <QDate>

class Tree
{
    // In which day the tree is planted.
    QDate date;
    // Tree type.
    int type;
    // whether the tree is dead or not
    bool isDead;

public:
    Tree() = default;
    Tree(const QDate&, int, bool);
    int getType() const;
    QDate getDate() const;
    bool ifDead() const;
};

#endif // TREE_H
