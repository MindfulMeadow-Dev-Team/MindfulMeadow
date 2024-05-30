
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

    return a.exec();
}
