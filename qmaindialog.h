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
    Ui::QMainDialog *ui;
    QProcess hotspotCreatorProcess;
    QString ssid;
    QString password;

    static QString startHotspotCommand;
    static QString stopHotspotCommand;
    static QString cmd;
};

#endif // QMAINDIALOG_H
