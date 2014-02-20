#include "plotwidget.h"
#include "ui_plotwidget.h"

const int MAX = 65535;
PlotWidget::PlotWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotWidget)
{
    ui->setupUi(this);

    ui->plot->addGraph();

    ui->plot->xAxis->setLabel("pixel");
    ui->plot->yAxis->setLabel("value");
    ui->xmax->setValidator(new QIntValidator(0, MAX));
    ui->xmin->setValidator(new QIntValidator(0, MAX));
    ui->ymax->setValidator(new QIntValidator(0, MAX));
    ui->ymin->setValidator(new QIntValidator(0, MAX));
    QObject::connect(ui->rangeApply, &QPushButton::clicked, this, &PlotWidget::rangeApply);
    rangeApply();
}

PlotWidget::~PlotWidget()
{
    delete ui;
}

void PlotWidget::setRange(int min, int max)
{
    ui->xmax->setText(QString::number(max));
    ui->xmin->setText(QString::number(min));
    rangeApply();

}
void PlotWidget::rangeApply()
{
    int xmax, xmin, ymax, ymin;

    xmax = ui->xmax->text().toInt();
    xmin = ui->xmin->text().toInt();
    ymax = ui->ymax->text().toInt();
    ymin = ui->ymin->text().toInt();

    ui->plot->yAxis->setRange(ymin, ymax);
    ui->plot->xAxis->setRange(xmin, xmax);
    ui->plot->replot();
}

void PlotWidget::setData(QVector<double>* x, QVector<double>* y)
{
    ui->plot->graph(0)->setData(*x, *y);
    ui->plot->replot();
}
