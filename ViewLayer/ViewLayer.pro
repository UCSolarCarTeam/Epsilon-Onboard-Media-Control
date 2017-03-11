TEMPLATE = lib
CONFIG += staticlib

! include(../common.pri){
error("Could not find common.pri file!")
}


DESTDIR = ../../build/.lib

HEADERS += \
ViewContainer.h \
SongPlayerView/SongPlayerView.h \
SongPlayerUI/SongPlayerUi.h \

SOURCES += \
ViewContainer.cpp \
SongPlayerUI/SongPlayerUi.cpp \
SongPlayerView/SongPlayerView.cpp

Forms += \
SongPlayerUI.ui
