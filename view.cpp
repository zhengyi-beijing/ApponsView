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

#include "view.h"
#ifndef QT_NO_OPENGL
#include <QtOpenGL>
#else
#include <QtWidgets>
#endif

void GraphicsView::wheelEvent(QWheelEvent *e)
{
    qDebug() << __FUNCTION__;
    if (e->modifiers() & Qt::ControlModifier) {
        if (e->delta() > 0)
            view->zoomIn();
        else
            view->zoomOut();
        e->accept();
    } else {
        QGraphicsView::wheelEvent(e);
    }
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    qDebug() << __FUNCTION__<< event->pos();
    qDebug() << __FUNCTION__<< event->button();
    mousePressed = true;
}

void GraphicsView::mouseReleaseEvent ( QMouseEvent * event )
{

    mousePressed = false;
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << __FUNCTION__<< event->pos();
    qDebug() << __FUNCTION__<< event->button();
    if(mousePressed) {
        if(mode == Move) {

        } else if (mode == Zoom) {

        } else { //contrast

        }
    }
}

View::View(const QString &name, QWidget *parent)
    : QFrame(parent)
{
    //setFrameStyle(Sunken | StyledPanel);
    setFrameStyle(Sunken | NoFrame);
    graphicsView = new GraphicsView(this);
    graphicsView->setRenderHint(QPainter::Antialiasing, false);
    graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    graphicsView->setCacheMode(QGraphicsView::CacheNone);
    graphicsView->setDragMode(QGraphicsView::NoDrag);
    graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);


    QVBoxLayout *topLayout = new QVBoxLayout;
    topLayout->addWidget(graphicsView);
    topLayout->setMargin(1);
    setLayout(topLayout);

    scale = 1.0;
    rotate = 0;
    setupMatrix();
}

QGraphicsView *View::view() const
{
    return static_cast<QGraphicsView *>(graphicsView);
}

void View::resetView()
{
    setupMatrix();
    graphicsView->ensureVisible(QRectF(0, 0, 0, 0));
    graphicsView->fitInView(graphicsView->scene()->itemsBoundingRect(),Qt::KeepAspectRatio);
}

void View::setupMatrix()
{
    //QMatrix matrix;
    //graphicsView->setMatrix(matrix);
    QMatrix matrix;
    matrix.scale(scale, scale);
    matrix.rotate(rotate);

    graphicsView->setMatrix(matrix);
}


void View::toggleOpenGL()
{
#ifndef QT_NO_OPENGL
    graphicsView->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
#endif
}

void View::toggleAntialiasing()
{
    graphicsView->setRenderHint(QPainter::Antialiasing);
}

void View::zoomIn()
{
    scale *= 1.2;
    setupMatrix();
}

void View::zoomOut()
{
    scale /= 1.2;
    setupMatrix();
}

void View::rotateLeft()
{
    rotate -= 90;
    setupMatrix();
}

void View::rotateRight()
{
    rotate += 90;
    setupMatrix();
}

//void On

PanelButton::PanelButton(const QString resPath, QWidget *parent, bool group)
    :QToolButton(parent)
{
    int size = 64;
    QSize iconSize(size, size);
    QIcon icon;
    QPixmap pixmap = QPixmap(resPath).scaled(iconSize);
    icon.addPixmap(pixmap);
    setIcon(icon);
    setIconSize(iconSize);
    //openButton->setMask(img.mask());
    if(group) {
        setAutoRaise(true);
        setCheckable(true);
    } else {
        setAutoRaise(true);
        setCheckable(true);
    }

}

Panel::Panel(const QString &name, QWidget *parent)
    :QFrame(parent)
{
    setFrameStyle(QFrame::NoFrame);
   // int size = style()->pixelMetric(QStyle::PM_ToolBarIconSize);

    openButton = new PanelButton(":/Appons/res/open.ico");

    saveButton = new PanelButton(":/Appons/res/save.ico", 0, true);

    settingButton = new PanelButton(":/Appons/res/setting.ico");
    powerButton = new PanelButton(":/Appons/res/exit.ico");
    contrastButton = new PanelButton(":/Appons/res/contrast.ico", 0, true);
    autoContrastButton = new PanelButton(":/Appons/res/autoContrast.ico");
    //Todo proxy Panel
    zoomButton = new PanelButton(":/Appons/res/zoomIn.ico", 0, true);
    moveButton = new PanelButton(":/Appons/res/move.ico", 0, true);
    singleScanButton = new PanelButton(":/Appons/res/singleScan.ico", 0, true);
    dualScanButton = new PanelButton(":/Appons/res/dualScan.ico", 0, true);
    invertButton = new PanelButton(":/Appons/res/invert.ico", 0);
    rotateButton = new PanelButton(":/Appons/res/rotate.ico", 0);

    clock = new DigitalClock(this);

    QGridLayout *panelLayout = new QGridLayout;
    panelLayout->addWidget(openButton, 0,0);
    panelLayout->addWidget(saveButton, 0,1);
    panelLayout->addWidget(settingButton, 1,0);
    panelLayout->addWidget(powerButton, 1,1);
    panelLayout->addWidget(contrastButton, 2,0);
    panelLayout->addWidget(autoContrastButton, 2,1);
    panelLayout->addWidget(zoomButton, 3,0);
    panelLayout->addWidget(moveButton, 3,1);
    panelLayout->addWidget(invertButton, 4,0);
    panelLayout->addWidget(rotateButton, 4,1);
    panelLayout->addWidget(singleScanButton, 5,0);
    panelLayout->addWidget(dualScanButton, 5,1);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(panelLayout);

    //QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Expanding);

    //vLayout->addSpacerItem(spacer);
    vLayout->addStretch();
    vLayout->addWidget(clock);
    //vLayout->addSpacerItem(spacer1);
    setLayout(vLayout);

    setBackgroundImage();
    signalInit();

    dualScanEnabled = false;
    singleScanEnabled = false;

    zoomEnabled = false;
    moveEnabled = false;
    contrastEnabled = false;
    autoSaveEnabled = false;
}

void Panel::setBackgroundImage()
{
    setAutoFillBackground(true);
    //setStyleSheet("background-image: url(:Appons/res/background.bmp)}" );
    setStyleSheet("background-color: rgb(34,139,34)}" );
/*
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(192,253,123));
    QSize size = this->size();
    //QPixmap img(":Appons/res/background.bmp");
    //img.scaled(size);
    //palette.setBrush(QPalette::Background, QBrush(img));
    palette.setBrush(QPalette::Background, QBrush(QColor(Qt::darkGreen)));
    setPalette(palette);
    */
}

void Panel::openButton_handle()
{
    emit openButton_click();
}

void Panel::saveButton_handle()
{
    autoSaveEnabled = !autoSaveEnabled;
    emit autoSaveEnable(autoSaveEnabled);
}

void Panel::powerButton_handle()
{
    emit powerButton_click();
}

void Panel::contrastButton_handle()
{
    contrastEnabled = !contrastEnabled;
    if(contrastEnabled) {
        zoomEnabled = false;
        moveEnabled = false;
    }
    setMousePressGroupButton();
    emit contrastEnable(contrastEnabled);
}

void Panel::autoContrastButton_handle()
{
    emit autoContrastButton_click();
}

void Panel::zoomButton_handle()
{
    zoomEnabled = !zoomEnabled;
    if(zoomEnabled){
        contrastEnabled = false;
        moveEnabled = false;
    }

    setMousePressGroupButton();
    emit zoomEnable(zoomEnabled);
}

void Panel::moveButton_handle()
{
    moveEnabled = !moveEnabled;
    if(moveEnabled){
        contrastEnabled = false;
        zoomEnabled = false;
    }
    setMousePressGroupButton();
    emit moveEnable(moveEnabled);
}

void Panel::setMousePressGroupButton()
{
   zoomButton->setChecked(zoomEnabled);
   moveButton->setChecked(moveEnabled);
   contrastButton->setChecked(contrastEnabled);
}

void Panel::setScanButtonGroup()
{
    singleScanButton->setChecked(singleScanEnabled);
    dualScanButton->setChecked(dualScanEnabled);
}

void Panel::singleScanButton_handle()
{
    singleScanEnabled = !singleScanEnabled;
    if (singleScanEnabled) {
        dualScanEnabled = false;
    }

    setScanButtonGroup();
    emit singleScanEnable(singleScanEnabled);
}

void Panel::dualScanButton_handle()
{
    dualScanEnabled = !dualScanEnabled;
    if(dualScanEnabled) {
        singleScanEnabled = false;
    }
    setScanButtonGroup();
    qDebug() << __FUNCTION__;
    emit dualScanEnable(dualScanEnabled);
}

void Panel::invertButton_handle()
{
    emit invertButton_click();
}

void Panel::rotateButton_handle()
{
    emit rotateButton_click();
}

void Panel::signalInit()
{
    connect(openButton, SIGNAL(clicked()),this,SLOT(openButton_handle()));
    connect(saveButton, SIGNAL(clicked()),this,SLOT(saveButton_handle()));
    connect(powerButton, SIGNAL(clicked()),this,SLOT(powerButton_handle()));
    connect(contrastButton, SIGNAL(clicked()),this,SLOT(contrastButton_handle()));
    connect(autoContrastButton, SIGNAL(clicked()),this,SLOT(autoContrastButton_handle()));
    connect(zoomButton, SIGNAL(clicked()),this,SLOT(zoomButton_handle()));
    connect(moveButton, SIGNAL(clicked()),this,SLOT(moveButton_handle()));
    connect(dualScanButton, SIGNAL(clicked()),this,SLOT(dualScanButton_handle()));
    connect(singleScanButton, SIGNAL(clicked()), this, SLOT(singleScanButton_handle()));
    connect(invertButton, SIGNAL(clicked()),this,SLOT(invertButton_handle()));
    connect(rotateButton, SIGNAL(clicked()), this, SLOT(rotateButton_handle()));
}
