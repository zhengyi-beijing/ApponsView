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
    dtcontrol.cpp \
    filestoreserver.cpp \
    QLogger.cpp

HEADERS  += \
    mainwindow.h \
    view.h \
    dtcontrol.h \
    QLogger.h \
    filestoreserver.h

#LIBS += "c:\work\apponsview\QLogger.lib"
OTHER_FILES +=

RESOURCES += \
    Appons.qrc

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/ -lQLogger
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/ -lQLogger

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/
