#-------------------------------------------------
#
# Project created by QtCreator 2016-04-02T17:12:52
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = assignment-part1
TEMPLATE = app

SOURCES += main.cpp\
        dialog.cpp \
    body.cpp \
    config.cpp \
    config_section.cpp \
    config_keyvalue.cpp \
    planetary_bodybuilder.cpp

HEADERS  += dialog.h \
    body.h \
    debug.h \
    config_keyvalue.h \
    config.h \
    config_section.h \
    prototype.h \
    planetary_bodybuilder.h \
    bodybuilder.h \
    galaxy.h \
    solarsystem.h \
    cluster.h \
    component.h \
    composite.h

FORMS    += dialog.ui

OTHER_FILES += \
    ../build-assignment-part1-Desktop-Debug/config.ini
