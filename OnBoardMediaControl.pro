#-------------------------------------------------
#
# Project created by QtCreator 2016-11-23T18:42:05
#
#-------------------------------------------------

QT       += core widgets multimedia
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OnBoardMediaControl
TEMPLATE = app


SOURCES += OnBoard-Media-Control/main.cpp\
song_player/SongPlayer.cpp\
OnBoard-Media-Control/OnBoardMediaControl.cpp

HEADERS  += song_player/SongPlayer.h\
OnBoard-Media-Control/OnBoardMediaControl.h

FORMS    += song_player/SongPlayer.ui
