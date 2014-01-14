#ifndef DIGITALCLOCK_H
#define DIGITALCLOCK_H
#include <QLCDNumber>
#include <QTimer>

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
