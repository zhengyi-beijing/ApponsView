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
    //populateScene();
    setMinimumSize(1024,768);
    resize(QSize(1280,1024));
    move(QApplication::desktop()->screen()->rect().center() - this->rect().center());

    createAxWidget();
    initAxWidget();

    panel = new Panel("Command Pannel");
    panel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    panel->setMinimumSize(64, 64);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(10);
    layout->setSpacing(5);
    layout->addWidget(axDisplay);
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


void MainWindow::widgetMoveto(QPoint dpos)
{
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
}


void MainWindow::showEvent(QShowEvent* event)
{
}

void MainWindow::SubFrameReady(int NumOfBlockLeft, int StartLine, int NumLines, int bLastBlock)
{
    //qDebug() << __FUNCTION__;
}

void MainWindow::FrameReady(int)
{
    framecount++;
    qDebug()<< "Frame count: "<< framecount;
    qDebug() << "Frame Ready thread id = " << QThread::currentThreadId();
    if (setting.autoSave()) {
        int size = axImageObject->Width()*axImageObject->Height()*axImageObject->BytesPerPixel();
        ImageData* data = new ImageData((char*)axImageObject->ImageDataAddress(), size);
        fileServer.append(data, setting.autoSavePath(), setting.autoSaveSize());
    }
    panel->frameCountLabel->setFrameCount(framecount);
}

void MainWindow::createAxWidget()
{
    axDetector = new DTControl::CDTDetector(this);
    axDetector->setVisible(false);

    axDisplay = new DTControl::CDTDisplay(this);
   // axDisplay = new Display(this);
    axDisplay->setVisible(false);

    axCommander = new DTControl::CDTCommanderF3(this);
    axCommander->setVisible(false);

    axImage = new DTControl::CDTImage(this);
    axImage->setVisible(false);
}

void MainWindow::initAxWidget()
{
    axDetector->SetChannelType(2);
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
    axImage->SetImgHeight(setting.height());
    axImage->SetImgWidth(setting.width());
    axImage->SetImagePort(4001);
    axImage->SetBytesPerPixel(2);
    //axImage->SetSubFrameHeight(32);
    axImage->setVisible(false);

    axDisplay->setVisible(true);
    axDisplay->setFocus(Qt::ActiveWindowFocusReason);
    //axDisplay->setMouseTracking(true);
    //QString String = "border: 2px solid black;";
    //axDisplay->setStyleSheet(String );
    axDisplay->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    axDisplay->SetDisplayScale(0);
    axDisplay->SetMapStart(100);
    axDisplay->SetMapEnd(10000);
    axDisplay->setMinimumSize(512,512);
    axDisplay->dynamicCall("SetDisplayScale(int)", 0);
    //axDisplay->SetRefreshMode(2);//Moving

    qDebug()<<"get ImageObject";
    IUnknown* imgsrcHandle =  axImage->ObjectHandle();
    qDebug()<<"get ImageObject end";
    if (imgsrcHandle) {
        qDebug()<<"Set Display Source";
        axDisplay->SetDataSource(imgsrcHandle);
    }

    //QObject::connect(axDisplay, SIGNAL(MouseMove(int, int, int)), this->panel->pixelInfoLabel, SLOT(setInfo(int, int, int)));
    //QObject::connect(axDisplay, SIGNAL(MouseMove(int, int, int)), this, SLOT(pixelInfo(int, int, int)));
    //QObject::connect(axDisplay,SIGNAL(MouseMove(int, int, int)), panel->pixelInfoLabel, SLOT(setInfo(int, int, int)));
    qDebug()<<"Connected mousemove";
    QObject::connect(axImage, SIGNAL(FrameReady(int)), this, SLOT(FrameReady(int)));
    QObject::connect(axImage, SIGNAL(Datalost(int)), this, SLOT(Datalost(int)));
    QObject::connect(axImage, SIGNAL(SubFrameReady(int, int, int, int)), this, SLOT(SubFrameReady(int, int, int, int)));
    if(!openDetector()){
        QMessageBox::information(this, "", "Open Detector Failed", "OK", "CANCEL");
    }
}

void MainWindow::pixelInfo(int x, int y, int v)
{
    qDebug() << "x ="<<x<<"   y="<< y<<"   v="<<v;
}

void MainWindow::setSpeed(int speed)
{
    float pixelSize = axCommander->PixelSize();
    qDebug()<<"PixelSize is mm"<< pixelSize;
    if(pixelSize < 0.1)
        pixelSize = 0.4;
    int time = pixelSize*1000000/(speed);
    qDebug()<<"Inetegration Time is us"<<time;
    axCommander->SetIntegrationTime(time);
}

void MainWindow::initDetector()
{
    QString rt;
   // axDetector->SendCommand(QString("[ED,M,0]"), rt);
    if(setting.dataPattern())
        axCommander->SetDataPattern(1);
    axCommander->SetSensitivityLevel(setting.sensitivityLevel());

    setSpeed(setting.scanSpeed());

    QString speed = QString("[SDS,%1]").arg(setting.scanSpeed());
    axDetector->SendCommand(speed, rt);

}

int MainWindow::openDetector()
{

    int opened = axDetector->Open();

    if (opened){
        initDetector();
        qDebug()<< "Detector Opened";
        int rt = axImage->Open();
        axImageObject = new DTControl::IImageObject((IDispatch*)axImage->ImageObject());

        if(rt) {
            qDebug()<<"open image ";
            rt = axDisplay->Open();
            axDisplayObject = new DTControl::IImageObject((IDispatch*)axDisplay->ImageObject());
            if(rt) {
                qDebug()<<"open Display sucesful";
            }
            else
                qDebug()<<"open display failed";
        }
        else
          qDebug()<<"Open Image failed" ;
        return true;
    }
    else {
        qDebug() << "OPen detector failed";
    }
    return false;
}

void MainWindow::connectSignals()
{
    QObject::connect(panel, &Panel::singleScanEnable, this, &MainWindow::singleScanEnable);
    QObject::connect(panel, &Panel::dualScanEnable, this, &MainWindow::dualScanEnable);
    QObject::connect(panel, &Panel::settingButton_click, this, &MainWindow::setting_clicked);
    QObject::connect(panel, &Panel::openButton_click, this, &MainWindow::open_clicked);
    QObject::connect(panel->saveButton, &QToolButton::clicked, this, &MainWindow::saveButtonClick);
    QObject::connect(panel, &Panel::powerButton_click, this, &MainWindow::power_clicked);
    QObject::connect(panel, &Panel::contrastEnable, this, &MainWindow::contrastEnable);
    QObject::connect(panel, &Panel::autoContrastButton_click, this, &MainWindow::autoContrast_clicked);
    QObject::connect(panel, &Panel::zoomEnable, this, &MainWindow::zoomEnable);
    QObject::connect(panel, &Panel::moveEnable, this, &MainWindow::moveEnable);
    QObject::connect(panel, &Panel::invertButton_click, this, &MainWindow::invert_click);
    QObject::connect(panel, &Panel::rotateButton_click, this, &MainWindow::rotate_click);

//    QObject::connect(view->view(), &GraphicsView::increaseContrastEnd, this, &MainWindow::increaseContrastEnd);
//    QObject::connect(view->view(), &GraphicsView::decreaseContrastEnd, this, &MainWindow::decreaseContrastEnd);
//    QObject::connect(view->view(), &GraphicsView::increaseContrastStart, this, &MainWindow::increaseContrastStart);
//    QObject::connect(view->view(), &GraphicsView::decreaseContrastStart, this, &MainWindow::decreaseContrastStart);

    QObject::connect(axDisplay,SIGNAL(MouseMove(int, int, int)), panel->pixelInfoLabel, SLOT(setInfo(int, int, int)));
}

void MainWindow::stop()
{
    axImage->Stop();
    grabing = false;
    timer.stop();
    QString rt;
    axDetector->SendCommand(QString("[SDR,0]"), rt);
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
    timer.setInterval(17);
    //QObject::connect(&timer,SIGNAL(timeout()), scene, SLOT(update()));
    timer.start();
    grabing = true;
    QString rt;
    axDetector->SendCommand(QString("[SDR,1]"), rt);
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
    ApponsSetting::showSettingDialog();
    setSpeed(setting.scanSpeed());
}

void MainWindow::open_clicked()
{
//open file dialog
    QString path = QFileDialog::getOpenFileName();
    QFile* file =  new QFile(path);
    if (!file->open(QIODevice::ReadOnly))
        return;
    QByteArray blob = file->readAll();

}

void MainWindow::saveButtonClick()
{
    qDebug()<<__FUNCTION__;
    if(!axImage->IsOpened()){
        QMessageBox::information(this, "", "No Image", "确定", "取消");
        return;
    }
    QString path = QFileDialog::getSaveFileName();
    QFile* file =  new QFile(path);
    if (file) {
        file->open(QIODevice::WriteOnly|QIODevice::Append);
        int size = axImageObject->Width()*axImageObject->Height()*axImageObject->BytesPerPixel();
        long writed = 0;
        char* src = (char*)axImageObject->ImageDataAddress();
        while (size > 0) {
            writed = file->write((char*)src, size);
            src += writed;
            size -= writed;
        }
        file->close();
    }
    else {
        QMessageBox::information(this, "", "File cannot open", "确定", "取消");
        return;
    }
}

void MainWindow::power_clicked()
{
    //exit
    QApplication::quit();
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
    axDisplay->dynamicCall("Repaint()");
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
        quint16* line = (quint16*)axImageObject->ImageLineAddress(j);
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
    //axDisplay->Repaint();
    axDisplay->dynamicCall("Repaint");
}

void MainWindow::zoomEnable(bool enable)
{
    zoomEnabled = enable;
    if(zoomEnabled) {
    } else {
    }
}

void MainWindow::rotate_click()
{
}

void MainWindow::moveEnable(bool enable)
{
    QString rt;
    if(enable){
        axCommander->SetDataPattern(1);
    }
    else
        axCommander->SetDataPattern(0);
}


int MainWindow::contrastStep()
{
    int start = axDisplay->MapStart();
    int end = axDisplay->MapEnd();
    int range = abs(start-end);
    if(range < 256)
        range = 256;
    if(range > 65535)
        range = 65535;
    qDebug()<< "range is " <<range;
    return  range / 5;
}

void MainWindow::increaseContrastStart()
{
    qDebug()<<__FUNCTION__;
    int step = contrastStep();
    int start = axDisplay->MapStart();
    step =100;
    start += step;
    axDisplay->SetMapStart(start);
    axDisplay->dynamicCall("Repaint()");
}

void MainWindow::decreaseContrastStart()
{
    qDebug()<<__FUNCTION__;
    int step = contrastStep();
    step =100;
    int start = axDisplay->MapStart();
    start -= step;
    axDisplay->SetMapStart(start);
    axDisplay->dynamicCall("Repaint()");

}

void MainWindow::increaseContrastEnd()
{
    qDebug()<<__FUNCTION__;
    int step = contrastStep();
    int end = axDisplay->MapEnd();
    //end += step;
    end += 100;
    axDisplay->SetMapEnd(end);
    axDisplay->dynamicCall("Repaint()");

}

void MainWindow::decreaseContrastEnd()
{
    qDebug()<<__FUNCTION__;
    int step = contrastStep();
    int end = axDisplay->MapEnd();
    //end -= step;
    if ((end -= 100) < 0)
        end = 0;

    qDebug() << "set end " << end;
    axDisplay->SetMapEnd(end);
    axDisplay->dynamicCall("Repaint()");
}

void MainWindow::contrastEnable(bool enable)
{
    qDebug() << __FUNCTION__<< enable;
    contrastEnabled = enable;//conflict with zoom and move
    if(contrastEnabled) {
        //view->view()->setMouseOpMode(GraphicsView::Contrast);
    } else {
        //view->view()->setMouseOpMode(GraphicsView::None);
    }
}
