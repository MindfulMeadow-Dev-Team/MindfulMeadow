#include "mainwindow.h"
#include "matter.h"
#include "matterhandler.h"

#include <QApplication>
#include <QDebug>
#include <memory>
#include <windows.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // MatterHandler handler("data.db");
    // handler.addNew(Matter());
    // handler.addNew(Matter());
    // handler.addNew(Matter());
    // handler.addNew(Matter());
    // handler.addNew(Matter());
    // auto matters = handler.getMatters(QDate::currentDate());
    // qDebug() << matters.size() << Qt::endl;

    return a.exec();
}
