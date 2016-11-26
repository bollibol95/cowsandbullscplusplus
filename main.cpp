/* /n is a new line. / stands for special symbol is coming. N means new line. namespace std prevends us from always having to put std before say std::cout. 
ones the program starts, it defines the constant expression and it can not change after that. 
<< is kinda like + in c# to add more lines. Although it is more like a line you pull out of the programm. >> is information you put in.  
sudo code programming helps you to know what you need to do where. Just command it out and think later how you will do it.
the getline() will automaticly read through spaces and it will discard the input stream once it reaches the new-line character. So instead of cin. You put in getline(cin, varuablename)
for is when you know how much is should repeat. While is when you don't know the limit. for(initialization; condition; increase) statement;
<> in a include means it is a system file, so predefined functions etc. "" means it is a created file! 
You can use TODO as a comment so you know what you need to do. You can easily check what you need to do in view>Task list
fstring is a changable object, ftext is used for user output. Both are used for UE just like int32. Replace it of the stardard VS style.
*/

/*	This is the console executabnle, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all user interaction. For game logic see the FBullCowGame class
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal Engine friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game, which will be re-used across plays

//entry point for our application
int main() {
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);
	
	return 0;
}

void PrintIntro() {
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	return;
}

//plays a single game to completion
void PlayGame() {
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLenght() << " letter isogram I'm thinking of?\n" << std::endl;
	
	// loop asking for guesses while the game is NOT won.
	// and there are still tries remaining.
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess(); 

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls << ". Cows = " << BullCowCount.Cows << std::endl << std::endl;
	}
	PrintGameSummary();
	return;
}



// loop continually untill the user gives a valid guess
FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		
		//get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		int32 GetMaxTries = BCGame.GetMaxTries();
		
		std::cout << "Try " << CurrentTry << " of " << GetMaxTries << ". Enter your guess: ";
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLenght() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters\n\n";
			break;
		default:
			// assume guess valid
			break;
		}
		
	} while(Status != EGuessStatus::OK); // keep looping until we get no errors.
	return Guess;
	
}

bool AskToPlayAgain()
{
	FText Response = "";
	
	std::cout << "Do you want to play again with the same hidden word? (y/n)";
	getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "Well Done! - You win!\n";
	}
	else {
		std::cout << "Better luck next time\n";
	}
}
