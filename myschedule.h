#ifndef MYSCHEDULE_H
#define MYSCHEDULE_H

#include <QWidget>
#include<QTableWidget>
#include <QAxObject>
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
};

#endif // MYSCHEDULE_H
