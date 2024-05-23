#ifndef MATTERBOX_H
#define MATTERBOX_H

#include <QWidget>
#include "matterhandler.h"
#include "mainwindow.h"

namespace Ui {
class MatterBox;
}

class MainWindow;

class MatterBox : public QWidget
{
    Q_OBJECT

public:
    explicit MatterBox(Matter matter, int matterId, MatterHandler* handler, MainWindow* mainWindow, QWidget *parent = nullptr);
    ~MatterBox();

private slots:
    void on_underlyingBtn_clicked();

    void on_checkBox_clicked(bool checked);

private:
    Ui::MatterBox *ui;
    Matter matter;
    int matterId;
    MatterHandler* handler;
    MainWindow* mainWindow;

    void checkTime();
};

#endif // MATTERBOX_H
