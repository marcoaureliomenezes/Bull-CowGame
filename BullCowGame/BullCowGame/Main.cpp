/* This is the console executable, that makes use of BullCow class 
This acts as the view in a MVC pattern. and is responsible for all 
user interations. For game logic see the FBullCowGame class
*/

#pragma once
#include "pch.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"
#include <fstream>
using namespace std;

// To make syntax in Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void printIntroduction();
void playGame();
bool askToPlayAgain();
FText GetValidGuess();
void PrintGameSummary();
void getHiddenWord();

FBullCowGame BCGame; // Instantiate a new game

/* The main fucntion is where the program begins to be executed.
	By concepts about abstraction and encapsulation it contains
	the following operation. Do the boolean variable bPlayAgain as
	false, and repeats the sequence PrintIntroduction() and playGame() 
	until the player changes bPlayAgain by function askToPlayAgain */
int main()
{
	getHiddenWord();
	bool bPlayAgain = false;
	do {
		printIntroduction();
		playGame();
		bPlayAgain = askToPlayAgain();

	} while (bPlayAgain);

	return 0;
}



/*	The printIntroduction() function prints in the console a
	initial message to the player.
*/
void printIntroduction(void) { 
	
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of? \n";
	std::cout << std::endl;
	return;
}

/* The playGame() function is where the game is really played.
	It resets the game, get the maximum of tries and while the 
	game is not won or the number of tries is extrapolated, the
	function call a valid guess as input
	*/
void playGame()
{
	BCGame.Reset();
	int MaxTries = BCGame.GetMaxTries();

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)  
	{
		FText Guess = GetValidGuess();
		
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}

/*	The askToPlayAgain() boolean function asks the
	player if he wants play again and returns true
	if response is "y" or "Y" and false if not. 
*/
bool askToPlayAgain()
{
	std::cout << "Do you wanna play again? (y/n)";
	FText response = "";
	std::getline(std::cin, response);

	return (response[0] == 'y') || (response[0] == 'Y');
	std::cout << std::endl;
	return false;
}

/*	The GetValidGuess() function asks the player to enter with a guess,
	check the validity of that guess using the function checkGuessValidity()
	from the class FBullCowGame. If OK it returns the guess.*/
FText GetValidGuess(void) 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess! ";
		std::getline(std::cin, Guess);

		EGuessStatus Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter with a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Enter with a word without repeating letters. \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters. \n\n";
			break;
		default:
			return Guess;
			break;
		}
	} while (Status != EGuessStatus::OK);	
}

/*	The PrintGameSummary() function says the the player
	if he won or lost the game
*/
void PrintGameSummary()
{
	if (BCGame.IsGameWon() == true)
	{
		std::cout << "Congratulations, you won the game.\n";
	}
	else
	{
		std::cout << "Try again, you lose.\n";
	}
	return;
}

void getHiddenWord()
{
	FString line;
	ifstream myfile("C:\\users\\marco\\source\\repos\\BuildingScapeDadaia\\BuildingScapeDadaia\\Source\\BuildingScapeDadaia\\lista_Isogramas.txt"); // ifstream = padrão ios:in
	if (myfile.is_open())
	{
		while (!myfile.eof()) //enquanto end of file for false continua
		{
			getline(myfile, line); // como foi aberto em modo texto(padrão)
								   //e não binário(ios::bin) pega cada linha
			cout << line << std::endl;
		}
		myfile.close();
	}
	else std::cout << "Unable to open file";
}