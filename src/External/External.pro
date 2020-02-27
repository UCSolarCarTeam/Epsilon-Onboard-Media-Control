QT -= gui
TEMPLATE = lib
CONFIG += staticlib

! include(../common.pri){
    error("Could not find common.pri file!")
}

DESTDIR = .lib
INCLUDEPATH += SongUrlSource \
               SongUrlSource/Local \


SOURCES += \
    SongUrlSource/Local/LocalSongUrlSource.cpp

HEADERS += \
    SongUrlSource/I_SongUrlSource.h \
    SongUrlSource/Local/LocalSongUrlSource.h
