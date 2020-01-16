TEMPLATE = lib
CONFIG += staticlib

! include(../common.pri){
error("Could not find common.pri file!")
}

DESTDIR = .lib

HEADERS += \
    SongPlayerUI/SongPlayerUi.h \
    SongPlayerUI/I_SongPlayerUi.h \
    SongPlayerView/SongPlayerView.h \
    ProgressBar/ProgressBar.h\
    ViewContainer.h \
    FontLoader/FontLoader.h \

SOURCES += \
    SongPlayerUI/SongPlayerUi.cpp \
    SongPlayerView/SongPlayerView.cpp \
    ProgressBar/ProgressBar.cpp \
    ViewContainer.cpp \
    FontLoader/FontLoader.cpp \

FORMS += \
    SongPlayerUi.ui \
