#pragma once

#include <string>

class FBullCowGame {
public:

	FBullCowGame(); // constructor

	int GetMaxTries() const;
	int GetCurrentTry() const;
	bool IsGameWon() const;

	void Reset();

	bool CheckGuessValidity(std::string); // TODO Make a more rich return validation

	// Provide a method for counting Bulls & cows, and increasing turn #
private:
	int MyCurrentTry;
	int MyMaxTries;
	bool IsIsogram;
};