/*
* User name: Cameron Holt
* AU UserID: cwh0023
* Project Name: project1.cpp
* File Name: encounter.h
* Use for access to encounter.h
* Compile in jGRASP or g++ compiler.
* Headers knowledge stems from my knowledge of C.
* Random Number generator usage found via Stackoverflow:
* https://stackoverflow.com/questions/2704521/generate-random-double-numbers-in-c
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

#ifndef ENCOUNTER_H
#define ENCOUNTER_H
#include "player.h" //The header for player class.

//Encounter class - manages events
class Encounter
{
public:
	Encounter(); //Default Constructor
	Encounter(Player playerIn); //Constructor with player
	void setPlayer(Player playerIn); //Set user
	Player randomEncounter();
private:
	static const int ENCOUNTERS_POSSIBLE = 6; //Add 1 more if time allows.
	Player player;
	void professor(); //Encounter professor. -time, +int
	void student(); //Encounter a fellow student. -time, -money
	void nothing(); //No event occurs. 
	void work(); //Forced to grade a paper. -time, +money
	void amiibo(); //Find a lost amiibo. +money, +int, +time (Add a random generator to determine which amiibo if time allows)
	void phoneCall(); //Best friend calls. -time, +int
	double fRand(double fMin, double fMax); //Rand function for double
};

#endif