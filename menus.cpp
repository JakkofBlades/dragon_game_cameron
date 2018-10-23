/*
* User name: Cameron Holt
* AU UserID: cwh0023
* Project Name: project1.cpp
* File Name: menus.cpp
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

//Menus class
class Menus
{
public:
	Menus(); //Default constructor
	int menuGame(); //Generates the game's menu.
	int menuMain(); //Generates the main menu.
private:
	int playerAction; //Player chooses an action.
	void checkGameAction(); //Check that an in-game action is valid.
	void checkMainAction(); //Check that a main menu aciton is valid.
};

//Test the main menu function.
void test_menuMain();

//Test the game's menu.
void test_menuGame();

//Main, use for testing this file.
int main() {
test_menuGame();
test_menuMain();
}

//Constructor. Sets playerAction to 0.
Menus::Menus() {
	playerAction = 0;
}

//Displays the main menu,returns player input
int Menus::menuMain() {
	//Main menu
	cout << "\n\t1) Start a new game of Escape Shelby!\n";
	cout << "\t2) View top 10 High Scores\n";
	cout << "\t3) Quit game\n\n";
	cout << "Please choose an option: ";
	//Get input
	cin >> playerAction;
	//Check user's choice.
	checkMainAction();
	return playerAction;

}

//Check user's choice on the main menu.
//If input is not valid, prompt for proper input.
void Menus::checkMainAction() {
	//If the input isn't valid, prompt for proper input. Loop until good input.
	while (cin.fail() || playerAction < 1 || playerAction > 3) {
		cin.clear();
		cin.ignore();
		cout << "\nInput invalid. Please input a menu number, or enter -1 to exit the game.\n";
		cout << "\nPlease choose an action: ";
		cin >> playerAction;
		//Player chooses to quit.
		if (playerAction== -1) {
			exit(1);
		}
	}
}

//Displays the menu, then gets the player's input.
//Returns the player's menu choice.
int Menus::menuGame() {
	//Display the menu
	cout << "\t1) Move forward (takes time, could be risky...)\n";
	cout << "\t2) Read technical papers (boost intelligence, takes time)\n";
	cout << "\t3) Search for loose change (boost money, takes time)\n";
	cout << "\t4) View character\n";
	cout << "\t5) Quit the game\n\n";
	cout << "Please choose an action: ";
	//Get input
	cin >> playerAction;
	//Validate input
	checkGameAction();
	return playerAction;
}

//Check to see if input is valid
//If input is not valid, prompt for proper input.
void Menus::checkGameAction() {
	//If the input isn't valid, prompt for proper input. Loop until good input.
	while (cin.fail() || playerAction < 1 || playerAction > 5) {
		cin.clear();
		cin.ignore();
		cout << "\nInput invalid. Please input a menu number, or enter -1 to exit the game.\n";
		cout << "\nPlease choose an action: ";
		cin >> playerAction;
		//If player chooses quit
		if (playerAction == -1) {
			exit(1);
		}
	}
}

/*************************************TESTING*****************************************/

//Test menu: Main
void test_menuMain() {
	cout << "Menu: Main Test\n";
	cout << "Test 1: Valid input\n";
	cout << "Enter a name followed by entering 1 as your input\n\n";
	Menus menu;
	int action;
	action = menu.menuMain();
	assert(1 == action);
	cout << "Test 2: Invalid input followed by valid input\n";
	cout << "Enter your name followed by entering invalid input, then enter 2\n\n";
	action = menu.menuMain();
	assert(2 == action);
	cout << "Test 3: Invalid input followed by quitting.\n";
	cout << "Enter your name, then Enter invalid input, then -1 to quit\n\n";
	action = menu.menuMain();
}
//Test Menu: Game
void test_menuGame() {
	cout << "Menu: Game Test\n";
	cout << "Test 1: Valid input\n";
	cout << "Enter 1 as input\n\n";
	Menus menu;
	int action;
	action = menu.menuGame();
	assert(1 == action);
	cout << "Test 2: Invalid input followed by valid input\n";
	cout << "Enter invalid input followed by entering 2\n\n";
	action = menu.menuGame();
	assert(2 == action);
	cout << "Test 3: Invalid input followed by quitting\n";
	cout << "Enter invalid input, follwed by -1 to quit\n\n";
	action = menu.menuGame();
}