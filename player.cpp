/*
* User name: Cameron Holt
* AU UserID: cwh0023
* Project Name: project1.cpp
* File Name: Player.cpp
* Compile in jGRASP or g++ compiler.
*/

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <string>
#include <ctime>
#include <iomanip> //std:setw
using namespace std;

class Player {
public:
	Player(); //Constructor for the class
	Player(string playName); //Constructor with a player name.
	Player(string playName, int intelIn, int timeIn, double moneyIn); //Constructor with input for all stats.
	string playerName; //Name of player
	int intelligence; //intelligence of a player's character
	int time; //Time left
	double money; //Money player currently has.
	int steps;
	void currentStats(); //Shows player their current stats.
private:
	//Constant values
	static const int DEFAULT_INTELLEIGENCE = 20; //Range should be 10-30
	static const int DEFAULT_TIME = 30; //Range should be 10-30
	static constexpr double DEFAULT_MONEY = 13.50; //Range should be 5-20
};

//Test constructors
void test_Constructors();

//Test currentStats
void test_currentStats();

//Main, used to testing.
//Comment out to prevent issues.
//int main() {
//test_Constructors();
//test_currentStats();
//}

//Constructor
//Sets stats to default;
Player::Player() 
{
	playerName = "";
	intelligence = DEFAULT_INTELLEIGENCE;
	time = DEFAULT_TIME;
	money = DEFAULT_MONEY;
	steps = 20;
}

//Constructor 2
//Player entered their name, other values default.
Player::Player(string playName)
{
	playerName = playName;
	intelligence = DEFAULT_INTELLEIGENCE;
	time = DEFAULT_TIME;
	money = DEFAULT_MONEY;
	steps = 20;
}

Player::Player(string playName, int intelIn, int timeIn, double moneyIn)
{
	playerName = playName;
	intelligence = intelIn;
	time = timeIn;
	money = moneyIn;
	steps = 20;
}

//
void Player::currentStats() {
	cout << endl << playerName << "'s Stats:\n";
	cout << "intelligence: " << intelligence << endl;
	cout << "time: " << time << endl;
	cout << "money: " << fixed << setprecision(2) << money << "\n\n";
}

//Add test files when more stuff is working!

/**************************Test*************************************/

//Test constructors
void test_Constructors() {
	//Test variables
	int defaultTime = 30;			//Default time is 30
	int defaultIntel = 20;			//Default intelligence is 15
	double defaultMoney = 13.50;	//Default money is 13.50
									//Test values entered by tester
	string playerNameTestVal;
	int timeTestVal;
	int intelTestVal;
	double moneyTestVal;
	//Test 1
	cout << "Constructor Tests\n";
	cout << "Test 1: Default constructor\n";
	Player playerTestVal;
	//Assert that the variables are true.
	assert("" == playerTestVal.playerName);
	assert(defaultTime == playerTestVal.time);
	assert(defaultIntel == playerTestVal.intelligence);
	assert(defaultMoney == playerTestVal.money);
	cout << "\tTest 1 passed\n";
	
	//Test 2
	cout << "Test 2: User inputs a screen name\n";
	cout << "\tEnter your name: ";
	cin >> playerNameTestVal;
	playerTestVal = Player(playerNameTestVal);
	//Assert that the variables are true.
	assert(playerNameTestVal == playerTestVal.playerName);
	assert(defaultTime == playerTestVal.time);
	assert(defaultIntel == playerTestVal.intelligence);
	assert(defaultMoney == playerTestVal.money);
	cout << "\tTest 2 Passed\n";
	
	//Test 3
	cout << "Test 3: User has custom stats\n";
	cout << "\tEnter your name: ";
	cin >> playerNameTestVal;
	cout << "\tEnter the time (10 - 30): ";
	cin >> timeTestVal;
	cout << "\tEnter the intelligence (10 - 30): ";
	cin >> intelTestVal;
	cout << "\tEnter the money (5 - 20): ";
	cin >> moneyTestVal;
	playerTestVal = Player(playerNameTestVal, timeTestVal, intelTestVal, moneyTestVal);
	//Check values
	assert(playerNameTestVal == playerTestVal.playerName);
	assert(timeTestVal == playerTestVal.time);
	assert(intelTestVal == playerTestVal.intelligence);
	assert(moneyTestVal == playerTestVal.money);
	cout << "\tTest 3 passed\n";
}

//Test currentStats
//Constructor tests passing means that we don't need to test them again.
void test_currentStats() {
	//Variables
	string nameTest;
	int timeTest;
	int intelTest;
	double moneyTest;
	Player playerTest;
	//Test 1
	cout << "currentStats test\n";
	cout << "Test 1: Show player their default stats\n";
	//Display default stats
	playerTest.currentStats();
	cout << "\nTest 1 Passed\n";
	
	//Test 2
	cout << "Test 2: Display custom name, other values default\n";
	cout << "\tEnter your name: ";
	cin >> nameTest;
	playerTest = Player(nameTest);
	//Display custom name and default stats
	playerTest.currentStats();
	cout << "\nTest 2 Passed\n";
	
	//Test 3
	cout << "Test 3: User has a custom game.\n";
	cout << "\tEnter your name: ";
	cin >> nameTest;
	cout << "\tEnter the time: ";
	cin >> timeTest;
	cout << "\tEnter the intelligence: ";
	cin >> intelTest;
	cout << "\tEnter the money: ";
	cin >> moneyTest;
	playerTest = Player(nameTest, timeTest, intelTest, moneyTest);
	//Display all entered input
	playerTest.currentStats();
	cout << "\nTest 3 Passed\n";

}