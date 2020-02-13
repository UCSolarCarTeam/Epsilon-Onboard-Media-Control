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
    SongControlPresenter.h \
    SongEntity.h \
    SongPlayer.h \
    I_SongControlEntity.h \
    SongControlEntity.h \
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
    SongControlEntity.cpp \
    SongController.cpp \
    CurrentSongPresenter.cpp
