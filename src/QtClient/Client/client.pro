#-------------------------------------------------
#
# Project created by QtCreator 2017-07-04T10:21:32
#
#-------------------------------------------------

QT       += core gui
QT += network
QT += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    login.cpp \
    manage.cpp

HEADERS  += mainwindow.h \
    login.h \
    manage.h

FORMS    += mainwindow.ui \
    login.ui
