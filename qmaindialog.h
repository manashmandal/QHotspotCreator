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



#ifndef QMAINDIALOG_H
#define QMAINDIALOG_H


#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QPushButton>
#include <QLineEdit>
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QSettings>
#include <QMessageBox>

#define MIN_KEY_LENGTH 8
#define MAX_KEY_LENGTH 32

namespace Ui {
class QMainDialog;
}

class QMainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QMainDialog(QWidget *parent = 0);
    ~QMainDialog();

private slots:
    void on_startButton_clicked();
    void on_stopButton_clicked();
    void on_setConfigButton_clicked();

private:
    void loadConfiguration(void);
    void saveConfiguration(void);

    void enableStartButton(bool enable);
    void enableStopButton(bool enable);

    //Checker function
    bool checkKeyLength(void);
    bool isKeyEmpty(void);
    bool isSSIDEmpty(void);


private:
    Ui::QMainDialog *ui;
    QProcess hotspotCreatorProcess;
    QString ssid;
    QString key;

    static const QString START_HOTSPOT;
    static const QString STOP_HOTSPOT;
    static const QString CMD;

    static const QString GROUP;
    static const QString KEY_KEY;
    static const QString SSID_KEY;
    static QString KEY_VALUE;
    static QString SSID_VALUE;

    static const QString DEFAULT_SSID;
    static const QString DEFAULT_KEY;

    QString standardOutput;

public slots:
    void readyForOutput(void);
};


//Settings function
void saveSettings(const QString &key, const QVariant &value, const QString &group);
QVariant loadSettings(const QString &key, const QString &group, const QVariant &defaultValue);

#endif // QMAINDIALOG_H
