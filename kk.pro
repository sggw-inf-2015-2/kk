#-------------------------------------------------
#
# Project created by QtCreator 2017-03-23T23:20:40
#
#-------------------------------------------------

QT  += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sample
TEMPLATE = app

SOURCES += src/main.cpp\
    src/recorder.cpp \
    src/mainwindow.cpp

HEADERS  += \
    src/recorder.h \
    src/mainwindow.h

FORMS += \
    src/mainwindow.ui

CONFIG += c++11
