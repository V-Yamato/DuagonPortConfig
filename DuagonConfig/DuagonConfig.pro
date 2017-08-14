#-------------------------------------------------
#
# Project created by QtCreator 2017-08-14T11:03:54
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DuagonConfig
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += MainWindow.h

FORMS    += MainWindow.ui

RC_ICONS = "port.ico"
