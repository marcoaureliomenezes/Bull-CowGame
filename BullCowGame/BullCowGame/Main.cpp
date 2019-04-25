#include "pch.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"

void printIntroduction(void);
void playGame();
bool askToPlayAgain();
std::string getGuess(void);

FBullCowGame BCGame; // instantiate a new game

int main()
{

	bool bPlayAgain = false;
	do {
		printIntroduction();
		playGame();
		bPlayAgain = askToPlayAgain();

	} while (bPlayAgain);

	return 0;
}

void printIntroduction(void) {
	// Introduce the game 
	constexpr int WORLD_LENGTH = 5;
	std::cout << "Welcome to Bulls and Cows, a word fun game! \n";
	std::cout << "Can you guess " << WORLD_LENGTH;
	std::cout << " letter isogram I'm thinking of? \n";
	std::cout << std::endl;
	return;
}

void playGame()
{
	BCGame.Reset();
	int MaxTries = BCGame.GetMaxTries();

	// loop for the number of turns asking for guesses
	// TODO Change from FOR to WHIE loop once we are validating tries 
	for (int i = 0; i < MaxTries; i++) {
		std::cout << "Your guess was " << getGuess();  // TODO Make a valid input

		// Submit a valid guess to the game
		// print number of bulls and cows
		std::cout << std::endl;
	}
	// TODO Summary game
}

bool askToPlayAgain()
{
	std::cout << "Do you wanna play again? (y/n)";
	std::string response = "";
	std::getline(std::cin, response);

	return (response[0] == 'y') || (response[0] == 'Y');
	std::cout << std::endl;
	return false;
}

std::string getGuess(void) {
	// Get a guess from a player
	int CurrentTry = BCGame.GetCurrentTry();

	std::cout << "Try " << CurrentTry << ". Enter your guess";
	std::string Guess = "";
	std::getline(std::cin, Guess);
	return Guess;
}