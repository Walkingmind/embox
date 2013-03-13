TARGET = emboxvc
include(../../qpluginbase.pri)

TEMPLATE = lib
CONFIG += staticlib

QTDIR_build:DESTDIR = $$QT_BUILD_TREE/plugins/platforms

SOURCES += main.cpp emboxvcintegration.cpp emboxvcwindowsurface.cpp
HEADERS += emboxvcwindowsurface.h emboxvcintegration.h

include(../fontdatabases/genericunix/genericunix.pri)

target.path += $$[QT_INSTALL_PLUGINS]/platforms
INSTALLS += target
