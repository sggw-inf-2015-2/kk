#-------------------------------------------------
#
# Project created by QtCreator 2017-03-23T23:20:40
#
#-------------------------------------------------

QT  += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kk
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11 # for MinGW

linux-g++ {
	CONFIG += link_pkgconfig
	PKGCONFIG += fftw3
}

win32 {
	DESTDIR = $$PWD
	LIBS += -L$$DESTDIR\lib -llibfftw3-3
	INCLUDEPATH = $$DESTDIR\lib
}

SOURCES += src/main.cpp \
    src/recorder.cpp \
    src/mainwindow.cpp \
    src/user.cpp \
    src/userwindow.cpp \
    src/adduserwindow.cpp \
	src/calibrator.cpp \
    src/audiomodel.cpp

HEADERS  += \
    src/recorder.h \
    src/mainwindow.h \
    src/user.h \
    src/userwindow.h \
    src/adduserwindow.h \
    src/audiomodel.h \
    src/calibrator.h


FORMS += \
    src/mainwindow.ui \
    src/userwindow.ui \
    src/adduserwindow.ui
