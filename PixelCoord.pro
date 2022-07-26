

QT       += core gui widgets

TARGET = PixelCoord
TEMPLATE = app
DESTDIR = $$PWD/bin

DEFINES += QT_DEPRECATED_WARNINGS


CONFIG += c++11

SOURCES += \
        main.cpp \
        mygraphicsview.cpp \
        widget.cpp

HEADERS += \
        mygraphicsview.h \
        widget.h

FORMS += \
        widget.ui

RESOURCES += \
    resources.qrc


RC_ICONS = logo.ico

