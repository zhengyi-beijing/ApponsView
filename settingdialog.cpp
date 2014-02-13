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
    ui->sensitivty->addItem("Low");
    ui->sensitivty->addItem("High");
    ui->scanMode->addItem("Frame");
    ui->scanMode->addItem("Continues");

   // ui->RaySourceTab->setVisible(false);
   // ui->DisplayTab->setVisible(false);
    ui->tabWidget->removeTab(1);
    ui->tabWidget->removeTab(1);

    setScanMode(param->scanMode);
    setScanSpeed(param->scanSpeed);
    setSensitivityLevel(param->sensitivityLevel);
    setDataPattern(param->dataPattern);
    setRayVoltage(param->rayVoltage);
    setRayCurrent(param->rayCurrent);
    setRayExposeTime(param->rayExposeTime);
    setAutoSave(param->autoSave);
    setAutoSavePath(param->autoSavePath);
    setAutoSaveSize(param->autoSaveSize/1000000);
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

void SettingDialog::setOffsetEnable(int e)
{
    ui->offset->setChecked(e);
}

int SettingDialog::offsetEnable()
{

    return ui->offset->isChecked();
}

void SettingDialog::setGainEnable(int e)
{
    ui->gain->setChecked(e);
}

int SettingDialog::gainEnable()
{
    return ui->gain->isChecked();
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
    return ui->sensitivty->currentIndex();
}

void SettingDialog::setSensitivityLevel(int s)
{
    ui->sensitivty->setCurrentIndex(s);
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
    return ui->autoSave->isChecked();
}

void SettingDialog::setAutoSave(int b)
{
    return ui->autoSave->setChecked(b);
}

void SettingDialog::normalize_click()
{
    emit normalize();
    this->accept();
}
