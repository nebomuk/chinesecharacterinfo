#include <QWebView>

#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv); 
    a.setApplicationName("Chinese Character Info");
    a.setOrganizationName("Taiko");
    MainWindow w;
    w.setWindowTitle(a.applicationName());
    w.show();

    return a.exec();
}
