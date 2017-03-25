TEMPLATE = lib
CONFIG += staticlib

! include(../common.pri){
    error("Could not find common.pri file!")
}

DESTDIR = ../../build/.lib

HEADERS += \
    SongPlayerUI/SongPlayerUi.h \
    SongPlayerView/SongPlayerView.h \
    ViewContainer.h \

SOURCES += \ 
    SongPlayerUI/SongPlayerUi.cpp \
    SongPlayerView/SongPlayerView.cpp \
    ViewContainer.cpp \

FORMS += \
    SongPlayerUi.ui \
