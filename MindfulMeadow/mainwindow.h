
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
#include "myschedule.h"
#include "planttree.h"
#include "forest.h"

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

    void on_treeButton_clicked();

    void onTreeWindowClosing();

    void notDied();

    void on_page3_Button_clicked();

    void on_page4_Button_clicked();

    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);

private:
    Ui::MainWindow *ui;

    // animations on the mainwindow
    QPropertyAnimation* rightSideAnm;
    QPropertyAnimation* mainNameEditAnm;
    QPropertyAnimation* matterScrollAreaAnm;
    //windows tray
    QSystemTrayIcon* tray;
    // windows tray's menu
    QMenu* trayMenu;
    // timer for schedule noticing
    QTimer* timer;
    // mini-window
    MiniSchedule* mini;
    // white noise window
    WhiteNoiseWindow* whiteNoise;
    // tree-planting window
    plantTree *ptree;
    // window of the forest
    forest *frst;

    // indicates if the right side menu is hidden
    bool rightSideHidden;
    QDate currDate;
    Matter currMatter;
    int currMatterId;

    // database handler
    std::unique_ptr<MatterHandler> handler;

    void showRightSide();
    // update the matters on the first page of the stacked widget
    void updateMatters();
    // update the matters on the second page of the stacked widget
    void updateRecentMatters();
    void hideRightSide();

    // redefine closeEvent to avoid direct closing of the mainwindow
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent* event);
    // when the mouse clicked on the main window, hide the white noise window
    void mousePressEvent(QMouseEvent* event);

    int closeflag;

public:
    friend class MatterBox;
};
#endif // MAINWINDOW_H
