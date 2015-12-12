TARGET = ld34
DESTDIR = ../bin
OBJECTS_DIR = build

CONFIG += c++11 debug
CONFIG -= console
QMAKE_CXXFLAGS += -Wall -Werror -Wno-unused-parameter

SOURCES += main.cpp \
	tiled/Tileset.cpp \
	tiled/Map.cpp \
	tiled/Layer.cpp \
	Light.cpp \
	Entity.cpp \
	Window.cpp \
	states/TestState.cpp \
	states/LogoState.cpp \
	StateHandler.cpp \
	StateCreationContext.cpp \
    states/MenuState.cpp \
    MenuDefinition.cpp \
    MenuDefinitionBuilder.cpp \
    states/MainMenuState.cpp \
    MenuDefinitionEntry.cpp \
    CollisionHandler.cpp \
    LightContext.cpp \
    TurnHandler.cpp \
	EntityManager.cpp \
    Enemy.cpp

HEADERS += \
	tiled/Tileset.h \
	tiled/Map.h \
	tiled/Layer.h \
	Light.h \
	Entity.h \
	Window.h \
	IState.h \
	states/TestState.h \
	states/LogoState.h \
	StateHandler.h \
	Util.h \
	StateCreationContext.h \
    states/MenuState.h \
    MenuDefinition.h \
    MenuDefinitionBuilder.h \
    states/MainMenuState.h \
    MenuDefinitionEntry.h \
    CollisionHandler.h \
    LightContext.h \
    TurnHandler.h \
	EntityManager.h \
    Enemy.h

LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window
INCLUDEPATH += ../libs/json/src
