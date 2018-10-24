/*
* User name: Cameron Holt
* AU UserID: cwh0023
* Project Name: project1.cpp
* File Name: cwh0023-project1.cpp
* Compile in jGRASP or g++ compiler.
* Copy the following into the terminal:
* g++ menus.cpp player.cpp system.cpp encounter.cpp puzzles.cpp game.cpp -o CollegeDnD
*
*/

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <string>
#include <ctime>
#include <iomanip> //std:setw
#include <random>
#include "system.h"		//System class
#include "menus.h"		//Menu class
#include "player.h"		//Player Class
#include "encounter.h"  //Encounter class
#include "puzzle.h"	//Puzzle class
using namespace std;

//Starts the game.
int main() 
{
	System awakenSystem;
	awakenSystem.startMenu();
}
