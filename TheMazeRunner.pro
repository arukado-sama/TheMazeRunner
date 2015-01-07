#-------------------------------------------------
#
# Project created by QtCreator 2014-12-19T13:52:57
#
#-------------------------------------------------

QT       += core
QT       += widgets

QT       -= gui

TARGET = TheMazeRunner
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    maze.cpp \
    sprite.cpp \
    entity.cpp

LIBS += -lsfml-graphics
LIBS += -lsfml-window
LIBS += -lsfml-system

HEADERS += \
    maze.h \
    sprite.h \
    mazeTypes.h \
    defines.h \
    entity.h
