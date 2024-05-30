
#include "tree.h"

Tree::Tree(const QDate & date, int type, bool isDead)
    : date{date}, type{type}, isDead{isDead} { }

QDate Tree::getDate() const {
    return date;
}

int Tree::getType() const {
    return type;
}

bool Tree::ifDead() const {
    return isDead;
}
