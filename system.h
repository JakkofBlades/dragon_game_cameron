/*
* User name: Cameron Holt
* AU UserID: cwh0023
* Project Name: project1.cpp
* File Name: system.h
* Compile in jGRASP or g++ compiler.
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

#ifndef SYSTEM_H
#define SYSTEM_H
#include "menus.h" //Menu class
#include "player.h" //Player class
#include "encounter.h" //Encounter class
#include "puzzle.h" //Puzzle class

//High score struct 
struct Highscore {
	string name;
	int score;
};

class System {
public:
	System(); //Constructor
	void startMenu(); //Calls the start menu, waits for choices.
	void gameStep(); //Steps to next move in game
	void displayHighScore(); //Display high scores
	void addHighScore(string name, int score); //Adds high score
	Character getCharacter(); //Returns the character so other classes can use it.
	void setScoreFile(string filename); //Changes highscore file, refills array (USED FOR TESTING)
	bool replay(); //Sees if player wants to play again
	void readPapers(); //Lose time, gain intel
	void searchChange(); //Lose time, gain money
	void endGame(bool win); //End game
private:
	void fillScoreArray(); //Create score array for high scores
	void emptyScoreArray(); //Clears score array
	double fRand(double fMin, double fMax); //Rand function for double
	void writeHighScore(); // Writes highscore to file
	static const int MAX_SCORES = 10; //Max number of high scores to show
	static const int FIXED_TIME_LOSS = 1; //Time loss for collecting change or reading papers
	Player player;
	Menus menu;
	Encounter encounter;
	Puzzle puzzle;
	int numOfScores; //Number of high scores in file
	string highScoreFile; //File name for highscore
	Highscore highscore_list; //highscore linked list
	bool start;
	bool name;
	int fixedTimeLoss; //Time loss for collecting change or reading papers
};
#endif