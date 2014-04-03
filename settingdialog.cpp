#include "settingdialog.h"
#include "ui_settingdialog.h"
#include <QSettings>
#include "apponssetting.h"
#include <QFileDialog>
#include <QString>
#include <QDebug>

SettingDialog::SettingDialog(SettingParam* param, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    //ui->scanMode->addItem("Frame");
    //ui->scanMode->addItem("Continues");

    //ui->startPixel->setValidator(new QIntValidator(0, 1536));
    //ui->endPixel->setValidator(new QIntValidator(0, 1536));
   // ui->RaySourceTab->setVisible(false);
   // ui->DisplayTab->setVisible(false);
    ui->tabWidget->removeTab(1);
    ui->tabWidget->removeTab(1);
    ui->scanMode->setEnabled(false);

    setScanMode(param->scanMode);
    setScanSpeed(param->scanSpeed);
    setSensitivityLevel(param->sensitivityLevel);
    setDataPattern(param->dataPattern);
    setRayVoltage(param->rayVoltage);
    setRayCurrent(param->rayCurrent);
    setRayExposeTime(param->rayExposeTime);
    //setAutoSave(param->autoSave);
    setAutoSavePath(param->autoSavePath);
    setAutoSaveSize(param->autoSaveSize/1000000);
    setStartPixel(param->startPixel);
    setEndPixel(param->endPixel);


    QObject::connect(ui->browseButton, SIGNAL(clicked()), this, SLOT(browseBtn_click()));
    QObject::connect(ui->normalize, SIGNAL(clicked()), this, SLOT(normalize_click()));
}


SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::browseBtn_click()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                "/home",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    qDebug()<< "Path is " << dir;
    ui->path->setText(dir);

}

int  SettingDialog::startPixel()
{
    return ui->startPixel->text().toInt();
}

void  SettingDialog::setStartPixel(int start)
{
    ui->startPixel->setText(QString::number(start));
}

int SettingDialog::endPixel()
{
    return ui->endPixel->text().toInt();
}

void SettingDialog::setEndPixel(int end)
{
    ui->endPixel->setText(QString::number(end));
}



QString SettingDialog::autoSavePath()
{
    return ui->path->text();
}

void SettingDialog::setAutoSavePath(QString path)
{
    ui->path->setText(path);
}

int SettingDialog::autoSaveSize()
{
    return ui->singleFileSize->text().toInt()*1000*1000;
}

void SettingDialog::setAutoSaveSize (int size)
{
    ui->singleFileSize->setText(QString::number(size));
}

int SettingDialog::scanSpeed()
{
    return ui->scanSpeed->text().toInt();
}

void SettingDialog::setScanSpeed(int s)
{
    ui->scanSpeed->setText(QString::number(s));
}

int SettingDialog::sensitivityLevel()
{
    return ui->sensitivty->currentIndex()+1;
}

void SettingDialog::setSensitivityLevel(int s)
{
    ui->sensitivty->setCurrentIndex(s-1);
}

int SettingDialog::scanMode()
{
    return ui->scanMode->currentIndex();
}

void SettingDialog::setScanMode(int m)
{
    ui->scanMode->setCurrentIndex(m);
}

int SettingDialog::dataPattern ()
{
    return ui->dataPattern->isChecked();
}

void SettingDialog::setDataPattern (int b)
{
    ui->dataPattern->setChecked(b);
}

int SettingDialog::rayVoltage()
{
    return ui->rayVoltage->text().toInt();
}

void SettingDialog::setRayVoltage(int v)
{
    ui->rayVoltage->setText(QString::number(v));
}

int SettingDialog::rayCurrent()
{
    return ui->rayCurrent->text().toInt();
}

void SettingDialog::setRayCurrent(int c)
{
    ui->rayCurrent->setText(QString::number(c));

}

int SettingDialog::rayExposeTime()
{
    return ui->exposeTime->text().toInt();
}

void SettingDialog::setRayExposeTime(int s)
{
    ui->exposeTime->setText(QString::number(s));
}

int SettingDialog::autoSave()
{
    //return ui->autoSave->isChecked();
    return 0;
}

void SettingDialog::setAutoSave(int b)
{
    //return ui->autoSave->setChecked(b);
}

void SettingDialog::normalize_click()
{
    emit normalize();
    this->accept();
}
