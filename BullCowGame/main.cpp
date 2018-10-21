/*
Bull Cow Game. A simple guess the word game with isograms.
Copyright Sloan Gwaltney
This is the game view logic. 
It consums the engine/model logic in order to produce views for the user.
*/
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string; // to make Unreal friendly
using int32 = int; // to make Unreal friendly
void PrintIntro();
FText GetValidGuess();
void PrintBullsAndCows(FBullCowCount BullCowCount);
void PrintGameSummary();
void PlayGame();
bool AskToPlayAgain(bool DidPlayerEnterInvalidInput);

FBullCowGame BCGame; // Global because it is actualy needed everywhere

int main()
{
	do 
	{
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain(false) == true);
	return 0;
}

void PrintIntro()
{
	BCGame.Reset();
	std::cout << R"(

______       _ _                   _   _____                 _ 
| ___ \     | | |                 | | /  __ \               | |
| |_/ /_   _| | |   __ _ _ __   __| | | /  \/ _____      __ | |
| ___ \ | | | | |  / _` | '_ \ / _` | | |    / _ \ \ /\ / / | |
| |_/ / |_| | | | | (_| | | | | (_| | | \__/\ (_) \ V  V /  |_|
\____/ \__,_|_|_|  \__,_|_| |_|\__,_|  \____/\___/ \_/\_/   (_)
                                                               
                                                               
 )" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I am thinking of?" << std::endl;
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	do {
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
		PrintBullsAndCows(BullCowCount);
		BCGame.SetGameStatus(BullCowCount);
		std::cout << std::endl;
	} while (BCGame.GetGameStatus() == EGameStatus::Ongoing);
	PrintGameSummary();
	std::cout << std::endl;
	return;
}


FText GetValidGuess()
{
	std::cout << "Try " << BCGame.GetCurrentTry() << " of "; 
	std::cout << BCGame.GetMaxTries() << ": Enter your guess ";
	FText Guess = "";
	getline(std::cin, Guess);
	EWordStatus GuessStatus = BCGame.CheckValidGuess(Guess);

	switch (GuessStatus)
	{
	case EWordStatus::Invalid_Length:
		std::cout << "Please Enter a " << BCGame.GetHiddenWordLength() <<  " letter response.";
		std::cout << std::endl;
		std::cout << std::endl;
		return GetValidGuess();
	case EWordStatus::Not_Isogram:
		std::cout << "Please try again with no repeating letters.";
		std::cout << std::endl;
		std::cout << std::endl;
		return GetValidGuess();
	case EWordStatus::Not_Lowercase:
		std::cout << "All answeres should be in lowercase please try again.";
		std::cout << std::endl;
		std::cout << std::endl;
		return GetValidGuess();
	case EWordStatus::Space:
		std::cout << "Please try again without a space";
		std::cout << std::endl;
		std::cout << std::endl;
		return GetValidGuess();
	default:
		return Guess;
	}
}

void PrintBullsAndCows(FBullCowCount BullCowCount)
{
	std::cout << "Bulls (letters in the right place) = " << BullCowCount.Bulls << std::endl;
	std::cout << "Cows (letters in the worng place) = " << BullCowCount.Cows << std::endl;
	return;
}

bool AskToPlayAgain(bool DidPlayerEnterInvalidInput)
{
	if (DidPlayerEnterInvalidInput)
	{
		std::cout << std::endl;
		std::cout << "Please enter a vaild option." << std::endl;
	}

	std::cout << "Would you like to play again? Please enter Yes or No: ";
	FText Response = "";
	getline(std::cin, Response);
	std::cout << std::endl;

	if (Response == "Yes" || Response == "yes")
	{
		return true;
	}

	else if (Response == "No" || Response == "no")
	{
		return false;
	}

	return AskToPlayAgain(true);
}

void PrintGameSummary()
{
	switch (BCGame.GetGameStatus())
	{
	case EGameStatus::Player_Lost:
		std::cout << R"(
______      _   _              _                _    
| ___ \    | | | |            | |              | |   
| |_/ / ___| |_| |_ ___ _ __  | |    _   _  ___| | __
| ___ \/ _ \ __| __/ _ \ '__| | |   | | | |/ __| |/ /
| |_/ /  __/ |_| ||  __/ |    | |___| |_| | (__|   < 
\____/ \___|\__|\__\___|_|    \_____/\__,_|\___|_|\_\
                                                     
                                                     
 _   _           _     _____ _                  _    
| \ | |         | |   |_   _(_)                | |   
|  \| | _____  _| |_    | |  _ _ __ ___   ___  | |   
| . ` |/ _ \ \/ / __|   | | | | '_ ` _ \ / _ \ | |   
| |\  |  __/>  <| |_    | | | | | | | | |  __/ |_|   
\_| \_/\___/_/\_\\__|   \_/ |_|_| |_| |_|\___| (_)   
                                                     
                                                     
 )" << std::endl;
		break;
	case EGameStatus::Player_Won:
		std::cout << R"(
__   __            _    _               _ 
\ \ / /           | |  | |             | |
 \ V /___  _   _  | |  | | ___  _ __   | |
  \ // _ \| | | | | |/\| |/ _ \| '_ \  | |
  | | (_) | |_| | \  /\  / (_) | | | | |_|
  \_/\___/ \__,_|  \/  \/ \___/|_| |_| (_)
                                          
                                          
 )" << std::endl;
		break;
	default:
		break;
	}
	return;
}