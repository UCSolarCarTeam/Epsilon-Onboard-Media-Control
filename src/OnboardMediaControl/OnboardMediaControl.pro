TEMPLATE = app
LIBS += -L../ViewLayer/.lib -L../BusinessLayer/.lib -lViewLayer -lBusinessLayer -L../External/.lib -lExternal

! include(../common.pri){
    error("Could not find common.pri file!")
}

PRE_TARGETDEPS += \
 ../ViewLayer/.lib/* \
 ../BusinessLayer/.lib/* \
 ../External/.lib/*

TARGET = OnboardMediaControl

DESTDIR = ../bin/
INCLUDEPATH += ../BusinessLayer \
               ../ViewLayer \

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
