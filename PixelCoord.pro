

QT       += core gui widgets

TARGET = RelativeCoord
TEMPLATE = app
DESTDIR = $$PWD/bin

DEFINES += QT_DEPRECATED_WARNINGS


CONFIG += c++11

SOURCES += \
        main.cpp \
        paintlabel.cpp \
        widget.cpp

HEADERS += \
        paintlabel.h \
        widget.h

FORMS += \
        widget.ui

