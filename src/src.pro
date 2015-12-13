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
    Enemy.cpp \
    PlayerCharacter.cpp \
    EntityCreationContext.cpp \
    ITextureProvider.cpp \
    AnimatedSprite.cpp \
    tiled/Trigger.cpp \
    AnimatedSpriteState.cpp \
    AnimatedSpriteSegment.cpp \
    Character.cpp \
    Player.cpp \
    StatusIndicators.cpp \
    TextOverlay.cpp \
    PlayerStateManager.cpp \
	MapSelectionContext.cpp \
    SoundEffectPlayer.cpp

HEADERS += \
	tiled/Tileset.h \
	tiled/Map.h \
	tiled/Layer.h \
	Light.h \
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
    Enemy.h \
    PlayerCharacter.h \
    EntityCreationContext.h \
    ITextureProvider.h \
    AnimatedSprite.h \
	tiled/Trigger.h \
    ITurn.h \
    AnimatedSpriteState.h \
    AnimatedSpriteSegment.h \
    Character.h \
    IEntity.h \
    Player.h \
    StatusIndicators.h \
    TextOverlay.h \
    PlayerStateManager.h \
	MapSelectionContext.h \
    SoundEffectPlayer.h

LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window
INCLUDEPATH += ../libs/json/src
