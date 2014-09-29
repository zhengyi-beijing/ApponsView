/********************************************************************************
** Form generated from reading UI file 'plotwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTWIDGET_H
#define UI_PLOTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_PlotWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QCustomPlot *plot;
    QHBoxLayout *horizontalLayout;
    QCheckBox *autoRange;
    QLabel *label;
    QLineEdit *xmin;
    QLabel *label_2;
    QLineEdit *xmax;
    QLabel *label_3;
    QLineEdit *ymin;
    QLabel *label_4;
    QLineEdit *ymax;
    QPushButton *rangeApply;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *PlotWidget)
    {
        if (PlotWidget->objectName().isEmpty())
            PlotWidget->setObjectName(QStringLiteral("PlotWidget"));
        PlotWidget->resize(692, 573);
        verticalLayout_2 = new QVBoxLayout(PlotWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        plot = new QCustomPlot(PlotWidget);
        plot->setObjectName(QStringLiteral("plot"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(plot->sizePolicy().hasHeightForWidth());
        plot->setSizePolicy(sizePolicy);
        plot->setMinimumSize(QSize(512, 512));

        verticalLayout->addWidget(plot);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        autoRange = new QCheckBox(PlotWidget);
        autoRange->setObjectName(QStringLiteral("autoRange"));

        horizontalLayout->addWidget(autoRange);

        label = new QLabel(PlotWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(60, 20));

        horizontalLayout->addWidget(label);

        xmin = new QLineEdit(PlotWidget);
        xmin->setObjectName(QStringLiteral("xmin"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(xmin->sizePolicy().hasHeightForWidth());
        xmin->setSizePolicy(sizePolicy1);
        xmin->setMaximumSize(QSize(60, 20));

        horizontalLayout->addWidget(xmin);

        label_2 = new QLabel(PlotWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(60, 20));

        horizontalLayout->addWidget(label_2);

        xmax = new QLineEdit(PlotWidget);
        xmax->setObjectName(QStringLiteral("xmax"));
        sizePolicy1.setHeightForWidth(xmax->sizePolicy().hasHeightForWidth());
        xmax->setSizePolicy(sizePolicy1);
        xmax->setMaximumSize(QSize(60, 20));

        horizontalLayout->addWidget(xmax);

        label_3 = new QLabel(PlotWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(60, 20));

        horizontalLayout->addWidget(label_3);

        ymin = new QLineEdit(PlotWidget);
        ymin->setObjectName(QStringLiteral("ymin"));
        sizePolicy1.setHeightForWidth(ymin->sizePolicy().hasHeightForWidth());
        ymin->setSizePolicy(sizePolicy1);
        ymin->setMaximumSize(QSize(60, 20));

        horizontalLayout->addWidget(ymin);

        label_4 = new QLabel(PlotWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMaximumSize(QSize(60, 20));

        horizontalLayout->addWidget(label_4);

        ymax = new QLineEdit(PlotWidget);
        ymax->setObjectName(QStringLiteral("ymax"));
        sizePolicy1.setHeightForWidth(ymax->sizePolicy().hasHeightForWidth());
        ymax->setSizePolicy(sizePolicy1);
        ymax->setMaximumSize(QSize(60, 20));

        horizontalLayout->addWidget(ymax);

        rangeApply = new QPushButton(PlotWidget);
        rangeApply->setObjectName(QStringLiteral("rangeApply"));

        horizontalLayout->addWidget(rangeApply);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(PlotWidget);

        QMetaObject::connectSlotsByName(PlotWidget);
    } // setupUi

    void retranslateUi(QWidget *PlotWidget)
    {
        PlotWidget->setWindowTitle(QApplication::translate("PlotWidget", "Form", 0));
        autoRange->setText(QApplication::translate("PlotWidget", "Auto", 0));
        label->setText(QApplication::translate("PlotWidget", "X Min", 0));
        xmin->setText(QApplication::translate("PlotWidget", "0", 0));
        label_2->setText(QApplication::translate("PlotWidget", "X Max", 0));
        xmax->setText(QApplication::translate("PlotWidget", "1536", 0));
        label_3->setText(QApplication::translate("PlotWidget", "Y Min", 0));
        ymin->setText(QApplication::translate("PlotWidget", "0", 0));
        label_4->setText(QApplication::translate("PlotWidget", "Y Max", 0));
        ymax->setText(QApplication::translate("PlotWidget", "30000", 0));
        rangeApply->setText(QApplication::translate("PlotWidget", "Apply", 0));
    } // retranslateUi

};

namespace Ui {
    class PlotWidget: public Ui_PlotWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTWIDGET_H
