/*
* User name: Cameron Holt
* AU UserID: cwh0023
* Project Name: project1.cpp
* File Name: menus.h
* Use for access to menu.cpp.
* Compile in jGRASP or g++ compiler.
* Headers knowledge stems from my knowledge of C.
*/

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <string>
#include <ctime>
#include <iomanip> //std:setw
#include <random>
using namespace std;


ifndef MENU_H
#define MENU_H

//Menus class
class Menus 
{
public:
	Menus(); //Default constructor
	int menuGame(); //Generates the game's menu.
	int menuMain(); //Generates the main menu.
private:
	int playerAction; //Player chooses an action.
	void checkGameAction(); //Check that an in-game action is valid.
	void checkMainAction(); //Check that a main menu aciton is valid.
};

#endif