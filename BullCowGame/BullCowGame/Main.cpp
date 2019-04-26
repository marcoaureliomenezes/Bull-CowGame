/* This is the console executable, that makes use of BullCow class 
This acts as the view in a MVC pattern. and is responsible for all 
user interations. For game logic see the FBullCowGame class
*/

#include "pch.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void printIntroduction(void);
void playGame();
bool askToPlayAgain();
FText GetValidGuess(void);

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
	std::cout << "\n\nWelcome to Bulls and Cows, a word fun game! \n";
	std::cout << "Can you guess " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of? \n";
	std::cout << std::endl;
	return;
}

void playGame()
{
	BCGame.Reset();
	int MaxTries = BCGame.GetMaxTries();

	// loop  asking for guesses while the game is NOT won
	// and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)  {
		FText Guess = GetValidGuess();
		
		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;  // TODO Make a valid input
		std::cout << " Cows = " << BullCowCount.Cows << "\n\n";

	}
	// TODO Summary game
}

bool askToPlayAgain()
{
	std::cout << "Do you wanna play again? (y/n)";
	FText response = "";
	std::getline(std::cin, response);

	return (response[0] == 'y') || (response[0] == 'Y');
	std::cout << std::endl;
	return false;
}

// loop continually until the user gives a valid guess
FText GetValidGuess(void) 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		EGuessStatus Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter with a " << BCGame.GetHiddenWordLength() << " letter word. \n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Enter with a word without repeating letters. \n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters. \n";
			break;
		default:
			return Guess;
			break;
		}
		
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // keep looping until we get a valid input
	
}