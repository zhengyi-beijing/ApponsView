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

#ifndef VIEW_H
#define VIEW_H

#include <QFrame>
#include <QGraphicsView>
#include <QToolButton>
#include "digitalclock.h"
#include <QLabel>
#include <QPushButton>
#include <QResizeEvent>
#include <QTimer>
#include <QPoint>
#include <QCheckBox>
class View;
class QGLWidget;

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    enum Mode {None, Move, Zoom, Contrast};
    GraphicsView(View *v) : QGraphicsView(), view(v)
    {
        mode = None;
        setInteractive(true);
        moveThreshold = 10;
        mousePressed = false;
    }
    void setMouseOpMode(Mode m) { mode = m; }

signals:
    void zoomIn();
    void zoomOut();
    void increaseContrastStart();
    void decreaseContrastStart();
    void increaseContrastEnd();
    void decreaseContrastEnd();

protected:
    void wheelEvent(QWheelEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent * event);
    void resizeEvent(QResizeEvent *event) {
    }
private:
    View *view;
    Mode mode;
    bool mousePressed;
    QPoint start;
    int moveThreshold;
};

class View : public QFrame
{
    Q_OBJECT
public:
    explicit View(const QString &name, QWidget *parent = 0);

    GraphicsView *view() const;

public slots:
    void zoomIn();
    void zoomOut();
    void rotateLeft();
    void rotateRight();
    void resetView();

private slots:
    void setupMatrix();
    void toggleOpenGL();
    void toggleAntialiasing();

private:
    GraphicsView *graphicsView;
    qreal scale;
    qreal rotate;
    QGLWidget* glWidget;
    QTimer timer;
};

class PanelButton: public QToolButton
{
    Q_OBJECT
public:
    explicit PanelButton(const QString resPath, QWidget *parent = 0, bool group = false, QSize size = QSize(64,64));

};

class Panel: public QFrame
{
    Q_OBJECT
public:
    explicit Panel(const QString &name, QWidget *parent = 0);
signals:
    void openButton_click();
    void autoSaveEnable(bool enable);
    void powerButton_click();
    void contrastEnable(bool enable);
    void autoContrastButton_click();
    void zoomEnable(bool enable);
    void moveEnable(bool enable);
    void singleScanEnable(bool enable);
    void dualScanEnable(bool enable);
    void invertButton_click();
    void rotateButton_click();
    void settingButton_click();

    void calibrationButton_click();
    void plotButton_click();
public:

    PixelInfoLabel* pixelInfoLabel;
    FrameCountLabel* frameCountLabel;
    PanelButton *saveButton;
    QCheckBox* autoSave ;
    QCheckBox* gain;
    QCheckBox* offset;
public slots:
    void aboutButton_handle();
    void openButton_handle();
    void settingButton_handle();
    void powerButton_handle();
    void contrastButton_handle();
    void autoContrastButton_handle();
    void zoomButton_handle();
    void moveButton_handle();
    void singleScanButton_handle();
    void dualScanButton_handle();
    void invertButton_handle();
    void rotateButton_handle();
    void calibrationButton_handle();
    void plotButton_handle();

private:
    void setBackgroundImage();
    void signalInit();
    PanelButton *aboutButton;
//    QPushButton *aboutButton;
    PanelButton *openButton;
    //PanelButton *settingButton;
    QPushButton *settingButton;
    PanelButton *powerButton;
    PanelButton *contrastButton;
    PanelButton *autoContrastButton;
    //Todo proxy Panel
    PanelButton *zoomButton;
    PanelButton *moveButton;
    PanelButton *singleScanButton;
    //PanelButton *dualScanButton;
    QPushButton *dualScanButton;

    PanelButton *invertButton;
    PanelButton *rotateButton;
    //PanelButton *plotButton;
    QPushButton *plotButton;
    PanelButton *calButton;


    DigitalClock* clock;

    void setMousePressGroupButton();

    bool autoSaveEnabled;

    bool dualScanEnabled;
    bool singleScanEnabled;
    void setScanButtonGroup();

    bool zoomEnabled;
    bool moveEnabled;
    bool contrastEnabled;
};

#endif // VIEW_H
