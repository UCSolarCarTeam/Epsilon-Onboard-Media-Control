QT -= gui
TEMPLATE = lib
CONFIG += staticlib

! include(../common.pri){
    error("Could not find common.pri file!")
}

DESTDIR = .lib

SOURCES += \
    LocalSongUrlSource.cpp

HEADERS += \
    I_SongUrlSource.h \
    LocalSongUrlSource.h
