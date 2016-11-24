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
song_player/songplayer.cpp\
song_loader/songloader.cpp

HEADERS  += song_player/songplayer.h\
song_loader/songloader.h

FORMS    += song_player/songplayer.ui
song_loader/songloader.ui
