TEMPLATE = lib
CONFIG += staticlib

! include(../common.pri){
    error("Could not find common.pri file!")
}

DESTDIR = ../../build/.lib
INCLUDEPATH += ../External/

HEADERS += \
    BusinessContainer.h \
    I_SongController.h \
    I_SongEntity.h \
    I_SongPlayer.h \
    I_SongPlayerPresenter.h \
    I_SongPresenter.h \
    SongController.h \
    SongPlayer/SongPlayer.h \
    SongPlayer/I_SongPlayer.h \
    SongControl/SongControl.h \
    SongPlayer/I_MediaPlayer.h

SOURCES += \
    BusinessContainer.cpp \
    SongController.cpp \
    SongPlayer/SongPlayer.cpp \
    SongControl/SongControl.cpp
