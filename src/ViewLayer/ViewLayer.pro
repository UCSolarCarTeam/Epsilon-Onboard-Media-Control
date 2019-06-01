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
    ContainerUI/ContainerUI.h \
    SongListUI/SongListUI.h \
    SongListUI/I_SongListUI.h \
    SongListView/SongListView.h \
    listItem/listItem.h \

SOURCES += \
    SongPlayerUI/SongPlayerUi.cpp \
    SongPlayerView/SongPlayerView.cpp \
    ProgressBar/ProgressBar.cpp \
    ViewContainer.cpp \
    ContainerUI/ContainerUI.cpp \
    SongListUI/SongListUI.cpp \
    SongListView/SongListView.cpp \
    listItem/listItem.cpp \

FORMS += \
    SongPlayerUi.ui \
    ContainerUI.ui \
    SongListUI.ui
