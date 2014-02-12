#include "apponssetting.h"
#include <QSettings>
#include <settingdialog.h>
#include <QCoreApplication>

SettingParam ApponsSetting::param;

ApponsSetting::ApponsSetting()
{
   // LoadConfig();
}

void ApponsSetting::LoadConfig()
{
    QString path =  QCoreApplication::applicationDirPath ();
    QSettings setting(path+"/config.ini", QSettings ::IniFormat);
    param.ip = setting.value("Network/ip", "192.168.1.25").toString();
    param.width = setting.value("Image/width", 1536).toInt();
    param.height = setting.value("Image/height", 1024).toInt();

    param.gainEnable = setting.value("Detector/gainEnable", 0).toInt();
    param.offsetEnable = setting.value("Detector/offsetEnable", 0).toInt();

    param.scanSpeed = setting.value("Detector/scanSpeed", 200).toInt();
    param.sensitivityLevel = setting.value("Detector/sensitivity", 0).toInt();
    param.dataPattern = setting.value("Detector/dataPattern", 0).toInt();
    param.scanMode = setting.value("Display/scanMode", 0).toInt();
    param.rayVoltage = setting.value("RaySource/rayVoltage", 120).toInt();
    param.rayCurrent = setting.value("RaySource/rayCurrent", 2).toInt();
    param.rayExposeTime = setting.value("RaySource/rayExposeTime", 2).toInt();
    param.autoSave = setting.value("Image/autoSave", false).toBool();
    param.autoSavePath = setting.value("Image/autoSavePath", path).toString();
    param.autoSaveSize = setting.value("Image/autoSaveSize", 10).toInt();

}

QString ApponsSetting::ip()
{
    return param.ip;
}

long ApponsSetting::width()
{
    return param.width;
}

long ApponsSetting::height()
{
    return param.height;
}

int ApponsSetting::scanSpeed()
{
    return param.scanSpeed;
}

int ApponsSetting::sensitivityLevel()
{
    return param.sensitivityLevel;
}

int ApponsSetting::scanMode()
{
    return param.scanMode;
}

int ApponsSetting::dataPattern()
{
    return param.dataPattern;
}

int ApponsSetting::rayVoltage()
{
    return param.rayVoltage;
}

int ApponsSetting::rayCurrent()
{
    return param.rayCurrent;
}

int ApponsSetting::rayExposeTime()
{
    return param.rayExposeTime;
}

bool ApponsSetting::autoSave()
{
    return param.autoSave;
}

QString ApponsSetting::autoSavePath()
{
    return param.autoSavePath;
}

int ApponsSetting::autoSaveSize()
{
    return param.autoSaveSize;
}

int ApponsSetting::isGainEnable()
{
    return param.gainEnable   ;
}

int ApponsSetting::isOffsetEnable()
{
    return param.offsetEnable;
}

void ApponsSetting::normalize_slot()
{
    emit normalize();
}

void ApponsSetting::showSettingDialog()
{
    SettingDialog dlg(&param);
    QObject::connect(&dlg, &SettingDialog::normalize, this, &ApponsSetting::normalize_slot, Qt::QueuedConnection);
    if(dlg.exec() == QDialog::Accepted){
        param.scanSpeed = dlg.scanSpeed();
        param.sensitivityLevel = dlg.sensitivityLevel();
        param.dataPattern = dlg.dataPattern();
        param.scanMode = dlg.scanMode();
        param.rayVoltage = dlg.rayVoltage();
        param.rayCurrent =dlg.rayCurrent();
        param.rayExposeTime = dlg.rayExposeTime();
        param.autoSave = dlg.autoSave();
        param.autoSavePath =  dlg.autoSavePath();
        param.autoSaveSize = dlg.autoSaveSize();

        param.gainEnable = dlg.gainEnable();
        param.offsetEnable = dlg.offsetEnable();

        QString path =  QCoreApplication::applicationDirPath ();
        QSettings setting(path+"/config.ini", QSettings ::IniFormat);

        setting.setValue("Detector/scanSpeed", param.scanSpeed);
        setting.setValue("Detector/sensitivity", param.sensitivityLevel);
        setting.setValue("Detector/dataPattern", param.dataPattern);
        setting.setValue("Detector/gain", param.gainEnable);
        setting.setValue("Detector/offset", param.offsetEnable);
        setting.setValue("Display/scanMode", param.scanMode);
        setting.setValue("RaySource/rayVoltage", param.rayVoltage);
        setting.setValue("RaySource/rayCurrent", param.rayCurrent);
        setting.setValue("RaySource/rayExposeTime", param.rayExposeTime);
        setting.setValue("Image/autoSave", param.autoSave);
        setting.setValue("Image/autoSavePath", param.autoSavePath);
        setting.setValue("Image/autoSaveSize", param.autoSaveSize);
    }
}
