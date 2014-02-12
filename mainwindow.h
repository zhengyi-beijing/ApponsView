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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QFrame>
#include <QAxObject>
#include <ActiveQt/QAxWidget>
#include "view.h"
#include <QGraphicsScene>
#include "dtcontrol.h"
#include "filestoreserver.h"
#include <QGraphicsProxyWidget>
#include <QSettings>
#include <QTimer>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include "apponssetting.h"
#include <QWizard>
#include "plotwidget.h"

class Scene :public QGraphicsScene
{
    Q_OBJECT
public :
//void mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent )
//{
//    qDebug()<<"scene mouse move vent sceene pos is "<< mouseEvent->scenePos();
//    QGraphicsScene::mouseMoveEvent(mouseEvent);
//}

};

class Display : public DTControl::CDTDisplay
{
    Q_OBJECT
public:
    Display(QWidget* parent = 0):CDTDisplay(parent)
    {
        setMouseTracking(true);
       // installEventFilter(this);
    }

    void mouseMoveEvent ( QMouseEvent * event )
    {
        qDebug()<<"------Display MouseMove Event " << event->pos();
        QAxWidget::mouseMoveEvent(event);
    }
public slots:
//    bool eventFilter(QObject *object, QEvent *event){
//           qDebug()<<"Display event type  is " << event->type();
//           if(object==this && (event->type()==QEvent::Enter || event->type()==QEvent::Leave))
//               if(event->type()==QEvent::Enter)
//                   qDebug() << "Hovering";
//               else
//                   qDebug() << "Not Hovering";
//           return QWidget::eventFilter(object, event);
//       }

};

class Proxy: public QGraphicsProxyWidget
{
public:
    Proxy(QGraphicsItem * parent=0):QGraphicsProxyWidget(parent)
    {
        setAcceptHoverEvents(false);
        setFlag(ItemIsFocusable);
        setFlag(ItemIsSelectable);
    }
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event)
    {
        qDebug()<<__FUNCTION__<<"pos "<<event->pos();
        qDebug()<< "rect is " << rect();
        qDebug() << "widget is " << widget();
        QGraphicsProxyWidget::hoverMoveEvent(event);
    }

    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        //event->ignore();
        //event->accept();
        qDebug()<<__FUNCTION__;
        QGraphicsProxyWidget::mousePressEvent(event);
    }

    void mouseMoveEvent ( QGraphicsSceneMouseEvent * event )
    {
         qDebug()<<"-------Proxy mouse move scence "<< event->scenePos();
         QGraphicsProxyWidget::mouseMoveEvent(event);
    }
};

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static ApponsSetting setting;
public slots:
    void singleScanEnable(bool enable);
    void dualScanEnable(bool enable);
    void setting_clicked();
    void open_clicked();
    void power_clicked();
    void contrastEnable(bool enable);
    void saveButtonClick();
    void autoContrast_clicked();
    void zoomEnable(bool enable);
    void moveEnable(bool enable);
    void rotate_click();
    void invert_click();
    void calibration_click();
    void widgetMoveto(QPoint pos);

    void increaseContrastStart();
    void decreaseContrastStart();
    void increaseContrastEnd();
    void decreaseContrastEnd();
    void switchDisplay();

protected:
    void resizeEvent(QResizeEvent * event);
    void showEvent (QShowEvent * event );
private:
    void connectSignals();
    void setupMatrix();
    void populateScene();
    void initAxWidget();
    void initCalibrationWiz ();
    void createAxWidget();
    int openDetector();
    void initDetector();
    void scan();
    void stop();
    int contrastStep();
    void setSpeed(int speed);

    QTimer timer;
    Scene *scene;
    Panel *panel;
    View *view;
    FileStoreServer fileServer;

    bool dualScanEnabled ;
    bool singleScanEnabled;
    bool autoSaveEnabled;
    bool zoomEnabled;
    bool moveEnabled;
    bool contrastEnabled;
    bool autoContrastEnabled;

    int framecount ;
    int lostLineCount;
    bool grabing;

    //QGraphicsProxyWidget* proxy;
    Proxy* proxy;
    DTControl::CDTDisplay* axDisplay;
    //Display* axDisplay;
    //DTControl::CDTDisplay* axDisplayWidget;
    DTControl::CDTImage* axImage;
    DTControl::CDTDetector* axDetector;
    DTControl::CDTCommanderF3* axCommander;
    DTControl::IImageObject* axDisplayObject;
    DTControl::IImageObject* axImageObject;

    //QCustomPlot* plot;
    PlotWidget* plot;

    QWizard* calibrationWiz;

    QString ip;

private slots:
    void ImageOpened();
    void SubFrameReady (int NumOfBlockLeft, int StartLine, int NumLines, int bLastBlock);
    void FrameReady(int);
    void Datalost(int num);
    void pixelInfo(int x, int y, int v);
    void fitToScene();
    void calibrationProc (int id);
};

#endif // MAINWINDOW_H
