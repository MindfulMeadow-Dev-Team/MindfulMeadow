#ifndef TREEHANDLER_H
#define TREEHANDLER_H

#include <QFile>
#include <QVector>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include "tree.h"

class TreeHandler
{
    QSqlDatabase db;
    QSqlQuery *qry;
public:
    TreeHandler(QString dbName);
    ~TreeHandler();

    // Add methods.
    // Add a newly planted tree to the database and return the id of it.
    int add(const Tree& tree);

    // Acquire methods.
    // Return all the trees that is planted on the date in the order of id ( i.e. the trees that was planted early will appear first in the vector ).
    QVector<Tree> getTrees(const QDate& date) const;
    // Return all the trees that is planted after date 'from' to the date 'to'.
    QVector<Tree> getTrees(const QDate &from, const QDate& to) const;
    // Return n trees that is planted most recently.
    QVector<Tree> getTrees(int n) const;
};

#endif // TREEHANDLER_H
