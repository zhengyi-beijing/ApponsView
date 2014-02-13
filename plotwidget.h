#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>

namespace Ui {
class PlotWidget;
}

class PlotWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlotWidget(QWidget *parent = 0);
    ~PlotWidget();

    void setData(QVector<double>* x, QVector<double>* y);
private slots:
    void rangeApply();
private:
    Ui::PlotWidget *ui;
};

#endif // PLOTWIDGET_H
