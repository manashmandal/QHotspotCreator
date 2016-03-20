#include "qmaindialog.h"
#include "ui_qmaindialog.h"


QString QMainDialog::startHotspotCommand = "/cnetsh wlan start hostednetwork";
QString QMainDialog::stopHotspotCommand = "/cnetsh wlan stop hostednetwork";
QString QMainDialog::cmd = "cmd.exe";

QMainDialog::QMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QMainDialog),
    password("password"),
    ssid("Hotspot")
{
    ui->setupUi(this);
}

QMainDialog::~QMainDialog()
{
    delete ui;
}

void QMainDialog::on_pushButton_clicked()
{
    hotspotCreatorProcess.start(cmd, QStringList() << QMainDialog::startHotspotCommand, QProcess::ReadWrite);
}



void QMainDialog::on_pushButton_2_clicked()
{
    hotspotCreatorProcess.start(cmd, QStringList() << QMainDialog::stopHotspotCommand, QProcess::ReadWrite);
}



void QMainDialog::on_pushButton_3_clicked()
{
    QString _ssid = ui->ssidLineEdit->text();
    QString _pass = ui->passwordLineEdit->text();
    QString configComm = "/cnetsh wlan set hostednetwork ssid=" + _ssid + " key=" + _pass;
    hotspotCreatorProcess.start(cmd, QStringList() << configComm, QProcess::ReadWrite);
}
