#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

class SettingParam;

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(SettingParam* param ,QWidget *parent = 0);
    ~SettingDialog();

    int scanSpeed();
    void setScanSpeed(int s);
    int sensitivityLevel();
    void setSensitivityLevel(int s);
    int scanMode();
    void setScanMode(int m);
    int dataPattern();
    void setDataPattern(int b);
    int rayVoltage();
    void setRayVoltage(int v);
    int rayCurrent();
    void setRayCurrent(int c);
    int rayExposeTime();
    void setRayExposeTime(int s);
    int autoSave();
    void setAutoSave(int b);

    QString autoSavePath();
    void setAutoSavePath(QString path);

    int autoSaveFrames();
    void setAutoSaveFrames (int size);

    void  setStartPixel(int start);
    int  startPixel();

    void  setEndPixel(int start);
    int  endPixel();
signals:
    void normalize();
private:
    Ui::SettingDialog *ui;
    void SettingDialog::LoadConfig();
private slots:
    void browseBtn_click();
    void normalize_click();
};

#endif // SETTINGDIALOG_H
