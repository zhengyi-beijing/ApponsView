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
    populateScene();
    setMinimumSize(1024,768);
    resize(QSize(1024,768));
    move(QApplication::desktop()->screen()->rect().center() - this->rect().center());


    panel = new Panel("Command Pannel");
    panel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    panel->setMinimumSize(64, 64);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(1);
    layout->setSpacing(1);
    layout->addWidget(view);
    layout->addWidget(plot);
    //layout->addWidget(axDisplay);
    layout->addWidget(panel);
    setLayout(layout);

    setWindowTitle(tr("ApponsView"));
    connectSignals();

    dualScanEnabled = false;
    autoSaveEnabled = false;
    grabing = false;
    calibrationWiz = NULL;

    fileServer.start();
}

MainWindow::~MainWindow()
{
}

void MainWindow::populateScene()
{
    //scene = new QGraphicsScene;
    scene = new Scene;
    createAxWidget();
    initAxWidget();
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

    plot->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    plot->setMinimumSize(512,512);
    plot->xAxis->setLabel("pixel");
    plot->yAxis->setLabel("value");
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
 //   fitToScene();
}

void MainWindow::fitToScene()
{
    //qDebug()<<"proxy "<< proxy->rect();
    view->resetView();
}

void MainWindow::showEvent(QShowEvent* event)
{
    fitToScene();
}

void MainWindow::switchDisplay()
{
    if(!plot->isVisible()) {
        plot->setVisible(true);
        view->setVisible(false);
    } else {
        plot->setVisible(false);
        view->setVisible(true);
    }


}

void MainWindow::SubFrameReady(int NumOfBlockLeft, int StartLine, int NumLines, int bLastBlock)
{
    qDebug() << __FUNCTION__;
    if(!plot->isVisible())
        return;
    //scene->update();
    int width = axImageObject->Width();
    QVector<double> x(width), y(width);
    int i = 0;
    int j = 0;
    int max = 0;
    int min = 0;
    int EndLine = StartLine + NumLines;
    qDebug() << "StartLine "<< StartLine;
    qDebug() << "NumLines"<< NumLines;
    //get average col value store into y[]
    for (j = StartLine; j < EndLine; j++) {
        quint16* pbase = NULL;
        pbase = (quint16*)axImageObject->ImageLineAddress(j);
        for (i=0; i < width; i++) {
            y[i] += *(pbase+i);
        }
    }

    for(i =0; i < width; i++) {
        x[i] = i;
        y[i] /= NumLines;
        if(y[i] > max)
            max = y[i];
    }

    plot->xAxis->setRange(0, width);
    plot->yAxis->setRange(0, max+100);
    plot->graph(0)->setData(x, y);
    plot->replot();
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
    //scene->update();
    //view->view()->viewport()->update();
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

    plot = new QCustomPlot(this);
    plot->setVisible(false);
    plot->addGraph();
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
    axImage->SetImgHeight(setting.height());
    axImage->SetImgWidth(setting.width());
    axImage->SetImagePort(4001);
    axImage->SetBytesPerPixel(2);
    axImage->SetSubFrameHeight(32);
    axImage->setVisible(false);

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
    QObject::connect(axDisplay, SIGNAL(MouseMove(int, int, int)), this, SLOT(pixelInfo(int, int, int)));
    //QObject::connect(axDisplay,&DTControl::CDTDisplay::MouseMove, this->panel->pixelInfoLabel, PixelInfoLabel::setInfo);
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

    QObject::connect(panel, &Panel::calibrationButton_click, this, &MainWindow::calibration_click);
    QObject::connect(panel, &Panel::plotButton_click, this, &MainWindow::switchDisplay);

    QObject::connect(view->view(), &GraphicsView::increaseContrastEnd, this, &MainWindow::increaseContrastEnd);
    QObject::connect(view->view(), &GraphicsView::decreaseContrastEnd, this, &MainWindow::decreaseContrastEnd);
    QObject::connect(view->view(), &GraphicsView::increaseContrastStart, this, &MainWindow::increaseContrastStart);
    QObject::connect(view->view(), &GraphicsView::decreaseContrastStart, this, &MainWindow::decreaseContrastStart);

    QObject::connect(axDisplay,SIGNAL(MouseMove(int, int, int)), panel->pixelInfoLabel, SLOT(setInfo(int, int, int)));

    QObject::connect(&setting, &ApponsSetting::normalize, this, &MainWindow::calibration_click);
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
    QObject::connect(&timer,SIGNAL(timeout()), scene, SLOT(update()));
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
    setting.showSettingDialog();
    setSpeed(setting.scanSpeed());
    if(setting.dataPattern())
        axCommander->SetDataPattern(1);
    else
        axCommander->SetDataPattern(0);

    if(setting.isGainEnable())
        axCommander->SetCorrectionGain(1);
    else
        axCommander->SetCorrectionGain(0);

    if(setting.isOffsetEnable())
        axCommander->SetCorrectionOffset(1);
    else
        axCommander->SetCorrectionOffset(0);
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
    scene->update();
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
    scene->update();
    view->view()->viewport()->update();
}

void MainWindow::zoomEnable(bool enable)
{
    zoomEnabled = enable;
    if(zoomEnabled) {
      //  view->zoomIn();
        view->view()->setMouseOpMode(GraphicsView::Zoom);
    } else {
        view->view()->setMouseOpMode(GraphicsView::None);
        view->resetView();
    }
}

void MainWindow::rotate_click()
{
    view->rotateRight();
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
        //qApp->thread()->msleep(3000);
        axCommander->OnBoardOffsetCalibration();

    } else if (2 == id) {
        axCommander->SaveOffset();
        axCommander->SetCorrectionOffset(1);
        //open x-ray

    } else if (3 == id) {
        //do gain operation
        axCommander->OnBoardGainCalibration(1);
       //change next
    } else if (4 == id) {
        //save to pos 1
        axCommander->SaveGain(1);
        axCommander->SetCorrectionGain(1);
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
    scene->update();
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
    scene->update();

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
    scene->update();

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
    scene->update();
}

void MainWindow::contrastEnable(bool enable)
{
    qDebug() << __FUNCTION__<< enable;
    contrastEnabled = enable;//conflict with zoom and move
    if(contrastEnabled) {
        view->view()->setMouseOpMode(GraphicsView::Contrast);
    } else {
        view->view()->setMouseOpMode(GraphicsView::None);
    }
}
