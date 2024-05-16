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
                  "tag text)");
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
    qry->prepare("select name, description, date, tag from Matters where id = ?");
    qry->addBindValue(id);
    qry->exec();
    qry->next();
    auto name = qry->value(0).toString();
    auto description = qry->value(1).toString();
    auto date = QDate::fromString(qry->value(2).toString());
    auto tag = qry->value(3).toString();
    auto matter = Matter(name, description, date, tag);

    qDebug() << "query data where id = " << id << Qt::endl;
    return matter;
}

QVector<Matter> MatterHandler::getMatters(QDate date) const {
    QVector<Matter> ret;
    qry->prepare("select name, description, date, tag from Matters where date = ?");
    qry->addBindValue(date.toString());
    qry->exec();
    while (qry->next()) {
        auto name = qry->value(0).toString();
        auto description = qry->value(1).toString();
        auto date = QDate::fromString(qry->value(2).toString());
        auto tag = qry->value(3).toString();
        auto matter = Matter(name, description, date, tag);
        ret.append(matter);
    }
    qDebug() << "query data where date = " << date.toString() << Qt::endl;
    return ret;
}

int MatterHandler::addNew(const Matter &matter) {
    qry->prepare("insert into Matters (name, description, date, tag)"
                "values (:name, :des, :date, :tag)");
    qry->bindValue(":name", matter.name);
    qry->bindValue(":des", matter.description);
    qry->bindValue(":date", matter.date.toString());
    qry->bindValue(":tag", matter.tag);
    qry->exec();
    qry->exec("select last_insert_rowid()");
    qry->next();
    auto id = qry->value(0).toInt();
    qDebug() << "add a new schedule which id = " << id << Qt::endl;
    return id;
}

void MatterHandler::updateMatter(int id, const Matter& matter) {
    qry->prepare("update Matters set name = ?, description = ?, date = ?, tag = ? where id = ?");
    qry->addBindValue(matter.name);
    qry->addBindValue(matter.description);
    qry->addBindValue(matter.date.toString());
    qry->addBindValue(matter.tag);
    qry->addBindValue(id);
    qry->exec();

    qDebug() << "update data which id = " << id << Qt::endl;
}
