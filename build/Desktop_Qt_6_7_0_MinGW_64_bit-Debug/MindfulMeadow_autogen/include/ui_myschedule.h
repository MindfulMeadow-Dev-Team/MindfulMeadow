/********************************************************************************
** Form generated from reading UI file 'myschedule.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYSCHEDULE_H
#define UI_MYSCHEDULE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MySchedule
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *MySchedule)
    {
        if (MySchedule->objectName().isEmpty())
            MySchedule->setObjectName("MySchedule");
        MySchedule->resize(640, 480);
        tableWidget = new QTableWidget(MySchedule);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 0, 641, 481));
        pushButton = new QPushButton(MySchedule);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(220, 410, 121, 41));
        pushButton_2 = new QPushButton(MySchedule);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(460, 410, 121, 41));

        retranslateUi(MySchedule);

        QMetaObject::connectSlotsByName(MySchedule);
    } // setupUi

    void retranslateUi(QWidget *MySchedule)
    {
        MySchedule->setWindowTitle(QCoreApplication::translate("MySchedule", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("MySchedule", "\344\277\235\345\255\230", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MySchedule", "\346\270\205\347\251\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MySchedule: public Ui_MySchedule {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYSCHEDULE_H
