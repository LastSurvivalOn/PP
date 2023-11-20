/********************************************************************************
** Form generated from reading UI file 'save.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVE_H
#define UI_SAVE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Save
{
public:
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Save)
    {
        if (Save->objectName().isEmpty())
            Save->setObjectName("Save");
        Save->resize(174, 70);
        verticalLayout = new QVBoxLayout(Save);
        verticalLayout->setObjectName("verticalLayout");
        lineEdit = new QLineEdit(Save);
        lineEdit->setObjectName("lineEdit");

        verticalLayout->addWidget(lineEdit);

        buttonBox = new QDialogButtonBox(Save);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(Save);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Save, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Save, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Save);
    } // setupUi

    void retranslateUi(QDialog *Save)
    {
        Save->setWindowTitle(QCoreApplication::translate("Save", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Save: public Ui_Save {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVE_H
