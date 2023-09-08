

QT       += core gui widgets
QT_MAJOR_VERSION = 5
TARGET = PixelCoord
TEMPLATE = app
VERSION = 2.1.2
CONFIG += release

contains(QMAKE_CC, cl) {
message("Current compiler: MSVC")
    DESTDIR = $$PWD/build/msvc
}

contains(QMAKE_CC, gcc) {
message("Current compiler: MinGW")
    DESTDIR = $$PWD/build/mingw
}

DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++11 release
SOURCES += \
        main.cpp \
        mygraphicsview.cpp

HEADERS += \
        mygraphicsview.h

FORMS +=

RESOURCES += \
    resources.qrc


RC_ICONS = logo.ico

