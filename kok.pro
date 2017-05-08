#-------------------------------------------------
#
# Project created by QtCreator 2017-03-23T23:20:40
#
#-------------------------------------------------

QT  += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sample
TEMPLATE = app

SOURCES += main.cpp\
    recorder.cpp \
    mainwindow.cpp

HEADERS  += \
    recorder.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

CONFIG += c++11
