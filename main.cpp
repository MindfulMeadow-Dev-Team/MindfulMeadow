#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include "tree.h"
#include "treehandler.h"
#include <memory>
<<<<<<< HEAD

=======
#include <windows.h>
>>>>>>> 25ddaa8f86ddbb61dd12adca040a91a77147a369
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
