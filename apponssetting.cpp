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

    param.scanSpeed = setting.value("Detector/scanSpeed", 200).toInt();
    param.sensitivityLevel = setting.value("Detector/sensitivity", 0).toInt();
    param.dataPattern = setting.value("Detector/dataPattern", 0).toInt();
    param.scanMode = setting.value("Display/scanMode", 0).toInt();
    param.rayVoltage = setting.value("RaySource/rayVoltage", 120).toInt();
    param.rayCurrent = setting.value("RaySource/rayCurrent", 2).toInt();
    param.rayExposeTime = setting.value("RaySource/rayExposeTime", 2).toInt();
    param.autoSave = setting.value("Image/autoSave", 0).toInt();

}

QString ApponsSetting::ip()
{
    return param.ip;
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

void ApponsSetting::showSettingDialog()
{
    SettingDialog dlg(&param);
    if(dlg.exec() == QDialog::Accepted){
        param.scanSpeed = dlg.scanSpeed();
        param.sensitivityLevel = dlg.sensitivityLevel();
        param.dataPattern = dlg.dataPattern();
        param.scanMode = dlg.scanMode();
        param.rayVoltage = dlg.rayVoltage();
        param.rayCurrent =dlg.rayCurrent();
        param.rayExposeTime = dlg.rayExposeTime();
        param.autoSave = dlg.autoSave();

        QString path =  QCoreApplication::applicationDirPath ();
        QSettings setting(path+"/config.ini", QSettings ::IniFormat);

        setting.setValue("Detector/scanSpeed", param.scanSpeed);
        setting.value("Detector/sensitivity", param.sensitivityLevel);
        setting.value("Detector/dataPattern", param.dataPattern);
        setting.value("Display/scanMode", param.scanMode);
        setting.value("RaySource/rayVoltage", param.rayVoltage);
        setting.value("RaySource/rayCurrent", param.rayCurrent);
        setting.value("RaySource/rayExposeTime", param.rayExposeTime);
        setting.value("Image/autoSave", param.autoSave);
    }
}
