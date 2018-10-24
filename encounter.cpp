/*
* User name: Cameron Holt
* AU UserID: cwh0023
* Project Name: project1.cpp
* File Name: encounter.cpp
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
#include "player.h" //The header for player class.
#include "encounter.h" //The header for encounter class.
using namespace std;


//default constructor
Encounter::Encounter() {
	srand(time(0)); //Sets random seed
}

//Constructor
//Takes in player variable and sets it to the active player variable.
Encounter::Encounter(Player playerIn) {
	srand(time(0)); //Sets random seed
	player = playerIn;
}

//Sets player to playerIn
void Encounter::setPlayer(Player playerIn) {
	player = playerIn;
}

//Sets a random encounter
Player Encounter::randomEncounter() {
	cout << endl; //Formatting
	int randNum = rand() % ENCOUNTERS_POSSIBLE; //Randomly choose from encounters
	switch (randNum) {
	case 0:
		professor();
		break;
	case 1:
		student();
		break;
	case 2:
		nothing();
		break;
	case 3:
		work();
		break;
	case 4:
		amiibo();
		break;
	case 5:
		phoneCall();
		break;
	default:
		cout << "Cameron is a bad programmer.\n";
		break;
	}
	cout << endl; //Formatting
	return player;
}

//Encounter a professor
//Lose time. Chance to gain intelligence.
void Encounter::professor() {
	cout << "A scholarly professor appeared!\n";
	//80% chance to lose 1 time and gain 1-4 intelligence
	//20% chance to lose 4 time and gain 6-10 intelligence
	int randNum = rand() % 100;
	int changeIntel = 0;
	int changeTime = 0;
	if (randNum < 80) {
		cout << "Your conversation is short, but you feel smarter.\n";
		changeIntel = rand() % 4 + 1;
		cout << "You earned " << changeIntel << " intelligence, but lose 1 time\n";
		changeTime = 1;
	}
	else {
		cout << "You two talk for a while. Afterwards, your head is hurting from your newfound knowledge.\n" << endl;
		changeIntel = rand() % 3 + 5;
		cout << "You gain " << changeIntel << " intelligence and lose 3 time\n";
		changeTime = 4;
	}
	player.intelligence = player.intelligence + changeIntel;
	player.time = player.time - changeTime;
	player.steps = player.steps - 1; //1 step closer to end
}

//Encounter a student
//Lose time, chance to gain or lose intelligence. Lose 1 time
void Encounter::student() {
	cout << "A fellow student appeared!\n";
	//60% chance to gain 1-3 intelligence
	//30% chance to gain no intelligence
	//10% chance to lose 1-3 money
	int randNum = rand() % 100;
	int changeIntel = 0;
	int changeTime = 1;
	double changeMoney = 0;
	if (randNum < 60) {
		cout << "The student explains this project to you\n";
		changeIntel = rand() % 3 + 1;
		cout << "You gain " << changeIntel << " intelligence and lose 1 time\n";
	}
	else if (randNum >= 60 && randNum < 90) {
		cout << "The graduate student is swamped with work and runs past without having any sort of conversation with you\n";
		changeIntel = 0;
		cout << "You lose 1 time\n";
	}
	else {
		cout << "The student beats you up and takes some money\n";
		changeMoney = rand() % 3 + 1;
		cout << "You lose " << changeMoney << " intelligence and lose 1 time\n";
		changeMoney = 0 - changeMoney;
	}
	player.intelligence = player.intelligence + changeIntel;
	player.time = player.time - changeTime;
	player.money -= changeMoney;
	player.steps = player.steps - 1; //1 step closer to end
}

double Encounter::fRand(double fMin, double fMax) {
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

//Nothing happens.
//Lose time.
void Encounter::nothing() {
	cout << "You step forward and a special amount of nothing happens.\n";
	player.time -= 1;
	player.steps = player.steps - 1; //1 step closer to victory.
}

//Encounter work to do
//Lose time, chance to lose/gain money
void Encounter::work() {
	//If time allows add different tasks.
	cout << "A pile of papers was placed in your hands!\n";
	//75% chance to gain $1.00-$5.00, lose 1 time
	//20% chance to gain $3.00 -$8.00, lose 3 time
	//5% chance to lose $1.00-$5.00, lose 3 time
	int randNum = rand() % 100;
	double changeMoney = 0;
	int changeTime = 0;
	if (randNum < 75) {
		cout << "You're a fast grader!\n";
		changeMoney = fRand(1.0, 5.0);
		cout << "You gain $" << fixed << setprecision(2) << changeMoney << " and lose 1 time\n";
		changeTime = 1;
	}
	else if (randNum >= 75 && randNum < 95) {
		cout << "You carefully inspect each paper to ensure you're correct in your grading.\n";
		changeMoney = fRand(3.0, 8.0);
		cout << "You gain $" << fixed << setprecision(2) << changeMoney << " and lose 3 time\n";
		changeTime = 3;
	}
	else {
		cout << "You're incredibly bad at grading. You'll have to pay to have them regraded.\n";
		changeMoney = fRand(1.0, 5.0);
		cout << "You lose $" << fixed << setprecision(2) << changeMoney << " and lose 3 time\n";
		changeMoney = 0 - changeMoney;
		changeTime = 3;
	}
	player.money = player.money + changeMoney;
	player.time = player.time - changeTime;
	player.steps = player.steps - 1; //1 step closer to victory.
}

//Encounter amiibo figure.
//Stat increase.
void Encounter::amiibo() {
	cout << "A rare amiibo figures appears.\n";
	int changeMoney = rand() % 10 + 1;
	int changeTime = rand() % 4 + 1;
	int changeIntel = rand() % 5 + 1;
	cout << "You are reminded of simpler times.\nYou place the figure in your bag and see extra money.\n"
		<< "You realize your memory is better than you think.\nYou also see that you have a bit more time.\n";
	player.money = player.money + changeMoney;
	player.intelligence = player.intelligence + changeIntel;
	player.time = player.time + changeTime;
	player.steps = player.steps - 1; //1 step closer to victory.
}

//Encounter a watch
//Gain 1-5 time
void Encounter::phoneCall() {
	cout << "Your phone starts ringing!\n";
	int timeChange = rand() % 5 + 1;
	cout << "Your best friend calls and you talk for a few minutes.!\n";
	cout << "You lose " << timeChange << " time\n";
	player.time = player.time - timeChange;
	player.steps = player.steps - 1; //1 step closer to victory.
}