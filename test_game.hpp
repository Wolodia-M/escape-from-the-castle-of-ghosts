/*  Simple game where you need to escape from castle full of ghosts
    Copyright (C) 2022 WolodiaM

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
    My email: w.melnyk07@gmail.com    */
// Libraries
// Input / output
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_image.h"
// Console
#include "stdio.h"
// Work with text
#include "string"
// Randomiser
#include "random"
// For timers
#include "ctime"
// Work with file
#include "filesystem"
#include "fstream"
// Platform specific
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
#include "windows.h"
#elif defined(__linux__) || defined(__linux) || defined(linux)
#include "stdlib.h"
#endif
// Namespaces
using namespace std;
// Defines
const int SCREAN_WIGHT = 320;
const int SCREAN_HEIGHT = 240;
const string GAME_NAME = "Escape from the Castle of ghosts";
// #define DEBUG // ON / OFF debug
// Debug modes:
// DEBUG_GET_LEVEL_HELPER_DATA  - print helper data from levels
// DEBUG_KEY                    - print waht key is pressed 
// DEBUG_LOAD_TEXTURES          - print errors when loading texture atlass
// DEBUG_DECODE_LEVEL           - print raw data from level decoding
// DEBUG_WINDOVED               - set game to windoved mode
// Variables
bool is_run = 1;                        // Control run of game
bool time_writed = false;               // Used for write statiscics
int temp_level_number;                  // Used internally in level loading
clock_t timer = 0;                      // Timer for time of play
SDL_Window* window = NULL;              // App window 
SDL_Event event;                        // App event handler
Mix_Music* music = NULL;                // App music handler
SDL_Renderer* renderer = NULL;          // Renderer
SDL_Texture* mainScreen = NULL;         // Texture
SDL_Surface *mainScrn = NULL;           // Surface
SDL_GameController *joystick = NULL;    // Joystick 1
SDL_Joystick *joy = NULL;               // Joystick 2 ;)
// Files
#include "engine.hpp"
EngineClassMain engine;
#include "game_main.hpp"        // Game header
// My namespaces
using namespace game;           // Game main namespace
