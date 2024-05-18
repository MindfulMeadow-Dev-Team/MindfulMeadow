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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MatterBox
{
public:
    QPushButton *underlyingBtn;
    QCheckBox *checkBox;
    QLabel *description;

    void setupUi(QWidget *MatterBox)
    {
        if (MatterBox->objectName().isEmpty())
            MatterBox->setObjectName("MatterBox");
        MatterBox->resize(632, 68);
        MatterBox->setStyleSheet(QString::fromUtf8("background-color:lightgrey"));
        underlyingBtn = new QPushButton(MatterBox);
        underlyingBtn->setObjectName("underlyingBtn");
        underlyingBtn->setGeometry(QRect(0, 0, 631, 71));
        checkBox = new QCheckBox(MatterBox);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(10, 10, 81, 21));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(checkBox->sizePolicy().hasHeightForWidth());
        checkBox->setSizePolicy(sizePolicy);
        QFont font;
        font.setBold(true);
        checkBox->setFont(font);
        description = new QLabel(MatterBox);
        description->setObjectName("description");
        description->setGeometry(QRect(10, 40, 61, 16));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(description->sizePolicy().hasHeightForWidth());
        description->setSizePolicy(sizePolicy1);

        retranslateUi(MatterBox);

        QMetaObject::connectSlotsByName(MatterBox);
    } // setupUi

    void retranslateUi(QWidget *MatterBox)
    {
        MatterBox->setWindowTitle(QCoreApplication::translate("MatterBox", "Form", nullptr));
        underlyingBtn->setText(QString());
        checkBox->setText(QCoreApplication::translate("MatterBox", "CheckBox", nullptr));
        description->setText(QCoreApplication::translate("MatterBox", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MatterBox: public Ui_MatterBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATTERBOX_H
