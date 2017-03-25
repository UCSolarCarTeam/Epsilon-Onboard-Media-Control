TEMPLATE = lib
CONFIG += staticlib

! include(../common.pri){
error("Could not find common.pri file!")
}

PRE_TARGETDEPS += \
    ../../build/.lib/*

DESTDIR = ../../build/.lib

HEADERS += \
    BusinessContainer.h \
    SongPlayer/SongPlayer.h \
    OpenFile/OpenFile.h \
    SongControl/SongControl.h

SOURCES += \
    BusinessContainer.cpp \
    SongPlayer/SongPlayer.cpp \
    OpenFile/OpenFile.cpp \
    SongControl/SongControl.cpp
