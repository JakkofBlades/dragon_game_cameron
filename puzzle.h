/*
* User name: Cameron Holt
* AU UserID: cwh0023
* Project Name: project1.cpp
* File Name: puzzle.h
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


#ifndef PUZZLE_H
#define PUZZLE_H
#include "player.h" //Player class

//puzzle class
//Controls the puzzles
class Puzzle {
public:
	Puzzle(); //Default Constructor
	Puzzle(Player playerIn); //Constructor
	void setPlayer(Player playerIn); //Set player
	Player randomPuzzle();
private:
	static const int PUZZLES_POSSIBLE = 6; //Number of different encounters
	Player player;
	void nintendoConsole(); //What home console released after the Wii?
	void child(); //What's the name of the tiger?
	void cards(); //Cards remaining
	void weeks(); //how many months with 28 days
	void pattern(); //letter pattern
	void joe(); //jimmys family
	double fRand(double fMin, double fMax); //Rand function for double
	void verifyInput(); //makes sure input is good.
	int answerChoice; // player answer
};

#endif