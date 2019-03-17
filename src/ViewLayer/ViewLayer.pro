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
    ContainerUI/ContainerUI.h \
    SongListUI/SongListUI.h \
    SongListUI/I_SongListUI.h \
    SongListView/SongListView.h \

SOURCES += \
    SongPlayerUI/SongPlayerUi.cpp \
    SongPlayerView/SongPlayerView.cpp \
    ProgressBar/ProgressBar.cpp \
    ViewContainer.cpp \
    FontLoader/FontLoader.cpp \
    ContainerUI/ContainerUI.cpp \
    SongListUI/SongListUI.cpp \
    SongListView/SongListView.cpp \

FORMS += \
    SongPlayerUi.ui \
    ContainerUI.ui \
    SongListUI.ui
