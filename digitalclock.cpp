#include "digitalclock.h"
#include <QDateTime>
#include <QDebug>

DigitalClock::DigitalClock(QWidget *parent):QLCDNumber(parent)
{
    setDigitCount(19);
    setSegmentStyle(Filled);
    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showtime()));
    timer->start(1000);
    showtime();
}

void DigitalClock::showtime()
{
    QDateTime time=QDateTime::currentDateTime();
    QString text=time.toString("yyyy-MM-dd hh:mm:ss");
//    qDebug() << text;
    display(text);
}
