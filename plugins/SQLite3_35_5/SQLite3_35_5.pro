#-------------------------------------------------
#
# Project created by QtCreator 2015-04-20T16:15:39
#
#-------------------------------------------------

QT       -= gui

TARGET = SQLite3_35_5
TEMPLATE = lib

INCLUDEPATH += ../../CASE_SW

SOURCES += \
    sqlite3_35_5.cpp

HEADERS += \
    sqlite3_35_5.h

unix {
    CONFIG += plugin
    DESTDIR = $$PWD/../../build/case/lib/
}

win32 {
    CONFIG += dll
    DLLDESTDIR = $$PWD/../../build/case/lib/
}

