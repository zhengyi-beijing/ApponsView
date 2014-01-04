#-------------------------------------------------
#
# Project created by QtCreator 2014-01-02T23:30:54
#
#-------------------------------------------------

QT       += core gui axcontainer

qtHaveModule(opengl): QT += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ApponsView
TEMPLATE = app


SOURCES += main.cpp \
    mainwindow.cpp \
    view.cpp \
    dtcontrol.cpp

HEADERS  += \
    mainwindow.h \
    view.h \
    dtcontrol.h

OTHER_FILES +=

RESOURCES += \
    Appons.qrc
