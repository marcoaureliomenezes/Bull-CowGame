/*	 The game logic ( no view code or direct user interaction).
	The game is a simple guess the word based on Mastermind
*/

#pragma once
#include <string>

// To make syntax in Unreal friendly
using FString = std::string;
using int32 = int;

// all values initialised to zero
struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus 
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public:

	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	bool IsGameWon() const;
	int32 GetHiddenWordLength() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();

	FBullCowCount SubmitValidGuess(FString);

private:
	// See constructor for initialisation
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsAnIsogram(FString) const;
	bool IsLowerCase(FString) const;
};
