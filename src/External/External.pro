QT -= gui
TEMPLATE = lib
CONFIG += staticlib

! include(../common.pri){
    error("Could not find common.pri file!")
}

DESTDIR = ../../build/.lib

SOURCES +=

HEADERS += \
    I_SongUrlSource.h
