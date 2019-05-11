TEMPLATE = lib
CONFIG += staticlib

! include(../common.pri){
error("Could not find common.pri file!")
}

DESTDIR = ../../build/.lib

HEADERS += \
    SongPlayerUI/SongPlayerUi.h \
    SongPlayerUI/I_SongPlayerUi.h \
    SongPlayerView/SongPlayerView.h \
    ProgressBar/ProgressBar.h\
    ViewContainer.h \
    FontLoader/FontLoader.h \
    ProgressBar/ProgressBar.h \
    SongPlayerUI/I_SongPlayerUi.h \
    SongPlayerUI/SongPlayerUi.h \
    SongPlayerView/SongPlayerView.h \
    ViewContainer.h

SOURCES += \
    SongPlayerUI/SongPlayerUi.cpp \
    SongPlayerView/SongPlayerView.cpp \
    ProgressBar/ProgressBar.cpp \
    ViewContainer.cpp \
    FontLoader/FontLoader.cpp \
    ProgressBar/ProgressBar.cpp \
    SongPlayerUI/SongPlayerUi.cpp \
    SongPlayerView/SongPlayerView.cpp \
    ViewContainer.cpp

FORMS += \
    SongPlayerUi.ui \
