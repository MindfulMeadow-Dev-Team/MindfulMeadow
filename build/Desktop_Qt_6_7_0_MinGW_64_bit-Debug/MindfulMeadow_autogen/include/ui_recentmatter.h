/********************************************************************************
** Form generated from reading UI file 'recentmatter.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECENTMATTER_H
#define UI_RECENTMATTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>

QT_BEGIN_NAMESPACE

class Ui_recentmatter
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *recentmatter)
    {
        if (recentmatter->objectName().isEmpty())
            recentmatter->setObjectName("recentmatter");
        recentmatter->resize(400, 300);
        buttonBox = new QDialogButtonBox(recentmatter);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(recentmatter);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, recentmatter, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, recentmatter, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(recentmatter);
    } // setupUi

    void retranslateUi(QDialog *recentmatter)
    {
        recentmatter->setWindowTitle(QCoreApplication::translate("recentmatter", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class recentmatter: public Ui_recentmatter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECENTMATTER_H
