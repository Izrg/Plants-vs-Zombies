#-------------------------------------------------
#
# Project created by QtCreator 2014-11-14T12:56:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FinalProject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    maingame.cpp \
    sun.cpp \
    myview.cpp

HEADERS  += mainwindow.h \
    maingame.h \
    sun.h \
    myview.h

FORMS    += mainwindow.ui \
    maingame.ui

RESOURCES += \
    Resources.qrc
