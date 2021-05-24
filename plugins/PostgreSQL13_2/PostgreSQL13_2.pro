#-------------------------------------------------
#
# Project created by QtCreator 2015-04-20T16:15:39
#
#-------------------------------------------------

QT       -= gui

TARGET = Postgresql13_2
TEMPLATE = lib

INCLUDEPATH += ../../CASE_SW

SOURCES += postgresql13_2.cpp

HEADERS += postgresql13_2.h

unix {
    CONFIG += plugin
    DESTDIR = $$PWD/../../build/case/lib/
}

win32 {
    CONFIG += dll
    DLLDESTDIR = $$PWD/../../build/case/lib/
}
