/*
* User name: Cameron Holt
* AU UserID: cwh0023
* Project Name: project1.cpp
* File Name: system.cpp
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
using namespace std;
		
	void System::printScores()
	{
		for (auto score : scores) //C++ for each loop
		{
			std::cout << score.name << " " << score.score << "\n";
		}
	}
	void System::loadScores(std::string filePath)
	{
	string line;
		std::ifstream fileStream(filePath);
		if (fileStream.is_open())
		{
			while (getline(fileStream, line))
			{
				//name score
				Highscore localScore;

			istringstream iss(line);

				iss >> localScore.name;
				iss >> localScore.score;

				scores.push_back(localScore);
			}
		}
	}

	void System::writeScore(Highscore score)
	{
		std::ofstream outStream("highscores.txt", std::ofstream::trunc);
		for (auto score : scores)
		{
			outStream << score.name << " " << score.score << "\n";
		}
	}

	void System::addScore(Highscore score)
	{
		if (scores.size() == 0) 
		{
			scores.push_front(score);
			return;
		}
		for (auto it = scores.begin(); it != scores.end(); ++it) //C++ for each loop
		{
			if (score.score > it->score)
			{
				scores.insert(it, score);
				break;
			}
		}
		scores.push_back(score);
	}


//Constructor. Initializes values.
System::System()
:scores() 
{
	//Player and menu already set
	gameStart = true; //The game has just started.
	needName = true; //We need the player's name
	player.steps = 20; //length of hallway
	highScoreFile = "highscores.txt";
	srand(time(0)); //Sets random seed
}


//Start menu of the game
//Display menu and get input choice
void System::startMenu() {
	//Get name and greet user
	if (needName) {
		cout << "What's your name? ";
		cin >> player.playerName;
		needName = false; //No longer need name.
	}
	cout << "\n====================================================\n";
	cout << "|\t\tWelcome, " << player.playerName << "\t\t\t|";
	cout << "\n====================================================\n";
	//Display the start menu and get player input
	int playerChoice = menu.menuMain();
	//If 1 is inputed, start a new game.
	if (playerChoice == 1) {
		cout << "\nEntering the Game...\n\n";
		workGame();
	}
	//If 2, display highscore
	else if (playerChoice == 2) {
		loadScores("highscores.txt");
		printScores();
		//Repopulate start menu after displaying high scores
		startMenu();
	}
	//If 3, end game
	else if (playerChoice == 3) {
		cout << "Quitting game...\n";
		exit(1);
	}
}

//Displays the game menu and uses player input to step into next game action.
//If start is true, initialize character
//NOT FINISHED ADD ENCOUNTER
void System::workGame() {
	//If just started a new game, initialize character stats and display them.
	if (gameStart) {
		player.time = rand() % 20 + 10; //Range of 10-30
		player.intelligence = rand() % 20 + 10; //range of 10-30
		player.money = fRand(5.0, 20.0); //range of $5.00 - $20.00
		player.steps = 20;
		player.currentStats();
		gameStart = false; //Set start to false, no longer a new game.
	}
	//display status messsage before menu
	cout << "You are " << player.steps << " steps from the goal. Time left: " << player.time << endl;
	//Display game menu, get choice, step into next game action.
	int choice = menu.menuGame();
	int randNum;
	switch (choice) {
		//Step forward. Chance of encounter
	case 1:
		//10% chance for nothing to happen
		//45% chance for encounter
		//45% chance for puzzle
		randNum = rand() % 100;
		if (randNum < 10) {
			cout << "\nYou step forward and nothing happens\n\n";
			player.time = player.time - 1;
			player.steps = player.steps - 1;
		}
		else if (randNum >= 10 && randNum < 55) {
			encounter = Encounter(player); //reinitialize variables in encounter
			player = encounter.randomEncounter();
		}
		else {
			puzzle = Puzzle(player); //reinitialize variables in puzzle
			player = puzzle.randomPuzzle();
		}
		break;
		//Read technical papers. Gain intelligence, lose time.
	case 2:
		readTechPapers();
		break;
		//Search for change. Gain money, lose time.
	case 3:
		searchChange();
		break;
		//View  character stats
	case 4:
		player.currentStats();
		break;
		//Quit the game
	case 5:
		cout << "\nYou FAILED\n";
		exit(1);
		break;
		//Because the menus class handles player input, it should never reach default. 
		//If it does, you messed up somewhere.
	default:
		cout << "Error. Please blame Cameron.\n";
	}
	//Check if lost the game
	if (player.time <= 0 || player.money <= 0 || player.intelligence <= 0) {
		endGame(false);
	}
	//Check if won
	else if (player.steps <= 0) {
		endGame(true);
	}
	//If didn't win or lose, do next workGame.
	else {
		workGame();
	}
}

//Returns player
Player System::getPlayer() {
	return player;
}


//Allows rand to return double, for money initialization.
//(found on stack overflow as noted above).
//Takes the min and the max in, returns the random number.
double System::fRand(double fMin, double fMax) {
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

//endGame function. Ends the game. If won, adds the high score and displays it.
//If lost, asks if they wish to play again.
//NOT FINISHED ADD HIGH SCORES
void System::endGame(bool win) {
	//If lost
	if (!win) {
		cout << "One of your stats have dropped to 0 or less. You have lost.\n";
		player.currentStats();
		int highScoreVal = player.time * player.money * player.intelligence;
		Highscore newScore;
		newScore.name = player.playerName;
		newScore.score = highScoreVal;
		//Add and display high scores
		addScore(newScore);
		writeScore(newScore);
	}
	//If won
	else {
		cout << "You made it out of Shelby Center!\n";
		player.currentStats();
		int highScoreVal = player.time * player.money * player.intelligence;
		cout << "Your score: " << highScoreVal << endl;
		Highscore newScore;
		newScore.name = player.playerName;
		newScore.score = highScoreVal;
		//Add and display high scores
		addScore(newScore);
		writeScore(newScore);
		//Iterate through, if larger list.insert(highScore), otherwise go to the next one

		cout << "\nHighscore list:\n";
	}
	//Ask to replay
	if (replay()) {
		cout << "\nRestarting Game...\n\n";
		gameStart = true;
		startMenu();
	}
	else {
		cout << "\nGoodbye...\n\n";
		exit(1);
	}

}

//Asks if player wants to replay the game, returns true or false.
bool System::replay() {
	//Ask if they want to replay
	cout << "Would you like to play again? (y/n) ";
	string replay;
	cin >> replay;
	//Checks for valid input
	while (replay != "y" && replay != "Y" && replay != "n" && replay != "N") {
		cout << "Invalid input.\n";
		cout << "Would you like to play again? (y/n) ";
		cin >> replay;
	}
	if (replay == "y" || replay == "Y") {
		return true;
	}
	else if (replay == "n" || replay == "N") {
		return false;
	}
}

//Read technical papers
//Lose time, gain intelligence
void System::readTechPapers() {
	cout << "\nYou read technical papers\n";
	int intelChange = rand() % 5 + 1; //Range of 1-5
	cout << "You gain " << intelChange << " intelligence\n\n";
	player.intelligence = player.intelligence + intelChange;
	player.time = player.time - FIXED_TIME_LOST;
}

//Search for loose change
//Gain money, lose time.
void System::searchChange() {
	cout << "\nYou search for loose change\n";
	double moneyChange = fRand(0.01, 100.00);
	cout << "You gain $" << fixed << setprecision(2) << moneyChange << "\n\n";
	player.money = player.money + moneyChange;
	player.time = player.time - FIXED_TIME_LOST;
}


/*************************************************************************************/
/*************************************TESTING*****************************************/
/*************************************************************************************/
