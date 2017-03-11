TEMPLATE = lib
CONFIG += staticlib

! inlcude(../common.pri){
error("Could not find common.pri file!")
}

DESTDIR = ../../build/.lib

HEADERS += \
BusinessContainer.h \
SongPlayer/SongPlayer.h \
OpenFile/OpenFile.h

SOURCES += \
BusinessCOntainer.cpp \
SongPlayer/SongPlayer.cpp \
OpenFile/OpenFile.cpp
