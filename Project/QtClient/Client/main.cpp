#include "mainwindow.h"
#include"login.h"
#include "manage.h"
#include <QApplication>
#include <QDesktopServices>
#include <QTextStream>
#include <QUrl>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Manage c;
    return a.exec();
}
