#include "matterhandler.h"

MatterHandler::MatterHandler(QString dbName) {
    // If the connection is already here, there might be a problem.
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        qDebug() << "second database connection error\n";
        db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else {
        db = QSqlDatabase::addDatabase("QSQLITE");
    }

    // Open the database.
    db.setDatabaseName(dbName);
    if (!db.open()) {
        qDebug() << "data base open unsuccessful" << Qt::endl;
    }
    else {
        qDebug() << "data base opened successfully\n";
    }

    // If the table doesn't exist, create one.
    qry = new QSqlQuery(db);
    qry->exec("select * from Matters limit 1");
    if (!qry->next()) {
        // Id type "integer primary key autoincrement"
        // as the unique code of each matter.
        qry->exec("CREATE TABLE Matters("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "name text, "
                  "description text, "
                  "date text,"
                  "tag text,"
                  "isDone bool, "
                  "setDue bool, "
                  "dueTime text)");
        qDebug() << "table created\n";
    } else {
        qDebug() << "table already exists\n";
    }
}

MatterHandler::~MatterHandler() {
    delete qry;
    db.close();
}

// Acquire a single matter from the table with the matter's id.
Matter MatterHandler::getSingleMatter(int id) const {
    qry->prepare("select name, description, date, tag, isDone, setDue, dueTime from Matters where id = ?");
    qry->addBindValue(id);
    qry->exec();
    qry->next();
    auto name = qry->value(0).toString();
    auto description = qry->value(1).toString();
    auto date = QDate::fromString(qry->value(2).toString(), "yyyy-MM-dd");
    auto tag = qry->value(3).toString();
    auto isDone = qry->value(4).toBool();
    auto setDue = qry->value(5).toBool();
    auto dueTime = QTime::fromString(qry->value(6).toString());
    auto matter = Matter(name, description, date, tag, isDone, setDue, dueTime);

    qDebug() << "query data where id = " << id << Qt::endl;
    return matter;
}

// Acquire all the matters on the day.
// Return: {vector of the matters, vector of the ids}
std::pair<QVector<Matter>, QVector<int>> MatterHandler::getMatters(const QDate& date) const {
    QVector<Matter> ret;
    QVector<int> ids;
    qry->prepare("select name, description, date, tag, isDone, id, setDue, dueTime "
                 "from Matters where date = ? order by isDone, - setDue, time(dueTime), - id");
    qry->addBindValue(date.toString("yyyy-MM-dd"));
    qry->exec();
    while (qry->next()) {
        auto name = qry->value(0).toString();
        auto description = qry->value(1).toString();
        auto date = QDate::fromString(qry->value(2).toString(), "yyyy-MM-dd");
        auto tag = qry->value(3).toString();
        auto isDone = qry->value(4).toBool();
        auto id = qry->value(5).toInt();
        auto setDue = qry->value(6).toBool();
        auto dueTime = QTime::fromString(qry->value(7).toString());
        auto matter = Matter(name, description, date, tag, isDone, setDue, dueTime);
        ret.append(matter);
        ids.append(id);
    }
    qDebug() << "query data where date = " << date.toString("yyyy-MM-dd") << Qt::endl;
    return {ret, ids};
}

// Acquire all the matters that is overdue
// and the ones that are on the day and nday days after the day
std::pair<QVector<Matter>, QVector<int>> MatterHandler::getMattersSince(const QDate& date, int nday) const {
    QVector<Matter> ret;
    QVector<int> ids;
    // Matters before the day that are not done.
    qry->prepare("select name, description, date, tag, isDone, id, setDue, dueTime "
                 "from Matters where date(date) < ? and isDone = 0 order by date(date), dueTime");
    qry->addBindValue(date.toString("yyyy-MM-dd"));
    qry->exec();
    while (qry->next()) {
        auto name = qry->value(0).toString();
        auto description = qry->value(1).toString();
        auto date = QDate::fromString(qry->value(2).toString(), "yyyy-MM-dd");
        auto tag = qry->value(3).toString();
        auto isDone = qry->value(4).toBool();
        auto id = qry->value(5).toInt();
        auto setDue = qry->value(6).toBool();
        auto dueTime = QTime::fromString(qry->value(7).toString());
        auto matter = Matter(name, description, date, tag, isDone, setDue, dueTime);
        ret.append(matter);
        ids.append(id);
    }
    // Matters after the day
    qry->prepare("select name, description, date, tag, isDone, id, setDue, dueTime "
                 "from Matters where date >= ? and date <= ? order by date, isDone, - setDue, time(dueTime), - id");
    qry->addBindValue(date.toString("yyyy-MM-dd"));
    qry->addBindValue(date.addDays(nday).toString("yyyy-MM-dd"));
    qry->exec();
    while (qry->next()) {
        auto name = qry->value(0).toString();
        auto description = qry->value(1).toString();
        auto date = QDate::fromString(qry->value(2).toString(), "yyyy-MM-dd");
        auto tag = qry->value(3).toString();
        auto isDone = qry->value(4).toBool();
        auto id = qry->value(5).toInt();
        auto setDue = qry->value(6).toBool();
        auto dueTime = QTime::fromString(qry->value(7).toString());
        auto matter = Matter(name, description, date, tag, isDone, setDue, dueTime);
        ret.append(matter);
        ids.append(id);
    }
    qDebug() << "query data since date =  " << date.toString("yyyy-MM-dd") << Qt::endl;
    qDebug() << ret.size();
    return {ret, ids};
}

// Insert a new matter into the table.
// Return the id of it.
int MatterHandler::addNew(const Matter &matter) {
    qry->prepare("insert into Matters (name, description, date, tag, isDone, setDue, dueTime)"
                "values (?, ?, ?, ?, ?, ?, ?)");
    qry->addBindValue(matter.name);
    qry->addBindValue(matter.description);
    qry->addBindValue(matter.date.toString("yyyy-MM-dd"));
    qry->addBindValue(matter.tag);
    qry->addBindValue(matter.isDone);
    qry->addBindValue(matter.setDue);
    qry->addBindValue(matter.dueTime);
    qry->exec();
    qry->exec("select last_insert_rowid()");
    qry->next();
    auto id = qry->value(0).toInt();
    qDebug() << "add a new schedule which id = " << id << Qt::endl;
    return id;
}

// Update informations.
void MatterHandler::updateMatter(int id, const Matter& matter) {
    qry->prepare("update Matters set name = ?, description = ?, date = ?, tag = ?"
                 ", isDone = ?, setDue = ?, dueTime = ? where id = ?");
    qry->addBindValue(matter.name);
    qry->addBindValue(matter.description);
    qry->addBindValue(matter.date.toString("yyyy-MM-dd"));
    qry->addBindValue(matter.tag);
    qry->addBindValue(matter.isDone);
    qry->addBindValue(matter.setDue);
    qry->addBindValue(matter.dueTime);
    qry->addBindValue(id);
    qry->exec();

    qDebug() << "update data which id = " << id << Qt::endl;
}

// Delete one.
void MatterHandler::deleteMatter(int id) {
    qry->prepare("delete from Matters where id = ?");
    qry->addBindValue(id);
    qry->exec();
    qDebug() << "delete a matter with id " << id << Qt::endl;
}
