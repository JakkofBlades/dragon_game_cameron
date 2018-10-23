/*
* User name: Cameron Holt
* AU UserID: cwh0023
* Project Name: project1.cpp
* File Name: system.cpp
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
#include "menus.h" //Menu class
#include "player.h" //Character class
#include "encounter.h" //Encounter class
#include "puzzle.h" //Puzzle class
#include <list> //Linked List
using namespace std;


//High score struct 
struct Highscore {
	string name;
	int score;
};

//System class
//The backbone of the game. Makes calls to other classes to make a cohesive game.
class System {
public:
	System(); //Constructor
	void startMenu(); //Calls the start menu, waits for choices.
	void workGame(); //Steps to next move in game
	void displayHighScore(); //Display high scores
	void addHighScore(string name, int score); //Adds high score
	Player getCharacter(); //Returns the character so other classes can use it.
	void setScoreFile(string filename); //Changes highscore file, refills array (USED FOR TESTING)
	bool replay(); //Sees if player wants to play again
	void readTechPapers(); //Lose time, gain intel
	void searchChange(); //Lose time, gain money
	void endGame(bool win); //End game
	std::list<Highscore> scores; //Linked list of scores.
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
	bool gameStart;
	bool needName; //Check if need name or note
};


//Testing prototypes
void test_displayHighScore();
void test_replay();
void test_endGame();
void test_readPapers();
void test_changeSearch();
void test_addHighScore();

//For testing, delete or comment before submitting
//int main() {
//test_displayHighScore();
//test_replay();
//test_endGame();
//test_readPapers();
//test_changeSearch();
//test_addHighScore();
//}

//Constructor. Initializes values.
System::System() {
	//Player and menu already set
	gameStart = true; //The game has just started.
	needName = true; //We need the player's name
	player.steps = 20; //length of hallway
	emptyScoreList();
	highScoreFile = "highscores.txt";
	fillScoreArray();
	srand(time(0)); //Sets random seed
}

//Start menu of the game
//Display menu and get input choice
void System::startMenu() {
	//Get name and greet user
	if (needName) {
		cout << "What's your name? ";
		cin >> player.name;
		needName = false; //No longer need name.
	}
	cout << "\n====================================================\n";
	cout << "|\t\tWelcome, " << player.name << "\t\t\t|";
	cout << "\n====================================================\n";
	//Display the start menu and get player input
	int playerChoice = menu.mainMenu();
	//If 1 is inputed, start a new game.
	if (playerChoice == 1) {
		cout << "\nEntering the Game...\n\n";
		workGame();
	}
	//If 2, display highscore
	else if (playerChoice == 2) {
		displayHighScore();
		//Repopulate start menu after displaying high scores
		startMenu();
	}
	//If 3, end game
	else if (playerChoice == 3) {
		cout << "Quitting game...";
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
		player.displayStats();
		gameStart = false; //Set start to false, no longer a new game.
	}
	//display status messsage before menu
	cout << "You are " << player.steps << " steps from the goal. Time left: " << player.time << endl;
	//Display game menu, get choice, step into next game action.
	int choice = menu.gameMenu();
	int randNum;
	switch (choice) {
		//Step forward. Chance of encounter
	case 1:
		//10% chance for nothing to happen
		//45% chance for encounter
		//45% chance for puzzle
		randNum = rand() % 100;
		if (randNum < 10) {
			cout << "\nYou step forward and nothing happens\n";
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
		player.displayStats();
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

//Displays the highscores stored in highscore_array.
void System::displayHighScore() {
	//Display the highscore
	for (int i = 0; i < numOfScores; i++) {
		if (highscore_array[i].score != -1) {
			cout << highscore_array[i].name << " " << highscore_array[i].score << endl;
		}
	}
	//If less than 10 scores, inform user there are no more.
	if (numOfScores < MAX_SCORES - 1) {
		cout << "-no more scores to show-\n\n";
	}
}

//Fills highscore_array with up to MAX_SCORE scores. Does this when the system is created
//So it is easier to display and add scores later.
//File is formated as follows: Name (newline) score (newline)
void System::fillScoreArray() {
	ifstream inStream;
	inStream.open((char*)highScoreFile.c_str());
	//If cannot find or open, exit program
	if (inStream.fail()) {
		cout << "File open failed. Please use file highscores.txt\n";
		exit(1);
	}
	//input high scores into an array
	int index = 0;
	do {
		inStream >> highscore_array[index].name;
		inStream >> highscore_array[index].score;
		index++;
	} while (!inStream.eof() && index < MAX_SCORES);
	//Close file
	inStream.close();
	//Set number of scores to how many there are.
	numOfScores = index;
}

//Change filename for the highscore file. Only used for testing.
void System::setScoreFile(string filename) {
	highScoreFile = filename;
	emptyScoreArray();
	fillScoreArray();
}

//Empties score array. Reset numOfScores
//Mainly used for testing purposes.
void System::emptyScoreArray() {
	for (int i = 0; i < MAX_SCORES; i++) {
		highscore_array[i].name = "";
		highscore_array[i].score = -1;
	}
	numOfScores = 0;
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
		player.displayStats();
	}
	//If won
	else {
		cout << "You made it out of Shelby Center!\n";
		player.displayStats();
		int highScore = player.time * player.money * player.intelligence;
		cout << "Your score: " << highScore << endl;
		addHighScore(player.name, highScore);
		//Add and display high scores
		cout << "\nHighscore list:\n";
		displayHighScore();
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
	player.time = player.time - FIXED_TIME_LOSS;
}

//Search for loose change
//Gain money, lose time.
void System::searchChange() {
	cout << "\nYou search for loose change\n";
	double moneyChange = fRand(0.01, 100.00);
	cout << "You gain $" << fixed << setprecision(2) << moneyChange << "\n\n";
	player.money = player.money + moneyChange;
	player.time = player.time - FIXED_TIME_LOSS;
}


//Adds highscore to highscore array, then call to write it.
void System::addHighScore(string name, int score) {
	//Create highscore
	Highscore newHighScore;
	newHighScore.name = name;
	newHighScore.score = score;
	int target = -1;
	//Sort scores
	//Find target spot first
	for (int i = 0; i < numOfScores; i++) {
		//If score is >, this is the target spot. Break out of loop.
		if (score > highscore_array[i].score) {
			target = i;
			break;
		}
	}
	//Now that target spot is there, we need to shift all values from target spot on to the right one.
	if (target != -1) {
		if (numOfScores < MAX_SCORES) {
			numOfScores++;
		}
		for (int j = MAX_SCORES - 1; j > target; j--) {
			highscore_array[j] = highscore_array[j - 1];
		}
		//set target spot to new score
		highscore_array[target] = newHighScore;
		//write the highscore to file
		writeHighScore();
	}
}

//Writes highscore to file
void System::writeHighScore() {
	ofstream outStream;
	//Open/create file
	outStream.open((char*)highScoreFile.c_str());
	if (outStream.fail()) {
		cout << "Could not write to file";
	}
	else {
		for (int i = 0; i <= numOfScores; i++) {
			outStream << highscore_array[i].name << endl;
			outStream << highscore_array[i].score << endl;
		}
	}
	outStream.close();
}

/*************************************************************************************/
/*************************************TESTING*****************************************/
/*************************************************************************************/
//Test highscores system
void test_displayHighScore() {
	System system;
	cout << "Testing for displaying highscores\n";
	//Test 1: 10 scores
	cout << "Test 1: file with exactly 10 scores\n";
	system.setScoreFile("test1.txt");
	system.displayHighScore();
	cout << "Test 1: Passed\n\n";
	//Test 2: List that isn't full (3 scores)
	cout << "Test 2: file with only 3 scores\n";
	system.setScoreFile("test2.txt");
	system.displayHighScore();
	cout << "Test 2 Passed\n\n";
	//Test 3: Empty file
	cout << "Test 3: Empty file\n";
	system.setScoreFile("test3.txt");
	system.displayHighScore();
	cout << "Test 3 Passed\n\n";
	//Test 4: File with 11 scores
	cout << "Test 4: File with 11 scores\n";
	system.setScoreFile("test4.txt");
	system.displayHighScore();
	cout << "Test 4 Passed\n\n";
	//Test 5: Invalid file
	cout << "Test 5: invalid file (The program will exit if passes)\n";
	system.setScoreFile("fake.txt");
	cout << "If you see this, test 5 fails";
}

//Test replay()
void test_replay() {
	System system;
	cout << "Replay funntion testing\n";
	//Test 1: Yes to replay
	cout << "Test 1: Please enter Y or y\n";
	bool choice = system.replay();
	assert(true == choice);
	cout << "Test 1 Passed\n\n";
	//Test 2: No to replay
	cout << "Test 2: Please enter N or n\n";
	choice = system.replay();
	assert(false == choice);
	cout << "Test 2 passed\n\n";
	//Test 3: invalid input
	cout << "Test 3: invalid input, then any valid input\n";
	choice = system.replay();
	cout << "Test 3 passed\n\n";
}

//Test endGame()
//Because endGame() either forces you to restart or end the game,
//Can only test one at a time. Comment out the one you don't want to test.
void test_endGame() {
	cout << "endGame() Testing\n";
	System system;
	//system.endGame(true);
	system.endGame(false);
}

//Test read papers
void test_readPapers() {
	System system;
	int startTime = 25;
	int startIntelligence = 15;
	cout << "readPapers Testing\n";
	system.readTechPapers();
	Player player = system.getPlayer();
	int timeChange = startTime - player.time;
	int intelChange = player.intelligence - startIntelligence;
	//Be sure intelligence is in the right range
	assert(intelChange >= 1);
	assert(intelChange <= 5);
	//Be sure time change is correct
	assert(timeChange = 1);

	cout << "\nStart time: " << startTime << " New time: " << player.time << endl;
	cout << "Start intelligence: " << startIntelligence << " New intelligence: " << player.intelligence << endl;
	cout << "\nIf everything matches, test passes\n";
}

//Test changeSearch
void test_changeSearch() {
	System system;
	int startTime = 25;
	int startMoney = 10.00;
	cout << "changeSearch Testing\n";
	system.searchChange();
	Player player = system.getPlayer();
	int timeChange = startTime - player.time;
	double moneyChange = player.money - startMoney;
	//Be sure intelligence is in the right range
	assert(moneyChange >= 0.25);
	assert(moneyChange <= 3.50);
	//Be sure time change is correct
	assert(timeChange = 1);

	cout << "\nStart time: " << startTime << " New time: " << player.time << endl;
	cout << "Start Money: " << startMoney << " New money: " << player.money << endl;
	cout << "\nIf everything matches, test passes\n";
}

//test addHighScore
void test_addHighScore() {
	System system;
	Highscore testHS;
	testHS.name = "Test";
	testHS.score = 6000;
	cout << "Testing for adding highscores\n";
	cout << "Will add Test 6000 score to various scenarios\n\n";
	//test1: Adding to empty file
	cout << "Test 1: no scores\n";
	system.setScoreFile("addscoreTest1.txt");
	system.addHighScore(testHS.name, testHS.score);
	system.displayHighScore();
	cout << "\nIf list contains exactly one score, Test 6000, Test 1 passes\n\n";
	//Test2: Adding when less than 10 scores.
	cout << "Test 2: Adding when less than 10 scores exist\n\n";
	system.setScoreFile("addscoreTest2.txt");
	system.addHighScore(testHS.name, testHS.score);
	system.displayHighScore();
	cout << "\nIf list contains less than 10 scores and has Test 6000 in correct order, Test 2 passes\n\n";
	//Test 3: adding when already 10 scores
	cout << "Test 3: Adding when there are already 10 scores\n\n";
	system.setScoreFile("addscoreTest3.txt");
	system.addHighScore(testHS.name, testHS.score);
	system.displayHighScore();
	cout << "\nIf list contains 10 items and Test 6000 is in the correct location, Test 3 Passes\n\n";
}