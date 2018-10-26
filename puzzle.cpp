/*
* User name: Cameron Holt
* AU UserID: cwh0023
* Project Name: project1.cpp
* File Name: puzzle.cpp
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
#include "player.h" //Player class
#include "puzzle.h" //Puzzle class
using namespace std;


//default constructor
Puzzle::Puzzle() {
	srand(time(0)); //Sets random seed
}

//Constructor
//Takes in a player and sets it to player variable
Puzzle::Puzzle(Player playerIn) {
	srand(time(0)); //Sets random seed
	player = playerIn;
}

//Sets player to playerIn
void Puzzle::setPlayer(Player playerIn) {
	player = playerIn;
}


//Sets a random puzzle
Player Puzzle::randomPuzzle() {
	cout << endl;
	int randNum = rand() % PUZZLES_POSSIBLE; //Randomly choose from encounters
	switch (randNum) {
	case 0:
		nintendoConsole();
		break;
	case 1:
		child();
		break;
	case 2:
		cards();
		break;
	case 3:
		weeks();
		break;
	case 4:
		pattern();
		break;
	case 5:
		joe();
		break;
	default:
		cout << "The programmer screwed up\n";
		break;
	}
	return player;
}

//random with double
double Puzzle::fRand(double fMin, double fMax) {

	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

//What home console did Nintendo release after the Wii?
//Chance to win money or lose time.
void Puzzle::nintendoConsole() {
	cout << "Some computer science students are walking by and one is playing a triva game, when he's asks his friends which \n";
	cout << "Nintendo home console followed after the successful Wii.";
	cout << "Your choices are:\n1) N64\n2) GameCube\n3) WiiU\n4) Switch\n";
	cout << "What is your answer? (Enter a number 1-4): ";
	cin >> answerChoice;
	verifyInput();
	cout << endl; //Formatting
	int changeIntel = 0;
	int changeTime = 0;
	double changeMoney;
	//Correct answer
	if (answerChoice == 3) {
		changeMoney = fRand(.50, 3.75);
		changeIntel = (rand() % 3 + 1);
		cout << "You answered correctly. The kid pays you $" << fixed << setprecision(2) << changeMoney << endl;
		changeTime = 1;
	}
	else { //Wrong answer
		changeTime = rand() % 3 + 1;
		changeMoney = 0;
		cout << "You answered incorrectly. The nerds mock you about your lack of gaming knowledge.\n";
		cout << "You lose " << changeTime << " time\n";
	}
	player.intelligence = player.intelligence + changeIntel;
	player.money = player.money + changeMoney;
	player.time = player.time - changeTime;
	player.steps = player.steps - 1; //Move 1 step closer.
	cout << endl; //Formatting
}

//Puzzle about Aubie
//Chance to gain/lose intelligence.
void Puzzle::child() {
	cout << "A young child approaches you and asks you a question.";
	cout << "The question is: \n";
	cout << " What is the name of Auburn's tiger?\n";
	cout << "1) Aubie\n2) Tigger\n3) Bouncer\n4) Run away\n";
	cout << "What is your answer? (Enter a number 1-4): ";
	cin >> answerChoice;
	verifyInput();
	cout << endl; //Formatting
	int changeIntel = 0;
	int changeTime = 1;
	int changeStep = 1;
	//Try to run away: 60% chance successful, 40% chance unsuccessful
	if (answerChoice == 4) {
		int randNum = rand() % 100;
		if (randNum < 40) {
			cout << "The child trips you and you land on your head!\n";
			cout << "You lose 10 intelligence and 5 time\n";
			changeTime = 5;
			changeIntel = -10;
		}
		else {
			cout << "You speed around the child screaming \"I'm very late!\" The child starts crying.\n";
			cout << "You lose 7 intelligence but move 4 steps forward\n";
			changeIntel = -7;
			changeStep = 4;
		}
	}
	else if (answerChoice == 1) {
		cout << "You answer: Auburn's tiger is named Aubie.\n";
		cout << "You gain 4 intelligence\n";
		changeIntel = 4;
	}
	else {
		cout << "You answer incorrectly. The child says \"That doesn't sound right.\" and leaves you.\n";
		cout << "You lose 4 intelligence\n";
		changeIntel = -4;
	}
	player.intelligence = player.intelligence + changeIntel;
	player.time = player.time - changeTime;
	player.steps = player.steps - changeStep;
	cout << endl; //Formatting
}

//Puzzle about a scalper's cards.
//gain/lose intelligence
void Puzzle::cards() {
	cout << "A scalper approaches you. If I put 60 cards on ebay and sell 32 of them, how many do I have left? \"\n";
	cout << "1) 5\n2) 28\n3) 19\n4) 24\n";
	cout << "What is your answer? (enter a number 1-4): ";
	cin >> answerChoice;
	verifyInput();
	cout << endl; //Formatting
	int changeIntel = 0;
	if (answerChoice == 2) {
		cout << "\"That is how many cards I have left!\" The scalper exclaims\n";
		cout << "You gain 2 intelligence\n";
		changeIntel = 2;
	}
	else {
		cout << "The scalper looks at you like he's disappointed. Or maybe like he thinks you're an idiot.\n";
		cout << "You lose 2 intelligence\n";
		changeIntel = -2;
	}
	player.intelligence = player.intelligence + changeIntel;
	player.time = player.time - 1;
	player.steps = player.steps - 1;
	cout << endl; //Formatting
}

//How many weeks have 7 days?
//Win money
void Puzzle::weeks() {
	cout << "Robert Sled walks up to you with a camera. He exclaims"
		<< "\"It is time to see if you are supposed to be here!\"\n";
	cout << "Your question is: how many weeks have 7 days?\n";
	cout << "What is your answer? (enter a number): ";
	cin >> answerChoice;
	//If the input isn't valid, prompt for proper input. Loop until good input.
	while (cin.fail()) {
		cin.clear();
		cin.ignore();
		cout << "\nInput invalid. Please enter a valid answer : ";
		cin >> answerChoice;
	}
	cout << endl; //Formatting
	if (answerChoice == 52) {
		cout << "Bob smiles. He says, \"You did well.\"\n";
		cout << "You win $15.00!";
		player.money = player.money + 15.0;
	}
	else {
		cout << "Bob looks dissapointed. \"Guess " << player.playerName << " is not supposed to be here.\"\n";
		cout << "You lose 5 intelligence\n";
		player.intelligence = player.intelligence - 5;
	}
	player.time = player.time - 1;
	player.steps = player.steps - 1;
	cout << endl; //formatting
}

//Pattern is x^2.
//Gain intelligence or lose time.
void Puzzle::pattern() {
	cout << "A fairy appears!\n She says you can only pass if you can place the next 2 numbers in the following pattern:\n";
	cout << "1, 4, 9, 16, ...\n\n";
	cout << "1) 25, 36 \n2) 24, 36 \n3) 25, 144 \n4) 6, 2 \n";
	cout << "What is your answer? (enter a number 1-4): ";
	cin >> answerChoice;
	verifyInput();
	cout << endl; //formatting
	int intelChange = 0;
	int timeChange = 1;
	if (answerChoice == 1) {
		cout << "The fairy transforms into your discrete structures professor. He lets you pass.\n";
		cout << "You gain 3 intelligence\n";
		intelChange = 3;
	}
	else if (answerChoice == 3) {
		cout << "The fairy rolls her eyes. She is not impressed by your inability to count."
			<< " She throws some fairy dust on you and when you look down at your watch you realize you've lost 3 time.";
		timeChange = 3;
	}
	else {
		cout << "Your answer is incorrect. You lose 2 intelligence and spend 2 time trying to pass the fairy.\n";
		timeChange = 2;
		intelChange = -2;
	}
	player.intelligence = player.intelligence + intelChange;
	player.time = player.time - timeChange;
	player.steps = player.steps - 1;
	cout << endl; //Formatting
}

//Joe's Mario Bros trivia.
//Gain nothing, lose time.
void Puzzle::joe() {
	cout << "A teen runs up and blocks your path. He says \"My name is Joe." << endl << "You can't pass until you solve my puzzle. \n"
		<< "The riddle is: In Super Mario Bros 2, you can play as Mario, Peach, Toad and one other character.\""
		<< " Who is the fourth character?";
	cout << "1) Mario\n2) Peach\n3) Luigi\n4) Green Mario\n";
	cout << "What is your answer? (enter a number 1-4): ";
	cin >> answerChoice;
	verifyInput();
	cout << endl; //Formatting
	if (answerChoice == 3) {
		cout << "Joe gives you a high five. Your answer was correct\n";
		cout << "Joe moves out of your way, but gives you nothing for your time.\n";
		player.time = player.time - 1;
	}
	else {
		cout << "Joe punches you in the nose. You tend to your bloody nose for a few minutes.\n";
		cout << "You lose 2 time\n";
		player.time = player.time - 2;
	}
	player.steps = player.steps - 1;
	cout << endl; //Formatting
}

void Puzzle::verifyInput() {
	//If the input isn't valid, prompt for proper input. Loop until good input.
	while (cin.fail() || answerChoice < 1 || answerChoice > 4) {
		cin.clear();
		cin.ignore();
		cout << "\nInput invalid. Please enter a valid answer : ";
		cin >> answerChoice;
	}
}