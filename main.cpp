
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

<<<<<<< HEAD
<<<<<<< HEAD
    /*auto handler = std::make_unique<TreeHandler>("trees.db");
    // for (int i = 0; i < 10; ++i) {
    //     handler->add(Tree(QDate::currentDate(), i, 0));
    // }
    // qDebug() << QDate::fromString("2024-5-29", "yyyy-M-dd");
    // for (int i = 0; i < 10; ++i) {
    //     handler->add(Tree(QDate::fromString("2024-5-29", "yyyy-M-dd"), i, 1));
    // }
=======
=======
>>>>>>> e9013314bd6c58654ee0aaa1ad4e25d17ca3f8b6
    auto handler = std::make_unique<TreeHandler>("trees.db");
    for (int i = 0; i < 10; ++i) {
        handler->add(Tree(QDate::currentDate(), i, 0, i));
    }
    qDebug() << QDate::fromString("2024-5-29", "yyyy-M-dd");
    for (int i = 0; i < 10; ++i) {
        handler->add(Tree(QDate::fromString("2024-5-29", "yyyy-M-dd"), i, 1, i));
    }
<<<<<<< HEAD
>>>>>>> dev
=======
>>>>>>> e9013314bd6c58654ee0aaa1ad4e25d17ca3f8b6

    auto trees = handler->getTrees(QDate::currentDate());
    for (auto tree: trees) {
        qDebug() << tree.getDate() << tree.getType() << ' ' << tree.ifDead() << ' ' << tree.getDuration();
    }
    qDebug() << Qt::endl;
<<<<<<< HEAD
*/
=======

>>>>>>> e9013314bd6c58654ee0aaa1ad4e25d17ca3f8b6
    return a.exec();
}
