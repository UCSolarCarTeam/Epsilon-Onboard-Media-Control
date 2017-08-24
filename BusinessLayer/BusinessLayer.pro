TEMPLATE = lib
CONFIG += staticlib

! include(../common.pri){
    error("Could not find common.pri file!")
}

DESTDIR = ../../build/.lib

HEADERS += \
    BusinessContainer.h \
    SongPlayer/SongPlayer.h \
    SongPlayer/I_SongPlayer.h \
    SongControl/SongControl.h

SOURCES += \
    BusinessContainer.cpp \
    SongPlayer/SongPlayer.cpp \
    SongControl/SongControl.cpp
