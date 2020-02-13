TEMPLATE = lib
CONFIG += staticlib

! include(../common.pri){
error("Could not find common.pri file!")
}

DESTDIR = .lib
INCLUDEPATH += ../BusinessLayer

HEADERS += \
    SongControlView.h \
    ProgressBar/ProgressBar.h\
    ViewContainer.h \
    FontLoader/FontLoader.h \
    SongPlayerUI/I_CurrentSongUi.h \
    SongPlayerUI/I_SongControlUi.h \
    CurrentSongView.h

SOURCES += \
    SongControlView.cpp \
    ProgressBar/ProgressBar.cpp \
    ViewContainer.cpp \
    FontLoader/FontLoader.cpp \
    CurrentSongView.cpp

FORMS += \
    SongPlayerUi.ui \
