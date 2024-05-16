/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *leftSide;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QWidget *underSide;
    QPushButton *plantButton;
    QPushButton *whiteNoiseButton;
    QScrollArea *rightScrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QPushButton *hideButton;
    QLineEdit *descriptionEdit;
    QLineEdit *nameEdit;
    QDateEdit *dateEdit;
    QStackedWidget *stackedWidget;
    QWidget *page1;
    QDateEdit *mainDateEdit;
    QLineEdit *mainNameEdit;
    QScrollArea *matterScrolArea;
    QWidget *scrollAreaWidgetContents_3;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QWidget *page2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMouseTracking(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        leftSide = new QWidget(centralwidget);
        leftSide->setObjectName("leftSide");
        leftSide->setGeometry(QRect(0, 0, 181, 581));
        leftSide->setStyleSheet(QString::fromUtf8("background-color:lightgrey;"));
        pushButton = new QPushButton(leftSide);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 130, 161, 41));
        pushButton_2 = new QPushButton(leftSide);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(10, 180, 161, 41));
        pushButton_3 = new QPushButton(leftSide);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(10, 230, 161, 41));
        pushButton_4 = new QPushButton(leftSide);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(10, 280, 161, 41));
        underSide = new QWidget(centralwidget);
        underSide->setObjectName("underSide");
        underSide->setGeometry(QRect(180, 509, 621, 71));
        underSide->setStyleSheet(QString::fromUtf8("background-color:gray;"));
        plantButton = new QPushButton(underSide);
        plantButton->setObjectName("plantButton");
        plantButton->setGeometry(QRect(440, 20, 101, 51));
        whiteNoiseButton = new QPushButton(underSide);
        whiteNoiseButton->setObjectName("whiteNoiseButton");
        whiteNoiseButton->setGeometry(QRect(270, 20, 101, 51));
        rightScrollArea = new QScrollArea(centralwidget);
        rightScrollArea->setObjectName("rightScrollArea");
        rightScrollArea->setGeometry(QRect(600, 0, 201, 511));
        rightScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName("scrollAreaWidgetContents_2");
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 199, 509));
        hideButton = new QPushButton(scrollAreaWidgetContents_2);
        hideButton->setObjectName("hideButton");
        hideButton->setGeometry(QRect(140, 30, 41, 41));
        descriptionEdit = new QLineEdit(scrollAreaWidgetContents_2);
        descriptionEdit->setObjectName("descriptionEdit");
        descriptionEdit->setGeometry(QRect(20, 150, 161, 23));
        nameEdit = new QLineEdit(scrollAreaWidgetContents_2);
        nameEdit->setObjectName("nameEdit");
        nameEdit->setGeometry(QRect(20, 100, 161, 23));
        dateEdit = new QDateEdit(scrollAreaWidgetContents_2);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(20, 200, 161, 24));
        dateEdit->setMaximumDateTime(QDateTime(QDate(2100, 12, 31), QTime(7, 59, 59)));
        dateEdit->setMinimumDate(QDate(2000, 9, 14));
        dateEdit->setCalendarPopup(true);
        rightScrollArea->setWidget(scrollAreaWidgetContents_2);
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(180, 0, 621, 511));
        page1 = new QWidget();
        page1->setObjectName("page1");
        mainDateEdit = new QDateEdit(page1);
        mainDateEdit->setObjectName("mainDateEdit");
        mainDateEdit->setGeometry(QRect(30, 20, 361, 41));
        mainDateEdit->setMaximumDateTime(QDateTime(QDate(2100, 12, 31), QTime(7, 59, 59)));
        mainDateEdit->setMinimumDateTime(QDateTime(QDate(2000, 9, 14), QTime(16, 0, 0)));
        mainDateEdit->setMinimumDate(QDate(2000, 9, 14));
        mainDateEdit->setCalendarPopup(true);
        mainNameEdit = new QLineEdit(page1);
        mainNameEdit->setObjectName("mainNameEdit");
        mainNameEdit->setGeometry(QRect(30, 90, 561, 41));
        matterScrolArea = new QScrollArea(page1);
        matterScrolArea->setObjectName("matterScrolArea");
        matterScrolArea->setGeometry(QRect(30, 160, 561, 321));
        matterScrolArea->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName("scrollAreaWidgetContents_3");
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 559, 319));
        verticalLayoutWidget = new QWidget(scrollAreaWidgetContents_3);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 0, 561, 321));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        matterScrolArea->setWidget(scrollAreaWidgetContents_3);
        stackedWidget->addWidget(page1);
        page2 = new QWidget();
        page2->setObjectName("page2");
        stackedWidget->addWidget(page2);
        MainWindow->setCentralWidget(centralwidget);
        stackedWidget->raise();
        leftSide->raise();
        underSide->raise();
        rightScrollArea->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setEnabled(false);
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        statusbar->setEnabled(true);
        statusbar->setSizeGripEnabled(true);
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Day Todo", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\346\227\245\347\250\213\346\246\202\350\247\210", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\346\210\221\347\232\204\350\257\276\350\241\250", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\346\210\221\347\232\204\346\243\256\346\236\227", nullptr));
        plantButton->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\347\247\215\346\240\221", nullptr));
        whiteNoiseButton->setText(QCoreApplication::translate("MainWindow", "\347\231\275\345\231\252\351\237\263", nullptr));
        hideButton->setText(QCoreApplication::translate("MainWindow", ">", nullptr));
        descriptionEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\346\217\217\350\277\260", nullptr));
        nameEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\346\227\245\347\250\213\345\220\215\347\247\260", nullptr));
        mainNameEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\345\234\250\346\255\244\346\267\273\345\212\240\345\206\205\345\256\271\357\274\214\346\214\211\345\233\236\350\275\246\345\210\233\345\273\272\344\272\213\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
