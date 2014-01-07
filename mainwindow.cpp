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
#include "pixelorderconverter.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    qDebug() << "Main thread id = " << QThread::currentThreadId();
    populateScene();
    setMinimumSize(1024,768);
    resize(QSize(1500,1000));
    move(QApplication::desktop()->screen()->rect().center() - this->rect().center());

    view = new View("X-ray view");
    view->view()->setScene(scene);
    view->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    view->setMinimumSize(512,512);
    view->view()->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    panel = new Panel("Command Pannel");
    panel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    panel->setMinimumSize(128,128);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(view);
    layout->addWidget(axDisplay);
    layout->addWidget(panel);
    setLayout(layout);

    setWindowTitle(tr("ApponsView"));
    connectSignals();

    dualScanEnabled = false;

    fileServer.start();
}

MainWindow::~MainWindow()
{
}

void MainWindow::populateScene()
{
    scene = new QGraphicsScene;
    createAxWidget();
    initAxWidget();
    proxy = scene->addWidget(axDisplayWidget);
}

void MainWindow::ImageOpened()
{
    qDebug()<<"ImageOpened";
}


void MainWindow::Datalost(int num)
{
    qDebug() << "DataLost Happen Lost************* " << num << "lines ";
    QMessageBox::information(this, "", "Data Lost Happend", "确定", "取消");
}

void MainWindow::FrameReady(int)
{
    static int framecount = 0;
    framecount++;
    qDebug()<< "Frame count: "<< framecount;
    qDebug() << "Frame Ready thread id = " << QThread::currentThreadId();
    //qDebug()<<"pixel 0,0=" << axImageObject->Pixel(0,0);
    if(dualScanEnabled) {
       DualToSingleConverter converter(8, 64);
       converter.process(axImageObject);
    }

    if (autoSaveEnabled) {
        int size = axImageObject->Width()*axImageObject->Height()*axImageObject->BytesPerPixel();
        ImageData* data = new ImageData((char*)axImageObject->ImageDataAddress(), size);
        fileServer.append(data);
    }
    scene->update();
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
    }

    axImage->SetChannelType(2);
    axImage->SetImgHeight(1024);
    axImage->SetImgWidth(512);
    axImage->SetImagePort(4001);
    axImage->SetBytesPerPixel(2);
    axImage->setVisible(false);

    axDisplay->SetDisplayScale(0);
    axDisplay->SetMapStart(100);
    axDisplay->SetMapEnd(10000);
    axDisplay->setMinimumSize(512,512);
    axDisplay->dynamicCall("SetDisplayScale(int)", 0);
    axDisplay->setVisible(true);
    //axDisplay->SetRefreshRate(30);
    axDisplayWidget->SetDisplayScale(0);
    axDisplayWidget->SetMapStart(100);
    axDisplayWidget->SetMapEnd(10000);
    axDisplayWidget->setMinimumSize(512,512);
    axDisplayWidget->dynamicCall("SetDisplayScale(int)", 0);
    axDisplayWidget->setVisible(true);

    qDebug()<<"get ImageObject";
    IUnknown* imgsrcHandle =  axImage->ObjectHandle();
    qDebug()<<"get ImageObject end";
    if (imgsrcHandle) {
        qDebug()<<"Set Display Source";
        axDisplay->SetDataSource(imgsrcHandle);
        axDisplayWidget->SetDataSource(imgsrcHandle);
    }

    openDetector();
    QObject::connect(axImage, SIGNAL(OnImageOpen()), this, SLOT(ImageOpened()));
    QObject::connect(axImage, SIGNAL(FrameReady(int)), this, SLOT(FrameReady(int)));
    QObject::connect(axImage, SIGNAL(Datalost(int)), this, SLOT(Datalost(int)));
}

void MainWindow::initDetector()
{
        axCommander->SetDataPattern(1);
        axCommander->SetIntegrationTime(1400);
        QString rt;
        axDetector->SendCommand(QString("[ED,M,0]"), rt);
}

void MainWindow::openDetector()
{

    int opened = axDetector->Open();
    initDetector();

    if (opened){
        qDebug()<< "Detector Opened";
        int rt = axImage->Open();
        axImageObject = new DTControl::IImageObject((IDispatch*)axImage->ImageObject());

        if(rt) {
            qDebug()<<"open image ";
            rt = axDisplay->Open();
            rt = axDisplayWidget->Open();
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

    axDisplay = new DTControl::CDTDisplay(this);
    axDisplay->setVisible(true);
    axDisplayWidget = new DTControl::CDTDisplay();
    axDisplayWidget->setVisible(true);

    axCommander = new DTControl::CDTCommanderF3(this);
    axCommander->setVisible(false);

    axImage = new DTControl::CDTImage(this);
    axImage->setVisible(false);
}

void MainWindow::connectSignals()
{
    QObject::connect(panel, &Panel::singleScanEnable, this, &MainWindow::singleScanEnable);
    QObject::connect(panel, &Panel::dualScanEnable, this, &MainWindow::dualScanEnable);
    QObject::connect(panel, &Panel::settingButton_click, this, &MainWindow::setting_clicked);
    QObject::connect(panel, &Panel::openButton_click, this, &MainWindow::open_clicked);
    QObject::connect(panel, &Panel::autoSaveEnable, this, &MainWindow::autoSaveEnable);
    QObject::connect(panel, &Panel::powerButton_click, this, &MainWindow::power_clicked);
    QObject::connect(panel, &Panel::contrastEnable, this, &MainWindow::contrastEnable);
    QObject::connect(panel, &Panel::autoContrastButton_click, this, &MainWindow::autoContrast_clicked);
    QObject::connect(panel, &Panel::zoomEnable, this, &MainWindow::zoomEnable);
    QObject::connect(panel, &Panel::moveEnable, this, &MainWindow::moveEnable);
    QObject::connect(panel, &Panel::invertButton_click, this, &MainWindow::invert_click);
    QObject::connect(panel, &Panel::rotateButton_click, this, &MainWindow::rotate_click);

}

void MainWindow::scan()
{
    int opened = false;
    opened = axDetector->property("IsOpened").toInt();
    if(!opened) {
        qDebug()<<"Call Open Detector";
        openDetector();
        opened = axDetector->property("IsOpened").toInt();
        if(!opened) {
            QMessageBox::information(this, "", "Open Failed", "确定", "取消");
            return;
        }
    }

    static int grabbing = 0;
    if(grabbing == 0) {
        //axImage->dynamicCall("grab(int)", 0);
        axImage->Grab(0);
        qDebug()<<"call image grab()";
        grabbing = 1;
    } else {
        axImage->dynamicCall("stop()");
        axImage->Stop();
        grabbing = 0;
        qDebug()<<"call image stop()";
    }
}

void MainWindow::singleScanEnable(bool enable)
{
    dualScanEnabled = !enable;
    qDebug() << __FUNCTION__;
    scan();
}

void MainWindow::dualScanEnable(bool enable)
{
    dualScanEnabled = enable;
    scan();
}

void MainWindow::setting_clicked()
{
    //OPen setting dialog
}

void MainWindow::open_clicked()
{
//open file dialog
}

void MainWindow::autoSaveEnable(bool enable)
{
    autoSaveEnabled = enable;
}

void MainWindow::power_clicked()
{
    //exit
    QApplication::quit();
}


void MainWindow::contrastEnable(bool enable)
{
    contrastEnabled = enable;//conflict with zoom and move
}

void MainWindow::invert_click()
{
    DTControl::IImageObject ImageObject((IDispatch*)axDisplay->ImageObject());
    int start = axDisplay->MapStart();
    int end = axDisplay->MapEnd();
    axDisplay->SetMapStart(end);
    axDisplay->SetMapEnd(start);
}

void MainWindow::autoContrast_clicked()
{
// 1find  minist of frame
//   2 find maximu of frame
//   3 set map range
    qDebug() << __FUNCTION__;
    DTControl::IImageObject ImageObject((IDispatch*)axDisplay->ImageObject());
    int width = ImageObject.Width();
    int height = ImageObject.Height();
    int min = 0;
    int max = 0;
    for(int j=0; j < height; j++)
        for(int i = 0; i < width; i++) {
            int v = ImageObject.Pixel(i, j);
            if (max < v)
                max = v;
            if (min > v)
                min = v;
        }
    axDisplay->SetMapStart(min);
    axDisplay->SetMapEnd(max);
}

void MainWindow::zoomEnable(bool enable)
{
    zoomEnabled = enable;
}

void MainWindow::rotate_click()
{
    view->rotateRight();
}

void MainWindow::moveEnable(bool enable)
{
    zoomEnabled = enable;
}
