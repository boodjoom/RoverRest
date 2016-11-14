QT += core network
QT -= gui

CONFIG += c++11

TARGET = RoverRest
CONFIG += console depend_includepath
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += src/main.cpp \
    src/requestmapper.cpp \
    src/rovermanager.cpp

OTHER_FILES += etc/*  logs/*

win32 {
   DEFINES += QTWEBAPPLIB_IMPORT
}

# Directories, where the *.h files are stored
INCLUDEPATH += $$PWD/3rdparty/QtWebApp

# Directory where the release version of the shared library (*.dll or *.so) is stored, and base name of the file.
CONFIG(release, debug|release) {
    win32:      LIBS += -L$$PWD/3rdparty/lib/win32-mingw/release/          -lQtWebApp1
    unix:!mac:  LIBS += -L$$PWD/3rdparty/lib/rpi-g++/release/              -lQtWebApp
}

# Directory where the debug version of the shared library (*.dll or *.so) is stored, and base name of the file.
CONFIG(debug, debug|release) {
    win32:      LIBS += -L$$PWD/3rdparty/lib/win32-mingw/debug/          -lQtWebAppd1
    unix:!mac:  LIBS += -L$$PWD/3rdparty/lib/rpi-g++/debug/              -lQtWebAppd
}

HEADERS += \
    src/requestmapper.h \
    src/rovermanager.h
