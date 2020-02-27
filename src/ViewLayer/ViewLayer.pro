TEMPLATE = lib
CONFIG += staticlib

! include(../common.pri){
error("Could not find common.pri file!")
}

DESTDIR = .lib
INCLUDEPATH += ../BusinessLayer \
                ../BusinessLayer/SongControlEntity \
                ../BusinessLayer/Presenter/SongControl \
                ../BusinessLayer/Presenter/CurrentSong \
                ../BusinessLayer/SongEntity \
                ProgressBar \
                FontLoader \
                SongPlayerUI \
                SongPlayerView \
                SongPlayerView/SongControl \
                SongPlayerView/CurrentSong \
                ../Resources \

HEADERS += \
    ViewContainer.h \
    ProgressBar/ProgressBar.h\
    FontLoader/FontLoader.h \
    SongPlayerUI/I_CurrentSongUi.h \
    SongPlayerUI/I_SongControlUi.h \
    SongPlayerUI/SongPlayerUi.h \
    SongPlayerView/SongControl/SongControlView.h \
    SongPlayerView/CurrentSong/CurrentSongView.h \

SOURCES += \
    ViewContainer.cpp \
    ProgressBar/ProgressBar.cpp \
    FontLoader/FontLoader.cpp \
    SongPlayerUI/SongPlayerUi.cpp \
    SongPlayerView/SongControl/SongControlView.cpp \
    SongPlayerView/CurrentSong/CurrentSongView.cpp \

FORMS += \
    SongPlayerUi.ui \
