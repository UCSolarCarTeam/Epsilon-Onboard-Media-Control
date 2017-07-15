TEMPLATE = app
LIBS += -L../../build/.lib -lViewLayer -lBusinessLayer

! include(../common.pri){
    error("Could not find common.pri file!")
}

PRE_TARGETDEPS += \
 ../../build/.lib/*

TARGET = OnboardMediaControl

DESTDIR = ../../build

SOURCES += \
    main.cpp \
    OnboardMediaControl.cpp

HEADERS += \
    OnboardMediaControl.h
