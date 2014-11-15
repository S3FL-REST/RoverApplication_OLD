#-------------------------------------------------
#
# Project created by QtCreator 2014-11-14T14:38:38
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = RoverApplication
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    Rover/robotdata.cpp \
    Rover/serialconnection.cpp \
    Rover/serialworker.cpp \
    robotmain.cpp \
    Network/networkclient.cpp \
    Network/networkdata.cpp

HEADERS += \
    Rover/robotdata.h \
    Rover/serialconnection.h \
    Rover/serialworker.h \
    Rover/robotmain.h \
    robotmain.h \
    Network/networkclient.h \
    Network/networkdata.h

unix:!macx: LIBS += -lserial
