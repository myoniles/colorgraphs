/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QGraphicsView *graphicsView;
    QPushButton *newMapButton;
    QPushButton *fromFileButton;
    QPushButton *saveButton;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(Dialog);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        graphicsView = new QGraphicsView(Dialog);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        verticalLayout_2->addWidget(graphicsView);

        newMapButton = new QPushButton(Dialog);
        newMapButton->setObjectName(QStringLiteral("newMapButton"));

        verticalLayout_2->addWidget(newMapButton);

        fromFileButton = new QPushButton(Dialog);
        fromFileButton->setObjectName(QStringLiteral("fromFileButton"));

        verticalLayout_2->addWidget(fromFileButton);

        saveButton = new QPushButton(Dialog);
        saveButton->setObjectName(QStringLiteral("saveButton"));

        verticalLayout_2->addWidget(saveButton);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        newMapButton->setText(QApplication::translate("Dialog", "Generate New Map", 0));
        fromFileButton->setText(QApplication::translate("Dialog", "Generate From File", 0));
        saveButton->setText(QApplication::translate("Dialog", "Save Graph", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
