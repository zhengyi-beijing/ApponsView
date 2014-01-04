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

class View;

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(View *v) : QGraphicsView(), view(v) { }

protected:
#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *);
#endif

private:
    View *view;
};

class View : public QFrame
{
    Q_OBJECT
public:
    explicit View(const QString &name, QWidget *parent = 0);

    QGraphicsView *view() const;

public slots:
    void zoomIn();
    void zoomOut();

private slots:
    void resetView();
    void setupMatrix();
    void toggleOpenGL();
    void toggleAntialiasing();
    void rotateLeft();
    void rotateRight();

private:
    GraphicsView *graphicsView;
    qreal scale;
    qreal rotate;

};

class PanelButton: public QToolButton
{
    Q_OBJECT
public:
    explicit PanelButton(const QString resPath, QWidget *parent = 0);

};

class Panel: public QFrame
{
    Q_OBJECT
public:
    explicit Panel(const QString &name, QWidget *parent = 0);
signals:
    void openButton_click();
    void saveButton_click();
    void powerButton_click();
    void contrastButton_click();
    void autoContrastButton_click();
    void zoomButton_click();
    void moveButton_clcik();
    void singleScanButton_click();
    void dualScanButton_click();

public slots:
    void openButton_handle();
    void saveButton_handle();
    void powerButton_handle();
    void contrastButton_handle();
    void autoContrastButton_handle();
    void zoomButton_handle();
    void moveButton_handle();
    void singleScanButton_handle();
    void dualScanButton_handle();
    //void invertButton_handle();

private:
    void setBackgroundImage();
    void signalInit();
    PanelButton *openButton;
    PanelButton *saveButton;
    PanelButton *settingButton;
    PanelButton *powerButton;
    PanelButton *contrastButton;
    PanelButton *autoContrastButton;
    //Todo proxy Panel
    PanelButton *zoomButton;
    PanelButton *moveButton;
    PanelButton *singleScanButton;
    PanelButton *dualScanButton;

    PanelButton *invertButton;
    PanelButton *rotateButton;

};

#endif // VIEW_H
