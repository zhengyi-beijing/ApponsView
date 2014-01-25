#ifndef DIGITALCLOCK_H
#define DIGITALCLOCK_H
#include <QLCDNumber>
#include <QTimer>
#include <QLabel>
#include <QDebug>

class PixelInfoLabel: public QLabel
{
    Q_OBJECT
    int x;
    int y;
    int value;
public:
    PixelInfoLabel(QWidget* parent=0):QLabel(parent)
    {
        x=0;
        y=0;
        value=0;
        setText(QString("x = %1, y = %2, v = %3").arg(QString::number(x),
                                                      QString::number(y),
                                                      QString::number(value)));

    }
public slots:
    void setInfo(int a, int b, int v)
    {
        qDebug()<<"get mouse move event";
        x = a;
        y = b;
        value = v;
        setText(QString("(x=%1, y=%2) = %3").arg(QString::number(x),
                                                      QString::number(y),
                                                      QString::number(value)));
    }
};

class FrameCountLabel:public QLabel
{
    Q_OBJECT
    int count;
    int lost;
public:
    FrameCountLabel(QWidget* parent=0):QLabel(parent)
    {
        lost =0;
        count = 0;
        setText(QString("Frame %1   Lost %2").arg(QString::number(count),
                                                       QString::number(lost)));
    }

public slots:
    void setDataLost(int n)
    {
        lost = n;
        setText(QString("Frame %1   Lost %2").arg(QString::number(count),
                                                       QString::number(lost)));
    }

    void setFrameCount(int c)
    {
        count = c;
        setText(QString("Frame %1   Lost %2").arg(QString::number(count),
                                                       QString::number(lost)));
    }
};

class DigitalClock:public QLCDNumber
{
Q_OBJECT
public:
  DigitalClock(QWidget *paraent=0);

private:
  QTimer *timer;

private slots:
  void showtime();
};
#endif // DIGITALCLOCK_H
