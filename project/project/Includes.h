// ====================================================================================================
// Includes
// ====================================================================================================
#include <stdio.h>
#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <array>
#include <queue>
#include <functional>
#include <cassert>
#include <exception>

// ====================================================================================================
// SFML Includes
// ====================================================================================================
#include <SFML/Graphics.hpp>

// ====================================================================================================
// Libraries
// ====================================================================================================
#pragma comment(lib, "sfml-main.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-graphics.lib")
//#pragma comment(lib, "sfml-audio.lib")
//#pragma comment(lib, "sfml-network.lib")

// ====================================================================================================
// Macros
// ====================================================================================================
#ifdef _WIN32
	#include <Windows.h>
	#define FRESCHI_FATAL_ERROR(msg) MessageBox(NULL,msg,"Freschi: Fatal Error",NULL); \
		exit(0);
#else
	#define FRESCHI_FATAL_ERROR(msg) exit(0);
#endif

#define ACCESSOR_FUNC(name, type, mVar) void Set##name(##type _##name) { ##mVar = _##name; }; \
	##type Get##name() { return mVar; }

// ====================================================================================================
// Forward Declarations
// ====================================================================================================
class Entity;
class Aircraft;
class Player;
class Game;
class World;
class SceneNode;
struct Command;
class CommandQueue;

// ====================================================================================================
// Internal Includes
// ====================================================================================================
#include "Foreach.hpp"
#include "ResourceManager.h"
#include "SceneNode.h"
#include "SpriteNode.h"
#include "Command.h"
#include "CommandQueue.h"
#include "World.h"
#include "Player.h"
#include "Game.h"
#include "Category.h"
#include "Entity.h"
#include "Aircraft.h"

// ====================================================================================================
// Lua
// ====================================================================================================
#include "lua/Lua.h"