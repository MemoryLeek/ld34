TARGET = ld34
DESTDIR = ../bin
OBJECTS_DIR = build

CONFIG += c++11
CONFIG -= console
QMAKE_CXXFLAGS += -Wall -Werror -Wno-unused-parameter

SOURCES += main.cpp \
	tiled/Tileset.cpp \
	tiled/Map.cpp \
	tiled/Layer.cpp \
    Light.cpp

HEADERS += \
	tiled/Tileset.h \
	tiled/Map.h \
	tiled/Layer.h \
    Light.h

LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window
INCLUDEPATH += ../libs/json/src
