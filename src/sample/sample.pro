#-------------------------------------------------
#
# Project created by QtCreator 2017-03-23T23:20:40
#
#-------------------------------------------------

QT  += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sample
TEMPLATE = app
CONFIG += console

SOURCES += main.cpp\
    recorder.cpp \
    mainwindow.cpp \
    wavFile.cpp

HEADERS  += \
    recorder.h \
    mainwindow.h \
    wavFile.h

FORMS += \
    mainwindow.ui
