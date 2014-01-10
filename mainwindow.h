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

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void singleScanEnable(bool enable);
    void dualScanEnable(bool enable);
    void setting_clicked();
    void open_clicked();
    void power_clicked();
    void contrastEnable(bool enable);
    void autoSaveEnable(bool enable);
    void autoContrast_clicked();
    void zoomEnable(bool enable);
    void moveEnable(bool enable);
    void rotate_click();
    void invert_click();
    void widgetMoveto(QPoint pos);
protected:

    void showEvent ( QShowEvent * event );
private:
    void connectSignals();
    void setupMatrix();
    void populateScene();
    void initAxWidget();
    void createAxWidget();
    void openDetector();
    void initDetector();
    void scan();
    void stop();

    QGraphicsScene *scene;
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
    bool grabing;

    QGraphicsProxyWidget* proxy;
    DTControl::CDTDisplay* axDisplay;
    //DTControl::CDTDisplay* axDisplayWidget;
    DTControl::CDTImage* axImage;
    DTControl::CDTDetector* axDetector;
    DTControl::CDTCommanderF3* axCommander;
    DTControl::IImageObject* axDisplayObject;
    DTControl::IImageObject* axImageObject;

    QString ip;

private slots:
    void ImageOpened();

    void FrameReady(int);
    void Datalost(int num);
};

#endif // MAINWINDOW_H
