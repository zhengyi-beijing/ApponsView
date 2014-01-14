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
#include <QDir>
#include <QFileDialog>

ApponsSetting MainWindow::setting;
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setting.LoadConfig();
    qDebug() << "Main thread id = " << QThread::currentThreadId();
    ip = setting.ip();
    qDebug() << "ip is " << ip;
    populateScene();
    setMinimumSize(1024,768);
    resize(QSize(1280,1024));
    move(QApplication::desktop()->screen()->rect().center() - this->rect().center());


    panel = new Panel("Command Pannel");
    panel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    panel->setMinimumSize(64, 64);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(1);
    layout->setSpacing(1);
    layout->addWidget(view);
    layout->addWidget(panel);
    setLayout(layout);

    setWindowTitle(tr("ApponsView"));
    connectSignals();

    dualScanEnabled = false;
    autoSaveEnabled = false;
    grabing = false;

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
    axDisplay->setParent(NULL);
    proxy = scene->addWidget(axDisplay);
    axDisplay->setVisible(true);

    view = new View("X-ray view");
    view->view()->setScene(scene);
    view->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    view->setMinimumSize(512, 512);
}

void MainWindow::widgetMoveto(QPoint dpos)
{
    //proxy->move(proxy->pos()+dpos);
    //scene->update();
}

void MainWindow::ImageOpened()
{
    qDebug()<<"ImageOpened";
}



void MainWindow::Datalost(int num)
{
    qDebug() << "DataLost Happen Lost************* " << num << "lines ";
    //QMessageBox::information(this, "", "Data Lost Happend", "确定", "取消");
    lostLineCount++;
    panel->frameCountLabel->setDataLost(lostLineCount);
}

void MainWindow::resizeEvent(QResizeEvent * event)
{
    fitToScene();
}

void MainWindow::fitToScene()
{
    qDebug()<<"proxy "<< proxy->rect();
    view->resetView();
}

void MainWindow::showEvent(QShowEvent* event)
{
    fitToScene();
}

void MainWindow::SubFrameReady(int NumOfBlockLeft, int StartLine, int NumLines, int bLastBlock)
{
    //qDebug() << __FUNCTION__;
    scene->update();
}

void MainWindow::FrameReady(int)
{
    framecount++;
    qDebug()<< "Frame count: "<< framecount;
    qDebug() << "Frame Ready thread id = " << QThread::currentThreadId();
    if (setting.autoSave()) {
        int size = axImageObject->Width()*axImageObject->Height()*axImageObject->BytesPerPixel();
        ImageData* data = new ImageData((char*)axImageObject->ImageDataAddress(), size);
        fileServer.append(data);
    }
    scene->update();
    view->view()->viewport()->update();
    panel->frameCountLabel->setFrameCount(framecount);
}

void MainWindow::createAxWidget()
{
    axDetector = new DTControl::CDTDetector(this);
    axDetector->setVisible(false);

    axDisplay = new DTControl::CDTDisplay(this);
    axDisplay->setVisible(false);

    axCommander = new DTControl::CDTCommanderF3(this);
    axCommander->setVisible(false);

    axImage = new DTControl::CDTImage(this);
    axImage->setVisible(false);
}

void MainWindow::initAxWidget()
{
    axDetector->SetChannelType(2);
    //axDetector->SetIPAddress("192.168.1.25");
    axDetector->SetIPAddress(ip);
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
    axImage->SetImgWidth(1536);
    axImage->SetImagePort(4001);
    axImage->SetBytesPerPixel(2);
    axImage->SetSubFrameHeight(32);
    axImage->setVisible(false);

    axDisplay->SetDisplayScale(0);
    axDisplay->SetMapStart(100);
    axDisplay->SetMapEnd(10000);
    axDisplay->setMinimumSize(512,512);
    axDisplay->dynamicCall("SetDisplayScale(int)", 0);
    axDisplay->SetRefreshMode(2);//Moving

    qDebug()<<"get ImageObject";
    IUnknown* imgsrcHandle =  axImage->ObjectHandle();
    qDebug()<<"get ImageObject end";
    if (imgsrcHandle) {
        qDebug()<<"Set Display Source";
        axDisplay->SetDataSource(imgsrcHandle);
    }

    //openDetector();
    QObject::connect(axImage, SIGNAL(FrameReady(int)), this, SLOT(FrameReady(int)));
    QObject::connect(axImage, SIGNAL(Datalost(int)), this, SLOT(Datalost(int)));
    QObject::connect(axImage, SIGNAL(SubFrameReady(int, int, int, int)), this, SLOT(SubFrameReady(int, int, int, int)));
}


void MainWindow::initDetector()
{
       // axCommander->SetDataPattern(1);
       // axCommander->SetIntegrationTime(1400);
    QString rt;
    axDetector->SendCommand(QString("[ED,M,1]"), rt);
    if(setting.dataPattern())
        axCommander->SetDataPattern(1);
    float pixelSize = axCommander->PixelSize();
    int time = pixelSize*1000000/(setting.scanSpeed()*10);
    qDebug()<<"Inetegration Time is "<<time;
    axCommander->SetIntegrationTime(time);
    axCommander->SetSensitivityLevel(setting.sensitivityLevel());

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
            //rt = axDisplayWidget->Open();

            axDisplayObject = new DTControl::IImageObject((IDispatch*)axDisplay->ImageObject());
            if(rt) {
                qDebug()<<"open Display sucesful";
            }
            else
                qDebug()<<"open display failed";
        }
        else
          qDebug()<<"Open Image failed" ;
    }
    else
        qDebug() << "OPen detector failed";
}

void MainWindow::connectSignals()
{
    QObject::connect(panel, &Panel::singleScanEnable, this, &MainWindow::singleScanEnable);
    QObject::connect(panel, &Panel::dualScanEnable, this, &MainWindow::dualScanEnable);
    QObject::connect(panel, &Panel::settingButton_click, this, &MainWindow::setting_clicked);
    QObject::connect(panel, &Panel::openButton_click, this, &MainWindow::open_clicked);
    QObject::connect(panel->saveButton, &QToolButton::click, this, &MainWindow::saveButtonClick);
    QObject::connect(panel, &Panel::powerButton_click, this, &MainWindow::power_clicked);
    QObject::connect(panel, &Panel::contrastEnable, this, &MainWindow::contrastEnable);
    QObject::connect(panel, &Panel::autoContrastButton_click, this, &MainWindow::autoContrast_clicked);
    QObject::connect(panel, &Panel::zoomEnable, this, &MainWindow::zoomEnable);
    QObject::connect(panel, &Panel::moveEnable, this, &MainWindow::moveEnable);
    QObject::connect(panel, &Panel::invertButton_click, this, &MainWindow::invert_click);
    QObject::connect(panel, &Panel::rotateButton_click, this, &MainWindow::rotate_click);

    QObject::connect(axDisplay,SIGNAL(MouseMove(int, int, int)), panel->pixelInfoLabel, SLOT(setInfo(int, int, int)));
}

void MainWindow::stop()
{
    axImage->Stop();
    grabing = false;
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
            QMessageBox::information(this, "", "Open Failed", "OK", "CANCEL");

            return;
        }
    }

    framecount = 0;
    lostLineCount = 0;
    axImage->Grab(0);
    grabing = true;
}

void MainWindow::singleScanEnable(bool enable)
{
    qDebug()<<__FUNCTION__<<enable;
    singleScanEnabled = enable;
    if(singleScanEnabled) {
        axImage->SetDualScanMode(0);
        if(!grabing) {
            scan();
        }
    } else {
        stop();
    }
}

void MainWindow::dualScanEnable(bool enable)
{
    qDebug()<<__FUNCTION__<<enable;
    dualScanEnabled = enable;

    if(dualScanEnabled) {
        axImage->SetDualScanMode(1);
        if(!grabing) {
            scan();
        }
    } else {
        stop();
    }
}

void MainWindow::setting_clicked()
{
    //OPen setting dialog
}

void MainWindow::open_clicked()
{
//open file dialog

}

void MainWindow::saveButtonClick()
{
    if(!axImage->IsOpened())
        return;
    QString path = QFileDialog::getOpenFileName();
    QFile* file =  new QFile(path);
    if (!file) {
        file->open(QIODevice::WriteOnly|QIODevice::Append);
    }
    if (file) {
        int size = axImageObject->Width()*axImageObject->Height()*axImageObject->BytesPerPixel();
        long writed = 0;
        char* src = (char*)axImageObject->ImageDataAddress();
        while (size > 0) {
            writed = file->write((char*)src, size);
            src += writed;
            size -= writed;
        }
    }
}

void MainWindow::power_clicked()
{
    //exit
    QApplication::quit();
}


void MainWindow::contrastEnable(bool enable)
{
    qDebug() << __FUNCTION__<< enable;
    contrastEnabled = enable;//conflict with zoom and move
}

void MainWindow::invert_click()
{
    qDebug() << __FUNCTION__;
    int start = axDisplay->MapStart();
    int end = axDisplay->MapEnd();
    qDebug() << "Start = " << start;
    qDebug() << "end = " << end;
    axDisplay->SetMapStart(end);
    axDisplay->SetMapEnd(start);
    axDisplay->repaint();
    scene->update();
    view->view()->viewport()->update();

}

void MainWindow::autoContrast_clicked()
{
// 1find  minist of frame
//   2 find maximu of frame
//   3 set map range
    qDebug() << __FUNCTION__;
    int width = axImageObject->Width();
    int height = axImageObject->Height();
    int min = 0;
    int max = 0;

    for(int j=0; j < height; j++) {
        quint16* line = (quint16*)axImageObject->ImageLineAddress(0);
        for(int i = 0; i < width; i++) {
            //int v = axImageObject->Pixel(i, j);
            int v = *(line+i);
            if (max < v)
                max = v;
            if (min > v)
                min = v;
        }
    }
    qDebug() << "min = " << min;
    qDebug () << "max = " << max;
    axDisplay->SetMapStart(min);
    axDisplay->SetMapEnd(max);
    axDisplay->repaint();
    scene->update();
    view->view()->viewport()->update();
}

void MainWindow::zoomEnable(bool enable)
{
    zoomEnabled = enable;
    if(zoomEnabled) {
        view->zoomIn();
    }
}

void MainWindow::rotate_click()
{
    view->rotateRight();
}

void MainWindow::moveEnable(bool enable)
{
    zoomEnabled = enable;
    QString rt;
    if(enable){
        axCommander->SetDataPattern(1);
    }
    else
        axCommander->SetDataPattern(0);
}
