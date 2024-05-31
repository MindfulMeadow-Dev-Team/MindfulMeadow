
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QDate>
#include <memory>
#include <QLayout>
#include <QScrollBar>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QCloseEvent>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "matterhandler.h"
#include "matterbox.h"
#include "minischedule.h"
#include "whitenoisewindow.h"
#include"myschedule.h"
//below are planttree by zjy
#include "planttree.h"
#include"forest.h"
//above are planttree by zjy
class MiniSchedule;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_hideButton_clicked();

    void on_mainNameEdit_returnPressed();

    void on_mainDateEdit_dateChanged(const QDate &date);

    void on_nameEdit_editingFinished();

    void on_descriptionEdit_editingFinished();

    void on_page1_Button_clicked();

    void on_page2_Button_clicked();

    void on_deleteBtn_clicked();

    void on_timeout();

    void on_mainDateEdit_userDateChanged(const QDate &date);

    void on_dateEdit_userDateChanged(const QDate &date);

    void on_setDueCheckbox_clicked(bool checked);

    void on_timeEdit_userTimeChanged(const QTime &time);

    void on_miniButton_clicked();

    void on_whiteNoiseButton_clicked();

    //below are planttree by zjy
    void on_treeButton_clicked();

    void onTreeWindowClosing();

    void notDied();
    //avove are planttree by zjy


    void on_page3_Button_clicked();

    void on_page4_Button_clicked();

private:
    Ui::MainWindow *ui;

    QPropertyAnimation* rightSideAnm;
    QPropertyAnimation* mainNameEditAnm;
    QPropertyAnimation* matterScrollAreaAnm;
    QSystemTrayIcon* tray;
    QMenu* trayMenu;
    // QAction* trayShow;
    // QAction* trayMini;
    // QAction* trayExit;
    QTimer* timer;
    MiniSchedule* mini;
    WhiteNoiseWindow* whiteNoise;
    //below are planttree by zjy
    plantTree *ptree;
    forest *frst;

    //avove are planttree by zjy

    bool rightSideHidden;
    QDate currDate;
    Matter currMatter;
    int currMatterId;
    std::unique_ptr<MatterHandler> handler;

    void showRightSide();
    void updateMatters();
    void updateMatters2();
    void hideRightSide();

    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent* event);
    // test: when the mouse clicked on the main window, hide the white noise window
    void mousePressEvent(QMouseEvent* event);

public:
    friend class MatterBox;
    //below are planttree by zjy
    int closeflag;

    //above are planttree by zjy
};
#endif // MAINWINDOW_H
