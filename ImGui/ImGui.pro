#-------------------------------------------------
#
# Project created by QtCreator 2016-11-08T15:16:50
#
#-------------------------------------------------

QT       -= core gui

TARGET = ImGui
TEMPLATE = lib

DEFINES += IMGUI_LIBRARY

SOURCES += imgui.cpp

HEADERS += imgui.h\
        imgui_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
