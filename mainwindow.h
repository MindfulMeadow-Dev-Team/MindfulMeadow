#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QDate>
#include <memory>
#include <QLayout>
#include "matterhandler.h"
#include "matterbox.h"

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

    void on_dateEdit_dateChanged(const QDate &date);

    void on_page1_Button_clicked();

    void on_page2_Button_clicked();


private:
    Ui::MainWindow *ui;

    QPropertyAnimation* rightSideAnm;
    QPropertyAnimation* mainNameEditAnm;
    QPropertyAnimation* matterScrollAreaAnm;

    bool rightSideHidden;
    QDate currDate;
    Matter currMatter;
    int currMatterId;
    std::unique_ptr<MatterHandler> handler;

    void showRightSide();
    void updateMatters();
};
#endif // MAINWINDOW_H
