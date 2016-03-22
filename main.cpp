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
