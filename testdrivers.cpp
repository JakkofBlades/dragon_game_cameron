/*
* User name: Cameron Holt
* AU UserID: cwh0023
* Project Name: project1.cpp
* File Name: testdrivers.cpp
* Compile in jGRASP or g++ compiler.
*/

#include "system.h" //System header
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <string>
#include <ctime>
#include <iomanip> //std:setw
#include <random>
#include "menus.h" //Menu class
#include "player.h" //Player class
#include "encounter.h" //Encounter class
#include "puzzle.h" //Puzzle class
#include <list> //Linked List
#include <sstream> //String stream
#include "system.h"
#include "testdrivers.h"
using namespace std;

bool testHighScore()
{
	Highscore score = { "Donald", 3000};
	Highscore score2 = {"Mickey", 5};
	Highscore score3 = {"Minnie", 6};
	Highscore score4 = {"Goofy", 7};
	System system;
	system.addScore(score);
	system.addScore(score4);
	system.addScore(score3);
	system.addScore(score2);
	system.printScores();
	return true;
}