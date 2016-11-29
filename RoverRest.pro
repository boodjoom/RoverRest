QT += core network
QT -= gui

CONFIG += c++11

TARGET = RoverRest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += src/main.cpp \
    src/requestmapper.cpp \
    src/rovermanager.cpp \
    src/controller/vehiclecontroller.cpp \
    src/controller/manipcontroller.cpp \
    src/controller/telemetrycontroller.cpp \
    src/controller/statecontroller.cpp

OTHER_FILES += etc/*  logs/* etc/docroot/* install.sh build.sh service.sh

include(common.pri)

win32 {
   DEFINES += QTWEBAPPLIB_IMPORT
}
#QtWebApp
CONFIG += depend_includepath
# Directories, where the *.h files are stored
INCLUDEPATH += $$PWD/3rdparty/QtWebApp

# Directory where the release version of the shared library (*.dll or *.so) is stored, and base name of the file.
CONFIG(release, debug|release) {
    win32:      LIBS += -L$$PWD/3rdparty/lib/$$Platform-$$Compiler/release/          -lQtWebApp1
    unix:!mac:  LIBS += -L$$PWD/3rdparty/lib/rpi-g++/release/              -lQtWebApp
}

# Directory where the debug version of the shared library (*.dll or *.so) is stored, and base name of the file.
CONFIG(debug, debug|release) {
    win32:      LIBS += -L$$PWD/3rdparty/lib/$$Platform-$$Compiler/debug/          -lQtWebAppd1
    unix:!mac:  LIBS += -L$$PWD/3rdparty/lib/rpi-g++/debug/              -lQtWebAppd
}

#RoboBody
INCLUDEPATH += $$PWD/../RoboBody/src

CONFIG(release, debug|release) {
#    win32:      LIBS += -L$$PWD/3rdparty/lib/win32-mingw/release/          -lQtWebApp1
    unix:!mac: LIBS += -lRoboBody
}

CONFIG(debug, debug|release) {
    win32:      LIBS += -L$$PWD/lib/$$Platform-$$Compiler/debug/          -lRoboBody
#    unix:!mac:  LIBS += -L$$PWD/3rdparty/lib/rpi-g++/debug/              -lQtWebAppd
}

HEADERS += \
    src/requestmapper.h \
    src/rovermanager.h \
    src/controller/vehiclecontroller.h \
    src/controller/manipcontroller.h \
    src/controller/telemetrycontroller.h \
    src/controller/statecontroller.h

unix:!mac:{
target.path = /usr/local/bin
INSTALLS += target
}
