#include "qmaindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainDialog w;
    w.setWindowTitle("Q Hotspot Creator");
    w.show();
    return a.exec();
}
