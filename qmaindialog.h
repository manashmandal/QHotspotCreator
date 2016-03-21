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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    void loadConfiguration(void);
    void saveConfiguration(void);

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
};


//Settings function
void saveSettings(const QString &key, const QVariant &value, const QString &group);
QVariant loadSettings(const QString &key, const QString &group, const QVariant &defaultValue);

#endif // QMAINDIALOG_H
