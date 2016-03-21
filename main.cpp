#include "qmaindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("Q Hotspot Creator");
    a.setApplicationDisplayName("Q Hotspot Creator");
    a.setApplicationVersion("1.0.0");
    a.setOrganizationDomain("electroscholars.com");
    a.setOrganizationName("Electroscholars");

    //Creating the dialog
    QMainDialog w;
    w.setWindowTitle("Q Hotspot Creator");
    w.show();
    return a.exec();
}
