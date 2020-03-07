TEMPLATE = lib
CONFIG += staticlib

! include(../common.pri){
    error("Could not find common.pri file!")
}

DESTDIR = .lib
INCLUDEPATH +=  ../External \
                SongPlayer \
                SongState \
                SongPlayerState \
                SongController \
                Presenter/SongControl \
                Presenter/CurrentSong \


HEADERS += \
    BusinessContainer.h \
    SongPlayerState/I_SongPlayerState.h \
    SongPlayerState/SongPlayerState.h \
    SongState/I_SongState.h \
    SongState/SongState.h \
    SongPlayer/I_SongPlayer.h \
    SongPlayer/SongPlayer.h \
    SongController/I_SongController.h \
    SongController/SongController.h \
    Presenter/SongControl/SongControlPresenter.h \
    Presenter/SongControl/I_SongControlPresenter.h \
    Presenter/CurrentSong/I_CurrentSongPresenter.h \
    Presenter/CurrentSong/CurrentSongPresenter.h \

SOURCES += \
    BusinessContainer.cpp \
    SongPlayerState/SongPlayerState.cpp \
    SongState/SongState.cpp \
    SongPlayer/SongPlayer.cpp \
    SongController/SongController.cpp \
    Presenter/SongControl/SongControlPresenter.cpp \
    Presenter/CurrentSong/CurrentSongPresenter.cpp \
