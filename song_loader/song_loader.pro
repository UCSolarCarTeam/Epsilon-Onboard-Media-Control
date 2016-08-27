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


SOURCES += main.cpp\
        songloader.cpp

HEADERS  += songloader.h \
    i_song_loader_observer.h \
    i_threadable.h \
    observable.h

FORMS    += songloader.ui
