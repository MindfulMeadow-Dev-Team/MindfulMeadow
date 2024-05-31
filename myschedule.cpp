#include "myschedule.h"

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

    loadSchedule(); // 在构造函数中调用读取函数
    QTableWidgetItem *item= new QTableWidgetItem("");
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(0, 0, item);

}
MySchedule::~MySchedule()
{
    saveSchedule(); // 在析构函数中调用保存函数
    delete ui;
}

void MySchedule::on_pushButton_clicked() // 保存按钮
{
    saveSchedule();
}

void MySchedule::on_pushButton_2_clicked() // 清空按钮
{

    // 清空文件内容
    QFile file("schedule.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file.resize(0); // 清空文件内容
        file.close();
    } else {
        QMessageBox::warning(this, "清空失败", "无法打开文件进行清空");
    }
    ui->tableWidget->clear();
    QStringList headerText;
    QStringList headerText2;
    headerText << "星期一" << "星期二" << "星期三" << "星期四" << "星期五" << "星期六" << "星期日";
    headerText2 << "第一节（8:00-8:50）" << "第二节（9:00-9:50）" << "第三节（10:10-11:00）" <<
        "第四节（11:10-12:00）" << "第五节（13:00-13:50）" << "第六节（14:00-14:50）" <<
        "第七节（15:10-16:00）" << "第八节（16:10-17:00）" << "第九节（17:10-18:00）" <<
        "第十节（18:40-19:30）" << "第十一节（19:40-20:30）" << "第十二节（20:40-21:30）";
    ui->tableWidget->setColumnCount(headerText.count());
    ui->tableWidget->setHorizontalHeaderLabels(headerText);
    ui->tableWidget->setRowCount(headerText2.count());
    ui->tableWidget->setVerticalHeaderLabels(headerText2);
    QTableWidgetItem *item;
    item = new QTableWidgetItem(0);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(0, 0, item);
    ui->tableWidget->adjustSize();
}



void MySchedule::saveSchedule() // 保存函数实现
{
    QFile file("schedule.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        // out << "\n";
        for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
            for (int column = 0; column < ui->tableWidget->columnCount(); ++column) {
                QTableWidgetItem *item = ui->tableWidget->item(row, column);
                if (item && !item->text().isEmpty()) {
                    out << item->text();
                } else {
                    out << "EMPTY"; // 标记空白单元格
                }
                if (column != ui->tableWidget->columnCount() - 1) {
                    out << "\t";
                }
            }
            out << "\n";
        }
        file.close();
    } else {
        QMessageBox::warning(this, "保存失败", "无法打开文件进行保存");
    }
}




void MySchedule::loadSchedule() // 读取保存的课表函数实现
{
    QFile file("schedule.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        ui->tableWidget->clearContents(); // 清空表格内容
        for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
            QString line = in.readLine();
            QStringList cells = line.split("\t");
            qDebug() << cells;
            for (int column = 0; column < ui->tableWidget->columnCount(); ++column) {
                QString text = (column < cells.size()) ? cells[column] : "EMPTY";
                QTableWidgetItem *item = new QTableWidgetItem(text == "EMPTY" ? "" : text);
                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                ui->tableWidget->setItem(row, column, item);
            }
        }
        ui->tableWidget->update();
        file.close();
    } else {
        QMessageBox::warning(this, "读取失败", "无法打开文件进行读取");
    }
}
