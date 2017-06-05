#-------------------------------------------------
#
# Project created by QtCreator 2017-03-23T23:20:40
#
#-------------------------------------------------

QT  += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sample
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11

SOURCES += src/main.cpp \
    src/recorder.cpp \
    src/mainwindow.cpp \
    src/wavFile.cpp \
    src/user.cpp \
    src/userwindow.cpp \
    src/audiomodel.cpp

HEADERS  += \
    src/recorder.h \
    src/mainwindow.h \
    src/wavFile.h \
    src/user.h \
    src/userwindow.h \
    src/audiomodel.h

FORMS += \
    src/mainwindow.ui \
    src/userwindow.ui
