#pragma once

#include "pch.h"
#include "FBullCowGame.h"
#include <map>
#include <iostream>

// To make syntax in Unreal friendly
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); }	// Default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

/*	The function GetMaxTries() calcules the maximum of tries the player has.
	This number of tries can change according with the size of the Hidden Word
*/
int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4},{4,7},{5,10},{6,16},{7,20}};
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

/*	The function Reset initialize the game with default configurations for
	some private attributes and determines the Hidden Word.
*/
void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet";	// this Must be an isogram
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}


/*	The CheckGuessValidity() function performs validation on
	the inputs provided by the player. It checks if the input 
	is an isogram, has the correct number of characters and
	the characters are lowercase.
*/
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (! IsAnIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;	
	}
	else if (! IsLowerCase(Guess))
	{

		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else 
	{
		return EGuessStatus::OK;
	}
}
/* The SubmitValidGuess() function submit the input entered
	by the player. It increments the number of tries and
	compare the guess (input) with the Hidden Word. At this
	way the function calcules the number of bulls and cows.
	If the number of bulls is equals the hidden Word length
	the boolean attribute BGameIsWon is set to true.
	*/
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();

	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) {
					BullCowCount.Bulls++;
				
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}		
	}		
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

/* The IsAnIsogram() function returns false if the
	input provides by the user has repeated letters
	and true if doesn't. It is a condition for 
	validation of the submitted guess.
	*/
bool FBullCowGame::IsAnIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false;
		} else 
		{
			LetterSeen[Letter] = true;
		}
	}

	return true;
}
/* The IsLowerCase() Function returns false if the parameter
	word contains any Capital letter and true if it doesn't
	contains It is a condition for validation of the submitted
	guess.
	*/
bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}