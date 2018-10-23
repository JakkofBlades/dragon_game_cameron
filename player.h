/*
* User name: Cameron Holt
* AU UserID: cwh0023
* Project Name: project1.cpp
* File Name: Player.h
* Use for access to player.cpp
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
using namespace std;

//Header guard.
#ifndef PLAYER_H 
#define PLAYER_H

//Player Class
//Contains information about character stats (intelligence, time and money)
class Player {
	public:
		Player(); //Constructor for the class
		Player(string playName); //Constructor with a player name.
		Player(string playName, int intelIn, int timeIn, double moneyIn); //Constructor with input for all stats.
		string playerName; //Name of player
		int intelligence; //intelligence of a character
		int time; //Time left
		double money; //Money player currently has.
		int steps;
		void currentStats(); //Shows player their current stats.
private:
	//Constant values
	static const int DEFAULT_TIME = 30;
	static const int DEFAULT_INTELLEIGENCE = 20;
	static constexpr double DEFAULT_MONEY = 13.50;
};

#endif