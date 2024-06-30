#ifndef MINISCHEDULE_H
#define MINISCHEDULE_H

#include <QWidget>
#include <QDate>
#include "matterbox.h"
#include "matterhandler.h"


namespace Ui {
class MiniSchedule;
}

class MiniSchedule : public QWidget
{
    Q_OBJECT

public:
    explicit MiniSchedule(MatterHandler* handler, QWidget* mainWindow, QWidget *parent = nullptr);
    ~MiniSchedule();

private slots:
    void on_maxBtn_clicked();

private:
    Ui::MiniSchedule *ui;
    QWidget* mainWindow;
    MatterHandler* handler;

    void updateMatters();

private:
    // override closeEvent to hide the window in windows tray
    void closeEvent(QCloseEvent* event);
    void showEvent(QShowEvent *event);
};

#endif // MINISCHEDULE_H
