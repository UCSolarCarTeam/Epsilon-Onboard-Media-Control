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
../OnBoard-Media-Control/i_threadable.h \

FORMS    += songloader.ui
