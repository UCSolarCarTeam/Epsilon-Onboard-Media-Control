INCLUDEPATH += .
QT+=core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network multimedia

                                  CONFIG += static c++11 debug

                                  QMAKE_CXXFLAGS +=
                                  RCC_DIR= ../release
                                  DESTDIR = ../release
                                  OBJECTS_DIR = ../release/.obj
                                  MOC_DIR = ../release/.moc
                                  RCC_DIR = ../release/.rcc
                                  UI_DIR = ../release/.ui
