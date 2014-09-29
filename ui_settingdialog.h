/********************************************************************************
** Form generated from reading UI file 'settingdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGDIALOG_H
#define UI_SETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
    QDialogButtonBox *buttonBox;
    QTabWidget *tabWidget;
    QWidget *DetectorTab;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_6;
    QLineEdit *scanSpeed;
    QComboBox *sensitivty;
    QComboBox *scanMode;
    QCheckBox *dataPattern;
    QPushButton *normalize;
    QLabel *label_21;
    QLabel *label_22;
    QLineEdit *startPixel;
    QLineEdit *endPixel;
    QWidget *RaySourceTab;
    QLabel *label_5;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *rayVoltage;
    QLineEdit *rayCurrent;
    QLineEdit *exposeTime;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QWidget *DisplayTab;
    QLabel *label_13;
    QLabel *label_14;
    QWidget *DataTab;
    QLabel *label_16;
    QLineEdit *path;
    QPushButton *browseButton;
    QLabel *label_17;
    QLineEdit *singleFileSize;
    QLabel *label_18;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName(QStringLiteral("SettingDialog"));
        SettingDialog->resize(510, 444);
        buttonBox = new QDialogButtonBox(SettingDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(120, 400, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        tabWidget = new QTabWidget(SettingDialog);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 20, 491, 361));
        DetectorTab = new QWidget();
        DetectorTab->setObjectName(QStringLiteral("DetectorTab"));
        label = new QLabel(DetectorTab);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 30, 71, 31));
        label_2 = new QLabel(DetectorTab);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 100, 141, 31));
        label_3 = new QLabel(DetectorTab);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 160, 108, 24));
        label_4 = new QLabel(DetectorTab);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 220, 108, 24));
        label_6 = new QLabel(DetectorTab);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(270, 30, 41, 31));
        scanSpeed = new QLineEdit(DetectorTab);
        scanSpeed->setObjectName(QStringLiteral("scanSpeed"));
        scanSpeed->setGeometry(QRect(120, 30, 141, 31));
        sensitivty = new QComboBox(DetectorTab);
        sensitivty->setObjectName(QStringLiteral("sensitivty"));
        sensitivty->setGeometry(QRect(120, 100, 141, 31));
        sensitivty->setEditable(false);
        scanMode = new QComboBox(DetectorTab);
        scanMode->setObjectName(QStringLiteral("scanMode"));
        scanMode->setGeometry(QRect(120, 160, 141, 31));
        scanMode->setEditable(false);
        dataPattern = new QCheckBox(DetectorTab);
        dataPattern->setObjectName(QStringLiteral("dataPattern"));
        dataPattern->setGeometry(QRect(120, 220, 131, 28));
        normalize = new QPushButton(DetectorTab);
        normalize->setObjectName(QStringLiteral("normalize"));
        normalize->setGeometry(QRect(20, 270, 191, 31));
        label_21 = new QLabel(DetectorTab);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(250, 220, 61, 31));
        label_22 = new QLabel(DetectorTab);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(250, 260, 51, 31));
        startPixel = new QLineEdit(DetectorTab);
        startPixel->setObjectName(QStringLiteral("startPixel"));
        startPixel->setGeometry(QRect(330, 220, 141, 31));
        endPixel = new QLineEdit(DetectorTab);
        endPixel->setObjectName(QStringLiteral("endPixel"));
        endPixel->setGeometry(QRect(330, 270, 141, 31));
        tabWidget->addTab(DetectorTab, QString());
        RaySourceTab = new QWidget();
        RaySourceTab->setObjectName(QStringLiteral("RaySourceTab"));
        label_5 = new QLabel(RaySourceTab);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(60, 60, 131, 31));
        label_7 = new QLabel(RaySourceTab);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(60, 130, 131, 31));
        label_8 = new QLabel(RaySourceTab);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(60, 200, 131, 31));
        label_9 = new QLabel(RaySourceTab);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(60, 280, 141, 31));
        rayVoltage = new QLineEdit(RaySourceTab);
        rayVoltage->setObjectName(QStringLiteral("rayVoltage"));
        rayVoltage->setGeometry(QRect(180, 130, 241, 41));
        rayCurrent = new QLineEdit(RaySourceTab);
        rayCurrent->setObjectName(QStringLiteral("rayCurrent"));
        rayCurrent->setGeometry(QRect(180, 200, 241, 41));
        exposeTime = new QLineEdit(RaySourceTab);
        exposeTime->setObjectName(QStringLiteral("exposeTime"));
        exposeTime->setGeometry(QRect(180, 280, 241, 41));
        label_10 = new QLabel(RaySourceTab);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(520, 120, 131, 41));
        label_11 = new QLabel(RaySourceTab);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(520, 200, 131, 41));
        label_12 = new QLabel(RaySourceTab);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(520, 280, 131, 41));
        tabWidget->addTab(RaySourceTab, QString());
        DisplayTab = new QWidget();
        DisplayTab->setObjectName(QStringLiteral("DisplayTab"));
        label_13 = new QLabel(DisplayTab);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(50, 90, 251, 31));
        label_14 = new QLabel(DisplayTab);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(50, 200, 211, 31));
        tabWidget->addTab(DisplayTab, QString());
        DataTab = new QWidget();
        DataTab->setObjectName(QStringLiteral("DataTab"));
        label_16 = new QLabel(DataTab);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(10, 70, 51, 31));
        path = new QLineEdit(DataTab);
        path->setObjectName(QStringLiteral("path"));
        path->setGeometry(QRect(100, 70, 321, 31));
        browseButton = new QPushButton(DataTab);
        browseButton->setObjectName(QStringLiteral("browseButton"));
        browseButton->setGeometry(QRect(330, 110, 91, 31));
        label_17 = new QLabel(DataTab);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(10, 160, 101, 31));
        singleFileSize = new QLineEdit(DataTab);
        singleFileSize->setObjectName(QStringLiteral("singleFileSize"));
        singleFileSize->setGeometry(QRect(140, 160, 121, 31));
        label_18 = new QLabel(DataTab);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(270, 160, 61, 31));
        tabWidget->addTab(DataTab, QString());

        retranslateUi(SettingDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SettingDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SettingDialog, SLOT(reject()));

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QApplication::translate("SettingDialog", "Dialog", 0));
        label->setText(QApplication::translate("SettingDialog", "Scan speed", 0));
        label_2->setText(QApplication::translate("SettingDialog", "Sensitivity", 0));
        label_3->setText(QApplication::translate("SettingDialog", "Work Mode", 0));
        label_4->setText(QApplication::translate("SettingDialog", "Data Pattern", 0));
        label_6->setText(QApplication::translate("SettingDialog", "us", 0));
        sensitivty->clear();
        sensitivty->insertItems(0, QStringList()
         << QApplication::translate("SettingDialog", "1", 0)
         << QApplication::translate("SettingDialog", "2", 0)
         << QApplication::translate("SettingDialog", "3", 0)
         << QApplication::translate("SettingDialog", "4", 0)
         << QApplication::translate("SettingDialog", "5", 0)
         << QApplication::translate("SettingDialog", "6", 0)
         << QApplication::translate("SettingDialog", "7", 0)
        );
        sensitivty->setCurrentText(QApplication::translate("SettingDialog", "1", 0));
        scanMode->setCurrentText(QString());
        dataPattern->setText(QApplication::translate("SettingDialog", "Enable", 0));
        normalize->setText(QApplication::translate("SettingDialog", "Normalize", 0));
        label_21->setText(QApplication::translate("SettingDialog", "StartPixel", 0));
        label_22->setText(QApplication::translate("SettingDialog", "EndPixel", 0));
        tabWidget->setTabText(tabWidget->indexOf(DetectorTab), QApplication::translate("SettingDialog", "Detector", 0));
        label_5->setText(QApplication::translate("SettingDialog", "Ray Source Model", 0));
        label_7->setText(QApplication::translate("SettingDialog", "Voltage", 0));
        label_8->setText(QApplication::translate("SettingDialog", "Current", 0));
        label_9->setText(QApplication::translate("SettingDialog", "Expose Time", 0));
        label_10->setText(QApplication::translate("SettingDialog", "Kv", 0));
        label_11->setText(QApplication::translate("SettingDialog", "mA", 0));
        label_12->setText(QApplication::translate("SettingDialog", "s", 0));
        tabWidget->setTabText(tabWidget->indexOf(RaySourceTab), QApplication::translate("SettingDialog", "Ray Source", 0));
        label_13->setText(QApplication::translate("SettingDialog", "Display Direction", 0));
        label_14->setText(QApplication::translate("SettingDialog", "Refresh Mode", 0));
        tabWidget->setTabText(tabWidget->indexOf(DisplayTab), QApplication::translate("SettingDialog", "Display", 0));
        label_16->setText(QApplication::translate("SettingDialog", "Path", 0));
        browseButton->setText(QApplication::translate("SettingDialog", "Browse", 0));
        label_17->setText(QApplication::translate("SettingDialog", "Single File Frames", 0));
        label_18->setText(QApplication::translate("SettingDialog", "Frames", 0));
        tabWidget->setTabText(tabWidget->indexOf(DataTab), QApplication::translate("SettingDialog", "Data", 0));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
