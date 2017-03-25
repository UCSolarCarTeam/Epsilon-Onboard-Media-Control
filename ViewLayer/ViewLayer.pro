TEMPLATE = lib
CONFIG += staticlib

! include(../common.pri){
error("Could not find common.pri file!")
}

PRE_TARGETDEPS += \
    ../../build/.lib/*

DESTDIR = ../../build/.lib

HEADERS += \
    ViewContainer.h \
    SongPlayerView/SongPlayerView.h \
    SongPlayerUI/SongPlayerUi.h \

SOURCES += \
    ViewContainer.cpp \
    SongPlayerUI/SongPlayerUi.cpp \
    SongPlayerView/SongPlayerView.cpp

FORMS += \
    SongPlayerUI.ui
