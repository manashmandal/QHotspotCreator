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
}

QMainDialog::~QMainDialog()
{
    delete ui;
}

void QMainDialog::on_pushButton_clicked()
{
    hotspotCreatorProcess.start(QMainDialog::CMD, QStringList() << QMainDialog::START_HOTSPOT, QProcess::ReadWrite);
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


void QMainDialog::on_pushButton_2_clicked()
{
    hotspotCreatorProcess.start(QMainDialog::CMD, QStringList() << QMainDialog::STOP_HOTSPOT, QProcess::ReadWrite);
}



void QMainDialog::on_pushButton_3_clicked()
{
    this->saveConfiguration();
    QString _ssid = ui->ssidLineEdit->text();
    QString _pass = ui->passwordLineEdit->text();
    QString configComm = "/cnetsh wlan set hostednetwork ssid=" + _ssid + " key=" + _pass;
    hotspotCreatorProcess.start(QMainDialog::CMD, QStringList() << configComm, QProcess::ReadWrite);
}


//Save settings
void saveSettings(const QString &key, const QVariant &value, const QString &group)
{
    QSettings settings;
    settings.beginGroup(group);
    settings.setValue(key, value);
    settings.endGroup();
}

QVariant loadSettings(const QString &key, const QString &group, const QVariant &defaultValue = QVariant())
{
    QSettings settings;
    settings.beginGroup(group);
    QVariant data = settings.value(key, defaultValue);
    settings.endGroup();
    return data;
}
