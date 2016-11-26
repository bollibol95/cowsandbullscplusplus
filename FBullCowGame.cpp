//functions are called methods here.
//constructor will overrule the privates.
#pragma once
#include "FBullCowGame.h"
#include <map>

t
#include <ctime>

#define TMap std::map // to make syntax Unreal friendly

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLenght() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ { 3, 4 }, { 4, 7 }, {5, 10},{ 6, 16 },{ 7, 20 }, {8, 24}, {9, 28} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
} 

void FBullCowGame::Reset() {
	srand(time(0));
	const FString WORD_LIST[25] = {"algorithm", "planet", "number", "tip", "orgasmic", "isogram", "roaming", "mirages", "savior", "mirages", "armor", "jams", "aims", "girl", "age", "ear", "ego", "army", "worm", "raw", "grows", "magic", "orgasm", "egoism", "gamer"}; // must be an isogram
	MyHiddenWord = WORD_LIST[rand() % 25];
	
	bGameIsWon = false;
	MyCurrentTry = 1;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram; 
	}
	else if (!IsLowercase(Guess)) { 
		return EGuessStatus::Not_Lowercase; 
	}
	else if (Guess.length() != GetHiddenWordLenght()) {
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::OK;
	}
}

// receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	// increment the turn number
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	for (int32 MHWChat = 0; MHWChat < WordLength; MHWChat++){
		// compare letters against the guess.
		for (int32 GChar = 0; GChar < WordLength; GChar++){
			// if they match then
			if(Guess[GChar] == MyHiddenWord[MHWChat]){
				// increment bulls if they're in the same place
				if (MHWChat == GChar) {
					BullCowCount.Bulls++; // increment bulls
				}
				else {
					BullCowCount.Cows++; // increment cows
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else { 
		bGameIsWon = false; 
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	// setup our map
	TMap<char, bool> LetterSeen; // setup our map
	for (auto Letter : Word)	//for all letter of the word
	{
		Letter = tolower(Letter); // handle mixed cases
		if (LetterSeen[Letter]) { // if the letter is in the map 
			return false; // we do not have an isogram
		}
		else {
			LetterSeen[Letter] = true;
		}
			
				// we do NOT have an isogram
			// otherwise
				// add the letter to the map as seen
	}
	return true; // for example in the cases where /0 is entered.
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)	//for all letter of the word
	{
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}


