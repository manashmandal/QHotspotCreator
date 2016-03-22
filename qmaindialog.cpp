/*
 *  Author: Manash Kumar Mandal
 *  GitHub: http://github.com/manashmndl/QHotspotCreator
 *
 *
 *
 *  DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                    Version 2, December 2004

 Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE FUCK YOU WANT TO.
 *
 *
 */


#include "qmaindialog.h"
#include "ui_qmaindialog.h"


const QString QMainDialog::START_HOTSPOT = "/cnetsh wlan start hostednetwork";
const QString QMainDialog::STOP_HOTSPOT = "/cnetsh wlan stop hostednetwork";
const QString QMainDialog::CMD = "cmd.exe";

const QString QMainDialog::KEY_KEY = "passkey";
QString QMainDialog::KEY_VALUE  = "password"; // Default value

const QString QMainDialog::SSID_KEY = "ssid"; //
QString QMainDialog::SSID_VALUE = "Hotspot"; // Default ssid value

const QString QMainDialog::GROUP = "hotspot_config";

const QString QMainDialog::DEFAULT_KEY = "password";
const QString QMainDialog::DEFAULT_SSID = "Hotspot";

QMainDialog::QMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QMainDialog),
    key(QMainDialog::KEY_VALUE),
    ssid(QMainDialog::SSID_VALUE)
{

    qDebug() << "Object Created with ssid: " << ssid;
    qDebug() << "Object created with key: " << key;

    ui->setupUi(this);
    this->loadConfiguration();
    this->enableStartButton(true);

    //Connecting process with the output
    connect(&hotspotCreatorProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(readyForOutput()));

}

QMainDialog::~QMainDialog()
{
    delete ui;
}

void QMainDialog::on_startButton_clicked()
{
    if (checkKeyLength() && !isSSIDEmpty()){
        this->enableStartButton(false);
        hotspotCreatorProcess.start(QMainDialog::CMD, QStringList() << QMainDialog::START_HOTSPOT, QProcess::ReadWrite);
    } else {
        if (!checkKeyLength() && !isSSIDEmpty()) QMessageBox::warning(this, "Password length is too short", "Password must be of length 8 character");
        else if (checkKeyLength() && isSSIDEmpty()) QMessageBox::warning(this, "Enter Hotspot SSID", "Please enter hotspot name, can't keep it empty!");
        else if (!checkKeyLength() && isSSIDEmpty()) QMessageBox::warning(this, "Required field empty", "Hotspot name field is empy and password length is less than required");
    }
}


void QMainDialog::saveConfiguration()
{
    ssid = ui->ssidLineEdit->text();
    key = ui->passwordLineEdit->text();

    QMainDialog::KEY_VALUE = key;
    QMainDialog::SSID_VALUE = ssid;

    //Saves settings
    saveSettings(QMainDialog::KEY_KEY, QMainDialog::KEY_VALUE, QMainDialog::GROUP);
    saveSettings(QMainDialog::SSID_KEY, QMainDialog::SSID_VALUE, QMainDialog::GROUP);

    qDebug() << "pass: " << KEY_VALUE;
    qDebug() << "ssid: " << SSID_VALUE;
}

void QMainDialog::loadConfiguration()
{
    ssid = loadSettings(SSID_KEY, GROUP, DEFAULT_SSID).toString();
    key = loadSettings(KEY_KEY, GROUP, DEFAULT_KEY).toString();
    ui->ssidLineEdit->setText(ssid);
    ui->passwordLineEdit->setText(key);
}


void QMainDialog::on_stopButton_clicked()
{
    this->enableStartButton(true);
    hotspotCreatorProcess.start(QMainDialog::CMD, QStringList() << QMainDialog::STOP_HOTSPOT, QProcess::ReadWrite);
}



void QMainDialog::on_setConfigButton_clicked()
{
    if (checkKeyLength() && !isSSIDEmpty()){
        this->saveConfiguration();
        QString _ssid = ui->ssidLineEdit->text();
        QString _pass = ui->passwordLineEdit->text();
        QString configComm = "/cnetsh wlan set hostednetwork ssid=" + _ssid + " key=" + _pass;
        hotspotCreatorProcess.start(QMainDialog::CMD, QStringList() << configComm, QProcess::ReadWrite);
    } else {
        if (!checkKeyLength() && !isSSIDEmpty()) QMessageBox::warning(this, "Password length is too short", "Password must be of length 8 character");
        else if (checkKeyLength() && isSSIDEmpty()) QMessageBox::warning(this, "Enter Hotspot SSID", "Please enter hotspot name, can't keep it empty!");
        else if (!checkKeyLength() && isSSIDEmpty()) QMessageBox::warning(this, "Required field empty", "Hotspot name field is empy and password length is less than required");
    }
}



void QMainDialog::enableStartButton(bool enable)
{
    ui->startButton->setEnabled(enable);
    ui->stopButton->setEnabled(!enable);
}

void QMainDialog::enableStopButton(bool enable)
{
    ui->stopButton->setEnabled(enable);
    ui->startButton->setEnabled(!enable);
}

bool QMainDialog::checkKeyLength()
{
    return (ui->passwordLineEdit->text().length() >= MIN_KEY_LENGTH);
}

bool QMainDialog::isKeyEmpty()
{
    return (ui->passwordLineEdit->text() == NULL);
}

bool QMainDialog::isSSIDEmpty()
{
    return (ui->ssidLineEdit->text() == NULL);
}

//Save settings
void saveSettings(const QString &key, const QVariant &value, const QString &group)
{
    QSettings settings;
    settings.beginGroup(group);
    settings.setValue(key, value);
    settings.endGroup();
}

//Load settings
QVariant loadSettings(const QString &key, const QString &group, const QVariant &defaultValue = QVariant())
{
    QSettings settings;
    settings.beginGroup(group);
    QVariant data = settings.value(key, defaultValue);
    settings.endGroup();
    return data;
}


//Read output from cmd
void QMainDialog::readyForOutput(void){
    standardOutput = hotspotCreatorProcess.readAllStandardOutput();
    qDebug() << standardOutput;
    if (standardOutput.contains("network stopped")) ui->statusLabel->setText("Hotspot stopped!");
    else if (standardOutput.contains("network started")) ui->statusLabel->setText("Hotspot Started");
    else if (standardOutput.contains("SSID of the hosted network has been successfully changed")) ui->statusLabel->setText("Hotspot was configured successfully");
}
