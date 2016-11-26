// you can define the function easily with the quick action.
// enum returns value. Prevents OK = 1 and Not_isogram = 2. See enum here.
// enum values can only be used ones in the project unless you make a enum class. So you can use OK in multiple enums for example

#pragma once
#include <string>

// to make syntax Unreal Engine friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};


class FBullCowGame {
public:
	FBullCowGame(); // constructer
	
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLenght() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	
	void Reset(); // TODO make a more rich return value.

	// coiunts bulls & cows, and increases try # assuming valid guess
	FBullCowCount SubmitValidGuess(FString);

private:
	//see construction for initialisation
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;
	
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	
};