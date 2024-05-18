#ifndef MATTERHANDLER_H
#define MATTERHANDLER_H

#include <QString>
#include <QFile>
#include <QVector>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include "matter.h"

class MatterHandler
{
    QSqlDatabase db;
    QSqlQuery *qry;
public:
    MatterHandler(QString dbName);
    ~MatterHandler();

    std::pair<QVector<Matter>, QVector<int>> getMatters(QDate date) const;
    Matter getSingleMatter(int id) const;
    // Add a new matter into the database and return the id.
    int addNew(const Matter& matter);
    void updateMatter(int id, const Matter& matter);
    void deleteMatter(int id);
};

#endif // MATTERHANDLER_H
