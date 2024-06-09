#ifndef MYSCHEDULE_H
#define MYSCHEDULE_H

#include <QWidget>
<<<<<<< HEAD
#include <QTableWidget>
#include "ui_myschedule.h"
#include <QTableWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QStringList>
#include <QTextEdit>
#include <QTextStream>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDate>
#include <QMessageBox>
#include <QDesktopServices>
#include <QApplication>
#include <QDebug>

=======
#include<QTableWidget>
#include <QAxObject>
>>>>>>> 25ddaa8f86ddbb61dd12adca040a91a77147a369
namespace Ui {
class MySchedule;
}
class MySchedule : public QWidget
{
    Q_OBJECT
    QTableWidget table;
public:
    explicit MySchedule(QWidget *parent = nullptr);
    void maybeSave(); // 判断是否需要保存
    bool saveFile();
    ~MySchedule();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MySchedule *ui;
<<<<<<< HEAD

    void saveSchedule(); // 新增的保存函数
    void loadSchedule(); // 读取保存的课表函数
=======
>>>>>>> 25ddaa8f86ddbb61dd12adca040a91a77147a369
};

#endif // MYSCHEDULE_H
