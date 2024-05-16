#include "matterhandler.h"

MatterHandler::MatterHandler(QString dbName) {
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else {
        db = QSqlDatabase::addDatabase("QSQLITE");
    }

    db.setDatabaseName(dbName);
    if (!db.open()) {
        qDebug() << "data base open unsuccessful" << Qt::endl;
    }
    else {
        qDebug() << "data base opened successfully\n";
    }

    qry = new QSqlQuery(db);
    qry->exec("select * from Matters limit 1");
    if (!qry->next()) {
        qry->exec("CREATE TABLE Matters("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "name text, "
                  "description text, "
                  "date text,"
                  "tag text,"
                  "isDone bool)");
        qDebug() << "table created\n";
    } else {
        qDebug() << "table already exists\n";
    }
}

MatterHandler::~MatterHandler() {
    delete qry;
    db.close();
}

Matter MatterHandler::getSingleMatter(int id) const {
    qry->prepare("select name, description, date, tag, isDone from Matters where id = ?");
    qry->addBindValue(id);
    qry->exec();
    qry->next();
    auto name = qry->value(0).toString();
    auto description = qry->value(1).toString();
    auto date = QDate::fromString(qry->value(2).toString());
    auto tag = qry->value(3).toString();
    auto isDone = qry->value(4).toBool();
    auto matter = Matter(name, description, date, tag, isDone);

    qDebug() << "query data where id = " << id << Qt::endl;
    return matter;
}

std::pair<QVector<Matter>, QVector<int>> MatterHandler::getMatters(QDate date) const {
    QVector<Matter> ret;
    QVector<int> ids;
    qry->prepare("select name, description, date, tag, isDone, id from Matters where date = ?");
    qry->addBindValue(date.toString());
    qry->exec();
    while (qry->next()) {
        auto name = qry->value(0).toString();
        auto description = qry->value(1).toString();
        auto date = QDate::fromString(qry->value(2).toString());
        auto tag = qry->value(3).toString();
        auto isDone = qry->value(4).toBool();
        auto id = qry->value(5).toInt();
        auto matter = Matter(name, description, date, tag, isDone);
        ret.append(matter);
        ids.append(id);
    }
    qDebug() << "query data where date = " << date.toString() << Qt::endl;
    return {ret, ids};
}

int MatterHandler::addNew(const Matter &matter) {
    qry->prepare("insert into Matters (name, description, date, tag, isDone)"
                "values (:name, :des, :date, :tag, :isDone)");
    qry->bindValue(":name", matter.name);
    qry->bindValue(":des", matter.description);
    qry->bindValue(":date", matter.date.toString());
    qry->bindValue(":tag", matter.tag);
    qry->bindValue(":isDone", matter.isDone);
    qry->exec();
    qry->exec("select last_insert_rowid()");
    qry->next();
    auto id = qry->value(0).toInt();
    qDebug() << "add a new schedule which id = " << id << Qt::endl;
    return id;
}

void MatterHandler::updateMatter(int id, const Matter& matter) {
    qry->prepare("update Matters set name = ?, description = ?, date = ?, tag = ?, isDone = ? where id = ?");
    qry->addBindValue(matter.name);
    qry->addBindValue(matter.description);
    qry->addBindValue(matter.date.toString());
    qry->addBindValue(matter.tag);
    qry->addBindValue(matter.isDone);
    qry->addBindValue(id);
    qry->exec();

    qDebug() << "update data which id = " << id << Qt::endl;
}
