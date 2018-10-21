/*
Bull Cow Game. A simple guess the word game with isograms.
Copyright Sloan Gwaltney
This is the game engine logic that holds all the non view specific logic of the game.
*/
#include "FBullCowGame.h"
#include <map>
#include <time.h>
#define TMap std::map // to make Unreal friendly

using FString = std::string; // to make Unreal friendly
using int32 = int; // to make Unreal friendly

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32>HiddenWordToTries{ {3,6}, {4,9}, {5,12}, {6,18}, {7,22} };
	return HiddenWordToTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	MyCurrentTry = 1;
	MyGameStatus = EGameStatus::Ongoing;
	CreateHiddenWord();
	return;
}

FBullCowCount FBullCowGame::SubmitGuess(FString Guess) // returns number of bull and cows
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 i = 0; i < HiddenWordLength; i++) 
	{
		if (Guess[i] == MyHiddenWord[i])
		{
			BullCowCount.Bulls++;
		}
		for (int32 j = 0; j < HiddenWordLength; j++)
		{
			if (Guess[i] == MyHiddenWord[j] && i != j)
			{
				BullCowCount.Cows++;
			}
		}
	}
	return BullCowCount;
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

EGameStatus FBullCowGame::GetGameStatus() const
{
	return MyGameStatus;
}

void FBullCowGame::SetGameStatus(FBullCowCount BullCowCount)
{
	if (BullCowCount.Bulls == GetHiddenWordLength())
	{
		MyGameStatus = EGameStatus::Player_Won;
	}
	else if (GetCurrentTry() <= GetMaxTries())
	{
		MyGameStatus = EGameStatus::Ongoing;
	}
	else 
	{
		MyGameStatus = EGameStatus::Player_Lost;
	}

	return;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) return true;
	TMap<char, bool> LettersSeen;
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LettersSeen[Letter]) return false;
		else LettersSeen[Letter] = true;
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	for (auto Letter : Guess)
	{
		if (!islower(Letter)) return false;
	}
	return true;
}

bool FBullCowGame::IsSpace(FString Word) const
{
	for (auto Letter : Word)
	{
		if (isspace(Letter)) return true;
	}
	return false;
}

void FBullCowGame::CreateHiddenWord()
{
	FString isograms[23] = 
	{
	"raw", "mix", "gym", "pig", "ark",
	"gash", "fair", "grow", "worm", "scar",
	"major", "scram", "grits", "dogma", "among",
	"orgasm", "cigars", "disarm", "mirage", "radios",
	"isogram", "margins", "mohairs"
	};
	srand(time(NULL));

	MyHiddenWord = isograms[rand() % 22];
}

EWordStatus FBullCowGame::CheckValidGuess(FString Guess) const
{
	if (Guess.length() != GetHiddenWordLength()) return EWordStatus::Invalid_Length;
	if (IsSpace(Guess)) return EWordStatus::Space;
	if (!IsLowercase(Guess)) return EWordStatus::Not_Lowercase;
	if (!IsIsogram(Guess)) return EWordStatus::Not_Isogram;
	return EWordStatus::Ok;
}
