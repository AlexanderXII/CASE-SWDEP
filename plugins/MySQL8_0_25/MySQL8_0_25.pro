#-------------------------------------------------
#
# Project created by QtCreator 2019-05-04T12:24:07
#
#-------------------------------------------------

QT       -= gui

TARGET = MySQL8_0_25
TEMPLATE = lib

INCLUDEPATH += ../../CASE_SW

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += mysql8_0_25.cpp

HEADERS += mysql8_0_25.h

unix {
    CONFIG += plugin
    DESTDIR = $$PWD/../../build/case/lib/
}

win32 {
    CONFIG += dll
    DLLDESTDIR = $$PWD/../../build/case/lib/
}
