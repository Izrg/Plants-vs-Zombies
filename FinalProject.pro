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
    myview.cpp \
    plant.cpp \
    defence.cpp \
    attack.cpp \
    sunflower.cpp \
    peashooter.cpp \
    zombie.cpp \
    regular.cpp \
    pvz.cpp \
    grass.cpp

HEADERS  += mainwindow.h \
    maingame.h \
    sun.h \
    myview.h \
    plant.h \
    defence.h \
    attack.h \
    sunflower.h \
    peashooter.h \
    zombie.h \
    regular.h \
    pvz.h \
    grass.h

FORMS    += mainwindow.ui \
    maingame.ui

RESOURCES += \
    Resources.qrc
