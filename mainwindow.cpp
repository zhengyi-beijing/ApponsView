/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwindow.h"

#include <QHBoxLayout>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    populateScene();
    setMinimumSize(1024,768);
    resize(QSize(1500,1000));
    move(QApplication::desktop()->screen()->rect().center() - this->rect().center());

    view = new View("X-ray view");
    view->view()->setScene(scene);
    view->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    view->setMinimumSize(512,512);

    panel = new Panel("Command Pannel");
    panel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    panel->setMinimumSize(128,128);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(view);
    layout->addWidget(panel);
    setLayout(layout);

    setWindowTitle(tr("ApponsView"));
    connectSignals();

    imageObject = NULL;
}

MainWindow::~MainWindow()
{
    if(imageObject) {
        delete imageObject;
        imageObject = NULL;
    }
}

void MainWindow::populateScene()
{
    scene = new QGraphicsScene;
    createAxWidget();
    initAxWidget();
    proxy = scene->addWidget(axDisplay);
//    scene->addLine(0,0,100,100);
}

void MainWindow::ImageOpened()
{
    qDebug()<<"ImageOpened";
}

void MainWindow::FrameReady(int)
{
    static int framecount = 0;
    framecount++;
    qDebug()<< "Frame count: "<< framecount;
    int min = 0;
    qDebug() << "Pixel 0,0 is" << imageObject->Pixel(0,0);
    qDebug() << "image width is " << imageObject->Width();

    view->view()->viewport()->update();
}

void MainWindow::initAxWidget()
{
    axDetector->SetChannelType(2);
    axDetector->SetIPAddress("192.168.1.25");
    axDetector->SetCmdPort(3000);

    IUnknown* detector = axDetector->ObjectHandle();

    if(detector) {
        axImage->SetDetectorObject(detector);
        axCommander->SetDetectorObject(detector);
        axCommander->setVisible(false);
        qDebug()<<"Get detecor";
        axCommander->SetDataPattern(1);
    }

    axImage->SetChannelType(2);
    axImage->SetImgHeight(1024);
    axImage->SetImgWidth(1024);
    axImage->SetImagePort(4001);
    axImage->SetBytesPerPixel(2);
    axImage->setVisible(false);

    axDisplay->SetImgHeight(1024);
    axDisplay->SetImgWidth(1024);
    axDisplay->SetDisplayScale(0);
    axDisplay->SetInfoDisplay(1);
    axDisplay->SetMapStart(0);
    axDisplay->SetMapEnd(5000);
    axDisplay->setMinimumSize(512,512);

    qDebug()<<"get ImageObject";
    IUnknown* imgsrcHandle =  axImage->ObjectHandle();
    qDebug()<<"get ImageObject end";
    if (imgsrcHandle) {
        qDebug()<<"Set Display Source";
        axDisplay->SetDataSource(imgsrcHandle);
    }
    QObject::connect(axImage, SIGNAL(OnImageOpen()), this, SLOT(ImageOpened()));
    QObject::connect(axImage, SIGNAL(FrameReady(int)), this, SLOT(FrameReady(int)));

}

void MainWindow::openDetector()
{

    int opened = axDetector->Open();
    if (opened){
        qDebug()<< "Detector Opened";
        int rt = axImage->Open();
        imageObject = new DTControl::CImageObject(axImage->ImageObject());
        if(rt) {
            qDebug()<<"open image ";
            rt = axDisplay->Open();
            if(rt)
                qDebug()<<"open Display sucesful";
            else
                qDebug()<<"open display failed";
        }
        else
          qDebug()<<"Open Image failed" ;
    }
    else
        qDebug() << "OPen detector failed";
}

void MainWindow::createAxWidget()
{
    axDetector = new DTControl::CDTDetector(this);
    axDetector->setVisible(false);

    axDisplay = new DTControl::CDTDisplay();
    axDisplay->setVisible(true);

    axCommander = new DTControl::CDTCommanderF3(this);
    axCommander->setVisible(false);

    axImage = new DTControl::CDTImage(this);
    axImage->setVisible(false);
}

void MainWindow::connectSignals()
{
    QObject::connect(panel, &Panel::singleScanButton_click, this, &MainWindow::singleScan_clicked);
    QObject::connect(panel, SIGNAL(settingButton_click()), this, SLOT(setting_clicked()));
}

void MainWindow::open_clicked()
{

}

void MainWindow::save_clicked()
{

}

void MainWindow::setting_clicked()
{

}

void MainWindow::zoom_clicked()
{

}

void MainWindow::contrast_clicked()
{

}

void MainWindow::autoContrast_clicked()
{

}

void MainWindow::singleScan_clicked()
{
    qDebug()<<"MainWindow::singleScan_Clieked";
    int opened = false;
    opened = axDetector->property("IsOpened").toInt();
    if(!opened) {
        openDetector();
        opened = axDetector->property("IsOpened").toInt();
        if(!opened)
            QMessageBox::information(this, "", "Open Failed", "确定", "取消");
        axCommander->setProperty("DataPattern", 1);
    }

    static int grabbing = 0;
    if(grabbing == 0) {
        axImage->dynamicCall("grab(int)", 0);
        qDebug()<<"call image grab()";
        grabbing = 1;
    } else {
        axImage->dynamicCall("stop()");
        grabbing = 0;
        qDebug()<<"call image stop()";
    }
}

void MainWindow::dualScan_clicked()
{
}
