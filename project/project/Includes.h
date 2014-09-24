// ====================================================================================================
// Includes
// ====================================================================================================
#include <stdio.h>
#include <iostream>
#include <memory>
#include <map>
#include <array>
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

// ====================================================================================================
// Most important classes
// ====================================================================================================
class Entity;
class Aircraft;
class Game;
class World;

//#include "Textures.h"
#include "ResourceManager.h"
#include "SceneNode.h"
#include "SpriteNode.h"
#include "World.h"
#include "Game.h"
#include "Entity.h"
#include "Aircraft.h"