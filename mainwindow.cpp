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
#include <QWizard>
#include <QWizardPage>

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
    resize(QSize(1024,768));
    move(QApplication::desktop()->screen()->rect().center() - this->rect().center());

    createAxWidget();
    initAxWidget();

    panel = new Panel("Command Pannel");
    panel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    panel->setMinimumSize(64, 64);

    panel->gain->setChecked(setting.isGainEnable());
    axCommander->SetCorrectionGain(setting.isGainEnable());

    panel->offset->setChecked(setting.isOffsetEnable());
    axCommander->SetCorrectionOffset(setting.isOffsetEnable());
    panel->autoSave->setChecked(setting.autoSave());
    QHBoxLayout *layout = new QHBoxLayout;

    layout->setMargin(1);
    layout->setSpacing(1);
   // layout->addWidget(view);
    layout->addWidget(plot);

    layout->addWidget(axDisplay);
    layout->addWidget(panel);
    setLayout(layout);

    setWindowTitle(tr("ApponsView"));
    connectSignals();
    singleScanEnabled = 1;

    dualScanEnabled = false;
    grabing = false;
    calibrationWiz = NULL;

    fileServer.start();
}

MainWindow::~MainWindow()
{
    fileServer.stop();
    fileServer.wait(2000);
    setting.save();
}


void MainWindow::populateScene()
{
    createAxWidget();
    initAxWidget();
    plot->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    plot->setMinimumSize(512,512);

    /*
    scene = new Scene;
    axDisplay->setParent(NULL);
    proxy = new Proxy();
    proxy->setWidget(axDisplay);
    //proxy->setWidget(new QPushButton(NULL));
    proxy->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);
    scene->addItem(proxy);
    //proxy = scene->addWidget(axDisplay);
    //scene->setSceneRect(scene->itemsBoundingRect());
    qDebug()<<"scene rect is "<<scene->sceneRect();
    qDebug()<<"proxy rect is "<<proxy->rect();

    //axDisplay->show();
    axDisplay->setVisible(true);
    axDisplay->setFocus(Qt::ActiveWindowFocusReason);
    axDisplay->setMouseTracking(true);
    axDisplay->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    qDebug()<<"Display size is "<<axDisplay->rect();


    view = new View("X-ray view");
    view->view()->setScene(scene);
    view->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    view->setMinimumSize(512, 512);
    view->resetView();
    */
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

    //fitToScene();
}

void MainWindow::switchDisplay()
{
    if(!plot->isVisible()) {
        plot->setVisible(true);
        //view->setVisible(false);
        axDisplay->setVisible(false);
    } else {
        plot->setVisible(false);
        //view->setVisible(true);
        axDisplay->setVisible(true);
    }


}

void MainWindow::SubFrameReady(int NumOfBlockLeft, int StartLine, int NumLines, int bLastBlock)
{

    //The axImageObject is not available in the subfarame event.
}

void MainWindow::updatePlot()
{
  //  qDebug() << __FUNCTION__;
    if(!plot->isVisible())
        return;
    //int width = axImageObject->Width();
    int startPixel = setting.startPixel();
    int endPixel = setting.endPixel();

    if((endPixel > axImageObject->Width()) || (endPixel <= 0))
        endPixel = axImageObject->Width();
    if(startPixel >= endPixel)
        startPixel = 0;
    int width = endPixel-startPixel+1;
    QVector<double> x(width), y(width);
    int i = 0;
    int j = 0;
    int max = 0;
   // int min = 0;
    int StartLine = 0;
    int EndLine = axImageObject->Height();
    int NumLines = axImageObject->Height();
    //get average col value store into y[]
#pragma omp parallel for private(i,j)
    for (j = StartLine; j < EndLine; j++) {
        quint16* pbase = NULL;
        pbase = (quint16*)axImageObject->ImageLineAddress(j);
        for (i=startPixel; i <= endPixel; i++) {
            y[i-startPixel] += *(pbase+i);
        }
    }

    for(i =startPixel; i <= endPixel; i++) {
        x[i-startPixel] = i-startPixel;
        y[i-startPixel] /= NumLines;
        if(y[i-startPixel] > max)
            max = y[i-startPixel];
    }

    plot->setData(&x, &y);


}

void MainWindow::FrameReady(int)
{
    int framePerFile = setting.autoSaveFrames();
    framecount++;
    //qDebug()<< "Frame count: "<< framecount;
    //qDebug()<< "FramesPerFile : "<< framePerFile;

    updatePlot();
    //if (setting.autoSave()) {
    if(panel->autoSave->isChecked()){
        qDebug() << "autoSave checked \n";
        if(framecount == 1) {
            qDebug()<<"Clear Buffer\n";
            fileServer.clearBuffer();
        }
        int startPixel = setting.startPixel();
        int endPixel = setting.endPixel();

        if((endPixel > axImageObject->Width()) || (endPixel <= 0))
            endPixel = axImageObject->Width();
        if(startPixel >= endPixel)
            startPixel = 0;
        int width = endPixel-startPixel+1;

        int bytesPerPixel = axImageObject->BytesPerPixel();

        int sizePerLine = width*bytesPerPixel;
            ImageData* data = NULL;
            int i = 0;
            char* temp = NULL;
            int blockSize = sizePerLine * axImageObject->Height();
            qDebug() << "blockSize = " << blockSize;
            temp = (char*)malloc (blockSize);
            int offset = 0;
            for(i = 0; i < axImageObject->Height(); i++) {
                memcpy(temp+offset, (void*)(axImageObject->ImageLineAddress(i)+(startPixel<<1)),sizePerLine);
                offset += sizePerLine;
            }

            if(framecount%framePerFile) {

                data = new ImageData(temp,blockSize, false);

            } else {

                data = new ImageData(temp,blockSize, true);

            }
            fileServer.append(data, setting.autoSavePath(), setting.autoSaveSize());
            if(temp) {
                free(temp);
                temp = NULL;
            }

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

    //plot = new QCustomPlot(this);
    plot = new PlotWidget(this);
   // plot->setRange(0, setting.endPixel()-setting.startPixel());
    plot->setVisible(true);
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
  //  axImage->SetImgHeight(320);
    axImage->SetImgWidth(setting.width());
    axImage->SetImagePort(4001);
    axImage->SetBytesPerPixel(2);
 //   axImage->SetSubFrameHeight(32);
    axImage->setVisible(false);
    axImage->SetDualScanMode(1);


    axDisplay->setVisible(true);
    axDisplay->setFocus(Qt::ActiveWindowFocusReason);
    //axDisplay->setMouseTracking(true);
    //QString String = "border: 2px solid black;";
    //axDisplay->setStyleSheet(String );
    axDisplay->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    if(setting.MixOrder()) {
        axImage->SetPixelOrderEnable(true);
    }
    if(setting.revert()) {
        axImage->SetRevert(1);
    }

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
    } else {
       // axCommander->LoadOffset();
       // axCommander->LoadGain(1);
    }
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeroutHandle()));
    timer->setInterval(1000);

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
//    int time = pixelSize*1000000/(speed);
//    qDebug()<<"Inetegration Time is us"<<time;
    int time = speed;
    axCommander->SetIntegrationTime(time);

    int scanspeed = pixelSize*1000000/time;
    QString rt;
    QString speedinfo = QString("[SDS,%1]").arg(scanspeed);
    axDetector->SendCommand(speedinfo, rt);
}

void MainWindow::initDetector()
{
    QString rt;
   // axDetector->SendCommand(QString("[ED,M,0]"), rt);
    if(setting.dataPattern())
        axCommander->SetDataPattern(1);
    axCommander->SetSensitivityLevel(setting.sensitivityLevel());

    setSpeed(setting.scanSpeed());


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

void MainWindow::gainChanged(bool b)
{
    setting.setGainEnable(b);
    if(setting.isGainEnable())
        axCommander->SetCorrectionGain(1);
    else
        axCommander->SetCorrectionGain(0);
}

void MainWindow::offsetChanged(bool b)
{
    setting.setOffsetEnable(b);

    if(setting.isOffsetEnable())
        axCommander->SetCorrectionOffset(1);
    else
        axCommander->SetCorrectionOffset(0);
}

void MainWindow::autoSaveChanged(bool b)
{
    setting.setAutoSave(b);
    framecount = 0;
    fileServer.clearBuffer();
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


    QObject::connect(panel, &Panel::calibrationButton_click, this, &MainWindow::calibration_click);
    QObject::connect(panel, &Panel::plotButton_click, this, &MainWindow::switchDisplay);
    QObject::connect(panel->autoSave, &QCheckBox::stateChanged, this, &MainWindow::autoSaveChanged);
    QObject::connect(panel->gain, &QCheckBox::stateChanged, this, &MainWindow::gainChanged);
    QObject::connect(panel->offset, &QCheckBox::stateChanged, this, &MainWindow::offsetChanged);


    QObject::connect(axDisplay,SIGNAL(MouseMove(int, int, int)), panel->pixelInfoLabel, SLOT(setInfo(int, int, int)));

    QObject::connect(&setting, &ApponsSetting::normalize, this, &MainWindow::calibration_click);
}

void MainWindow::stop()
{
    axImage->Stop();
    grabing = false;
    //timer.stop();
    fileServer.clearBuffer();
    QTimer::singleShot(1000, this, SLOT(grabStatus()));
    timer->stop();
    lostLineCount = 0;
}

void MainWindow::grabStatus()
{
    QString rt;
    if(grabing) {
        axDetector->SendCommand(QString("[SDR,1]"), rt);
    } else {
        axDetector->SendCommand(QString("[SDR,0]"), rt);
    }


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
    QTimer::singleShot(2000, this, SLOT(grabStatus()));
    timer->start(1000);
    qDebug() << "timer start";

}

void MainWindow::singleScanEnable(bool enable)
{
    qDebug()<<__FUNCTION__<<enable;
    //singleScanEnabled = enable;
    if(singleScanEnabled) {
        axImage->SetDualScanMode(1);
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
    dualScanEnabled = setting.dualMode();

    if(dualScanEnabled) {
        axImage->SetDualScanMode(1);
    } else {
        axImage->SetDualScanMode(1);
    }

    if(!grabing) {
        scan();
    } else {
        stop();
    }
}

void MainWindow::setting_clicked()
{
    //OPen setting dialog
    setting.showSettingDialog();
    setSpeed(setting.scanSpeed());

    if(setting.dataPattern())
        axCommander->SetDataPattern(1);
    else
        axCommander->SetDataPattern(0);

//    if(setting.isGainEnable())
//        axCommander->SetCorrectionGain(1);
//    else
//        axCommander->SetCorrectionGain(0);

//    if(setting.isOffsetEnable())
//        axCommander->SetCorrectionOffset(1);
//    else
//        axCommander->SetCorrectionOffset(0);
    axCommander->SetSensitivityLevel(setting.sensitivityLevel());
  //  plot->setRange(0, setting.endPixel()-setting.startPixel());
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


QWizardPage* getShutDownXPage()
{
    QWizardPage *page = new QWizardPage;
         page->setTitle("Calibration");
    QLabel *label = new QLabel("Please shutdown the x-ray source");
    label->setWordWrap(true);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    page->setLayout(layout);
    return page;
}

QWizardPage* getOffsetWaitingPage()
{
    QWizardPage *page = new QWizardPage;
         page->setTitle("Calibration");
    QLabel *label = new QLabel("Offset calibration done");
    label->setWordWrap(true);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    page->setLayout(layout);

    return page;
}

QWizardPage* getOpenXPage()
{
    QWizardPage *page = new QWizardPage;
         page->setTitle("Calibration");
    QLabel *label = new QLabel("Open X-ray source, click next when x-ray ready");
    label->setWordWrap(true);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    page->setLayout(layout);

    return page;
}

QWizardPage* getGainWaitingPage()
{
    QWizardPage *page = new QWizardPage;
         page->setTitle("Calibration");
    QLabel *label = new QLabel("Gain calibration done");
    label->setWordWrap(true);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    page->setLayout(layout);

    return page;
}

void MainWindow::calibration_click()
{
    initCalibrationWiz();
    calibrationWiz->show();
}

void MainWindow::calibrationProc (int id)
{
    qDebug() << "id is " << id;
    if(0 == id) {
        //off x-ray
    } else if (1 == id) {
        //do offset calibraion
//        axCommander->SetStartPixel(setting.startPixel());
//        axCommander->SetEndPixel(setting.endPixel());
        axCommander->SetBaseline(0);
        axCommander->SetCorrectionOffset(0);
        axCommander->SetCorrectionGain(0);
        axCommander->OnBoardOffsetCalibration();

    } else if (2 == id) {
        axCommander->SaveOffset();
        axCommander->SetCorrectionOffset(1);
        //open x-ray

    } else if (3 == id) {
        //do gain operation
        axCommander->OnBoardGainCalibration(setting.targetValue());
        axCommander->SaveGain(1);
        axCommander->SetCorrectionGain(1);
       //change next
    } else if (4 == id) {
        //save to pos 1
       //finish
    }
}

void MainWindow::initCalibrationWiz ()
{
    if(calibrationWiz){
        calibrationWiz->restart();
        return;
    }
    QWizardPage* shutDownXPage = getShutDownXPage();
    QWizardPage* offsetWaitingPage = getOffsetWaitingPage();
    QWizardPage* openXPage = getOpenXPage();
    QWizardPage* donePage = getGainWaitingPage();

    calibrationWiz = new QWizard(this);
    calibrationWiz->setVisible(false);
    calibrationWiz->addPage(shutDownXPage);
    calibrationWiz->addPage(offsetWaitingPage);
    calibrationWiz->addPage(openXPage);
    calibrationWiz->addPage(donePage);

    QObject::connect(calibrationWiz, &QWizard::currentIdChanged, this, &MainWindow::calibrationProc);
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

void MainWindow::timeroutHandle()
{
    QString msg;
     //   qDebug() << "call timer";
    axDetector->SendCommand(QString("[SDQ]"), msg);
    //qDebug() << "msg is " <<  msg ;
    panel->setProxyInfo(msg);
}
