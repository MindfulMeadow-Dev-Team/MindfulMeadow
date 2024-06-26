#include "treehandler.h"

TreeHandler::TreeHandler(QString dbName) {
    // If the connection is already here, there might be a problem.
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::database("qt_sql_default_connection");
        db.close();
        QSqlDatabase::removeDatabase("qt_sql_default_connection");
    }
    if (QSqlDatabase::contains("tree_db")) {
        qDebug() << "second database connection error\n";
        db = QSqlDatabase::database("tree_db");
    }
    else {
        db = QSqlDatabase::addDatabase("QSQLITE", "tree_db");
    }

    // Open the database.
    db.setDatabaseName(dbName);
    if (!db.open()) {
        qDebug() << "tree data base open unsuccessful" << Qt::endl;
    }
    else {
        qDebug() << "tree data base opened successfully\n";
    }

    // If the table doesn't exist, create one.
    qry = new QSqlQuery(db);
    qry->exec("select * from Trees limit 1");
    if (!qry->next()) {
        // Id type "integer primary key autoincrement"
        // as the unique code of each matter.
        qry->exec("CREATE TABLE Trees("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "date text, "
                  "type int, "
                  "isDead bool, "
                  "duration int)");
        qDebug() << "tree table created\n";
    } else {
        qDebug() << "tree table already exists\n";
    }
}

TreeHandler::~TreeHandler() {
    delete qry;
    db.close();
}

int TreeHandler::add(const Tree &tree) {
    qry->prepare("insert into Trees (date, type, isDead, duration)"
                 "values (?, ?, ?, ?)");
    qry->addBindValue(tree.getDate());
    qry->addBindValue(tree.getType());
    qry->addBindValue(tree.ifDead());
    qry->addBindValue(tree.getDuration());
    qry->exec();
    qry->exec("select last_insert_rowid()");
    qry->next();
    auto id = qry->value(0).toInt();
    qDebug() << "add a new tree which id = " << id << Qt::endl;
    return id;
}

QVector<Tree> TreeHandler::getTrees(const QDate &date) const {
    QVector<Tree> ret;
    qry->prepare("select date, type, isDead, duration "
                 "from Trees where date = ? order by id");
    qry->addBindValue(date.toString("yyyy-MM-dd"));
    qry->exec();
    while (qry->next()) {
        auto date = QDate::fromString(qry->value(0).toString(), "yyyy-MM-dd");
        auto type = qry->value(1).toInt();
        auto isDead = qry->value(2).toBool();
        auto duration = qry->value(3).toInt();
        auto tree = Tree(date, type, isDead, duration);
        ret.append(tree);
    }
    qDebug() << "acquire trees where date = " << date.toString("yyyy-MM-dd") << Qt::endl;
    return ret;
}

QVector<Tree> TreeHandler::getTrees(const QDate &from, const QDate& to) const {
    qDebug() << from << to;
    QVector<Tree> ret;
    qry->prepare("select date, type, isDead, duration "
                 "from Trees where date >= ? and date <= ? order by date, id");
    qry->addBindValue(from.toString("yyyy-MM-dd"));
    qry->addBindValue(to.toString("yyyy-MM-dd"));
    qry->exec();
    while (qry->next()) {
        auto date = QDate::fromString(qry->value(0).toString(), "yyyy-MM-dd");
        auto type = qry->value(1).toInt();
        auto isDead = qry->value(2).toBool();
        auto duration = qry->value(3).toInt();
        auto tree = Tree(date, type, isDead, duration);
        ret.append(tree);
    }
    qDebug() << "acquire trees from  " << from.toString("yyyy-MM-dd") << " to " << to.toString("yyyy-MM-dd") << Qt::endl;
    return ret;
}

QVector<Tree> TreeHandler::getTrees(int n) const {
    QVector<Tree> ret;
    qry->prepare("select date, type, isDead, duration from (select * "
                 "from Trees order by -id limit ?) order by id");
    qry->addBindValue(n);
    qry->exec();
    while (qry->next()) {
        auto date = QDate::fromString(qry->value(0).toString(), "yyyy-MM-dd");
        auto type = qry->value(1).toInt();
        auto isDead = qry->value(2).toBool();
        auto duration = qry->value(3).toInt();
        auto tree = Tree(date, type, isDead, duration);
        ret.append(tree);
    }
    qDebug() << "acquire " << n << " trees";
    return ret;
}
