#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include "tree.h"
#include "treehandler.h"
#include <memory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    auto handler = std::make_unique<TreeHandler>("trees.db");
    // for (int i = 0; i < 10; ++i) {
    //     handler->add(Tree(QDate::currentDate(), i, 0));
    // }
    // qDebug() << QDate::fromString("2024-5-29", "yyyy-M-dd");
    // for (int i = 0; i < 10; ++i) {
    //     handler->add(Tree(QDate::fromString("2024-5-29", "yyyy-M-dd"), i, 1));
    // }

    auto trees = handler->getTrees(QDate::currentDate());
    for (auto tree: trees) {
        qDebug() << tree.getDate() << tree.getType() << ' ' << tree.ifDead();
    }
    qDebug() << Qt::endl;


    auto trees2 = handler->getTrees(QDate::fromString("2024-5-29", "yyyy-M-dd"), QDate::currentDate());
    for (auto tree: trees2) {
        qDebug() << tree.getDate() << tree.getType() << ' ' << tree.ifDead();
    }
    qDebug() << Qt::endl;

    auto trees3 = handler->getTrees(8);
    for (auto tree: trees3) {
        qDebug() << tree.getDate() << tree.getType() << ' ' << tree.ifDead();
    }
    qDebug() << Qt::endl;

    return a.exec();
}
