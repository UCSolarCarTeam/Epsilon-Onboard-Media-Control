TEMPLATE = lib
CONFIG += staticlib

! include(../common.pri){
    error("Could not find common.pri file!")
}

DESTDIR = .lib
INCLUDEPATH += ../External/

HEADERS += \
    BusinessContainer.h \
    I_SongEntity.h \
    I_SongPlayer.h \
    I_SongPlayerPresenter.h \
    I_SongPresenter.h \
    SongControlPresenter.h \
    SongEntity.h \
    SongPlayer.h \
    SongPlayer/SongPlayer.h \
    SongPlayer/I_SongPlayer.h \
    SongControl/SongControl.h \
    SongPlayer/I_MediaPlayer.h \
    I_SongControlEntity.h \
    SongControlEntity.h \
    I_SongControllerDeprecated.h \
    SongControllerDeprecated.h \
    I_SongController.h \
    SongController.h \
    I_CurrentSongPresenter.h \
    I_SongControlPresenter.h \
    CurrentSongPresenter.h

SOURCES += \
    BusinessContainer.cpp \
    SongControlPresenter.cpp \
    SongEntity.cpp \
    SongPlayer.cpp \
    SongPlayer/SongPlayer.cpp \
    SongControl/SongControl.cpp \
    SongControlEntity.cpp \
    SongControllerDeprecated.cpp \
    SongController.cpp \
    CurrentSongPresenter.cpp
