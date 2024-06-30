
#include "tree.h"

Tree::Tree(const QDate & date, int type, bool isDead, int duration)
    : date{date}, type{type}, isDead{isDead}, duration{duration} { }

QDate Tree::getDate() const {
    return date;
}

int Tree::getType() const {
    return type;
}

bool Tree::ifDead() const {
    return isDead;
}

int Tree::getDuration() const {
    return duration;
}
