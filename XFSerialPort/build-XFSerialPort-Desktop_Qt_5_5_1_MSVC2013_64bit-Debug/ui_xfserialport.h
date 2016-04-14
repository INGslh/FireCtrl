/********************************************************************************
** Form generated from reading UI file 'xfserialport.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XFSERIALPORT_H
#define UI_XFSERIALPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_xfserialport
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *BtnOpen;
    QPushButton *BtnSend;
    QTextEdit *EditRev;
    QLineEdit *EditSend;

    void setupUi(QDialog *xfserialport)
    {
        if (xfserialport->objectName().isEmpty())
            xfserialport->setObjectName(QStringLiteral("xfserialport"));
        xfserialport->resize(400, 300);
        verticalLayoutWidget = new QWidget(xfserialport);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(269, 0, 91, 311));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        BtnOpen = new QPushButton(verticalLayoutWidget);
        BtnOpen->setObjectName(QStringLiteral("BtnOpen"));

        verticalLayout->addWidget(BtnOpen);

        BtnSend = new QPushButton(verticalLayoutWidget);
        BtnSend->setObjectName(QStringLiteral("BtnSend"));

        verticalLayout->addWidget(BtnSend);

        EditRev = new QTextEdit(xfserialport);
        EditRev->setObjectName(QStringLiteral("EditRev"));
        EditRev->setGeometry(QRect(40, 70, 201, 81));
        EditSend = new QLineEdit(xfserialport);
        EditSend->setObjectName(QStringLiteral("EditSend"));
        EditSend->setGeometry(QRect(42, 210, 201, 20));

        retranslateUi(xfserialport);

        QMetaObject::connectSlotsByName(xfserialport);
    } // setupUi

    void retranslateUi(QDialog *xfserialport)
    {
        xfserialport->setWindowTitle(QApplication::translate("xfserialport", "xfserialport", 0));
        BtnOpen->setText(QApplication::translate("xfserialport", "Open", 0));
        BtnSend->setText(QApplication::translate("xfserialport", "Send", 0));
    } // retranslateUi

};

namespace Ui {
    class xfserialport: public Ui_xfserialport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XFSERIALPORT_H
