#include "mainwindow.h"
#include "pyr_window.h"
//#include "ui_Pyr_window.h"
#include <QApplication>
//#include <ui_mainwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PyramidalWindow w;
    w.show();
    return a.exec();
}

