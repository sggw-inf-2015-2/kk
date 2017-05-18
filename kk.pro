#-------------------------------------------------
#
# Project created by QtCreator 2017-03-23T23:20:40
#
#-------------------------------------------------

QT  += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kk
TEMPLATE = app

SOURCES += src/main.cpp\
    src/recorder.cpp \
    src/mainwindow.cpp \
    src/user.cpp

HEADERS  += \
    src/recorder.h \
    src/mainwindow.h \
    src/user.h

FORMS += \
    src/mainwindow.ui

CONFIG += c++11
