TEMPLATE = lib
CONFIG += staticlib

! include(../common.pri){
    error("Could not find common.pri file!")
}

DESTDIR = .lib
INCLUDEPATH += ../External/SongUrlSource \
                ../External/SongUrlSource/Local \
                SongPlayer \
                SongEntity \
                SongControlEntity \
                SongController \
                Presenter/SongControl \
                Presenter/CurrentSong \


HEADERS += \
    BusinessContainer.h \
    SongPlayer/I_SongPlayer.h \
    SongPlayer/SongPlayer.h \
    SongEntity/I_SongEntity.h \
    SongEntity/SongEntity.h \
    SongControlEntity/I_SongControlEntity.h \
    SongControlEntity/SongControlEntity.h \
    SongController/I_SongController.h \
    SongController/SongController.h \
    Presenter/SongControl/SongControlPresenter.h \
    Presenter/SongControl/I_SongControlPresenter.h \
    Presenter/CurrentSong/I_CurrentSongPresenter.h \
    Presenter/CurrentSong/CurrentSongPresenter.h \

SOURCES += \
    BusinessContainer.cpp \
    SongPlayer/SongPlayer.cpp \
    SongEntity/SongEntity.cpp \
    SongControlEntity/SongControlEntity.cpp \
    SongController/SongController.cpp \
    Presenter/SongControl/SongControlPresenter.cpp \
    Presenter/CurrentSong/CurrentSongPresenter.cpp \
