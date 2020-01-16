TEMPLATE = app
LIBS += -L../ViewLayer/.lib -L../BusinessLayer/.lib -lViewLayer -lBusinessLayer

! include(../common.pri){
    error("Could not find common.pri file!")
}

PRE_TARGETDEPS += \
 ../ViewLayer/.lib/* \
 ../BusinessLayer/.lib/*

TARGET = OnboardMediaControl

DESTDIR = ../bin/

SOURCES += \
    main.cpp \
    OnboardMediaControl.cpp

HEADERS += \
    OnboardMediaControl.h

RESOURCES += \
    ../ViewLayer/uiresources.qrc

DISTFILES += \
    ../Resources/PlaySmall.png \
    ../Resources/Next.png \
    ../Resources/Previous.png \
    ../Resources/Fonts/BurlingamePro-Light.otf
