/********************************************************************************
** Form generated from reading UI file 'matterbox.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATTERBOX_H
#define UI_MATTERBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MatterBox
{
public:
    QCheckBox *name;
    QLabel *description;

    void setupUi(QWidget *MatterBox)
    {
        if (MatterBox->objectName().isEmpty())
            MatterBox->setObjectName("MatterBox");
        MatterBox->resize(400, 60);
        name = new QCheckBox(MatterBox);
        name->setObjectName("name");
        name->setGeometry(QRect(10, 0, 321, 41));
        description = new QLabel(MatterBox);
        description->setObjectName("description");
        description->setGeometry(QRect(30, 40, 54, 20));

        retranslateUi(MatterBox);

        QMetaObject::connectSlotsByName(MatterBox);
    } // setupUi

    void retranslateUi(QWidget *MatterBox)
    {
        MatterBox->setWindowTitle(QCoreApplication::translate("MatterBox", "Form", nullptr));
        name->setText(QCoreApplication::translate("MatterBox", "CheckBox", nullptr));
        description->setText(QCoreApplication::translate("MatterBox", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MatterBox: public Ui_MatterBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATTERBOX_H
