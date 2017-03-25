TEMPLATE = lib
CONFIG += staticlib

! include(../common.pri){
error("Could not find common.pri file!")
}

PRE_TARGETDEPS += \
    ../../build/.lib/*

DESTDIR = ../../build.lib

HEADERS += \
    DataContainer.h \

SOURCES += \
    DataContianer.cpp\
