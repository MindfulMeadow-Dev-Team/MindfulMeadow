/********************************************************************************
** Form generated from reading UI file 'pdfapi.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PDFAPI_H
#define UI_PDFAPI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PdfAPI
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *PdfAPI)
    {
        if (PdfAPI->objectName().isEmpty())
            PdfAPI->setObjectName("PdfAPI");
        PdfAPI->resize(640, 480);
        centralwidget = new QWidget(PdfAPI);
        centralwidget->setObjectName("centralwidget");
        PdfAPI->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PdfAPI);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 640, 21));
        PdfAPI->setMenuBar(menubar);
        statusbar = new QStatusBar(PdfAPI);
        statusbar->setObjectName("statusbar");
        PdfAPI->setStatusBar(statusbar);

        retranslateUi(PdfAPI);

        QMetaObject::connectSlotsByName(PdfAPI);
    } // setupUi

    void retranslateUi(QMainWindow *PdfAPI)
    {
        PdfAPI->setWindowTitle(QCoreApplication::translate("PdfAPI", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PdfAPI: public Ui_PdfAPI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PDFAPI_H
