#include "myschedule.h"
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
#include "PdfAPI.h"
#include <QApplication>

MySchedule::MySchedule(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MySchedule)
{
    ui->setupUi(this);
    setWindowTitle("课程表");
    QStringList headerText;
    QStringList headerText2;
    headerText<<"星期一"<<"星期二"<<"星期三"<<"星期四"<<"星期五"<<"星期六"<<"星期日";
    headerText2<<"第一节（8:00-8:50）"<<"第二节（9:00-9:50）"<<"第三节（10:10-11:00）"<<
        "第四节（11:10-12:00）"<<"第五节（13:00-13:50）"<<"第六节（14:00-14:50）"<<
        "第七节（15:10-16:00）"<<"第八节（16:10-17:00）"<<"第九节（17:10-18:00）"<<
        "第十节（18:40-19:30）"<<"第十一节（19:40-20:30）"<<"第十二节（20:40-21:30）";
    ui->tableWidget->setColumnCount(headerText.count());
    ui->tableWidget->setHorizontalHeaderLabels(headerText);
    ui->tableWidget->setRowCount(headerText2.count());
    ui->tableWidget->setVerticalHeaderLabels(headerText2);
    ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
    QTableWidgetItem *item;
    item=new QTableWidgetItem(0);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget->setItem(0,0,item);
}
MySchedule::~MySchedule()
{
    delete ui;
}
void MySchedule::on_pushButton_clicked()//保存
{

    }
void MySchedule::on_pushButton_2_clicked()
{
    ui->tableWidget->clear();
    QStringList headerText;
    QStringList headerText2;
    headerText<<"星期一"<<"星期二"<<"星期三"<<"星期四"<<"星期五"<<"星期六"<<"星期日";
    headerText2<<"第一节（8:00-8:50）"<<"第二节（9:00-9:50）"<<"第三节（10:10-11:00）"<<
        "第四节（11:10-12:00）"<<"第五节（13:00-13:50）"<<"第六节（14:00-14:50）"<<
        "第七节（15:10-16:00）"<<"第八节（16:10-17:00）"<<"第九节（17:10-18:00）"<<
        "第十节（18:40-19:30）"<<"第十一节（19:40-20:30）"<<"第十二节（20:40-21:30）";
    ui->tableWidget->setColumnCount(headerText.count());
    ui->tableWidget->setHorizontalHeaderLabels(headerText);
    ui->tableWidget->setRowCount(headerText2.count());
    ui->tableWidget->setVerticalHeaderLabels(headerText2);
    QTableWidgetItem *item;
    item=new QTableWidgetItem(0);
    item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget->setItem(0,0,item);
}

