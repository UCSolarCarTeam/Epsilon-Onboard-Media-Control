#-------------------------------------------------
#
# Project created by QtCreator 2016-08-27T15:09:28
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = song_loader
TEMPLATE = app


SOURCES += ../OnBoard-Media-Control/main.cpp\
        songloader.cpp

HEADERS  += songloader.h \
    i_song_loader_observer.h \
    ../OnBoard-Media-Control/i_threadable.h \
    ../OnBoard-Media-Control/observable.h

FORMS    += songloader.ui
