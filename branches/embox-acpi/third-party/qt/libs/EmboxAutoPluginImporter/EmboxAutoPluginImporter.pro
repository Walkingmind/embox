#-------------------------------------------------
#
# Project created by QtCreator 2013-01-25T15:08:54
#
#-------------------------------------------------

QT       -= gui

TARGET = EmboxAutoPluginImporter
TEMPLATE = lib
CONFIG += staticlib
CONFIG += create_prl

SOURCES += emboxautopluginimporter.cpp

LIBS        += -L$$[QT_INSTALL_PLUGINS]/platforms

QTPLUGIN          += qminimal
contains(DEFINES, QEMBOX_PLUGIN_VNC) {
	QTPLUGIN          += qvncgraphicssystem
}
contains(DEFINES, QEMBOX_PLUGIN_EMBOXVC) {
	QTPLUGIN          += emboxvc
}

unix:!symbian {
    target.path = $$[QT_INSTALL_LIBS]
    INSTALLS += target
}