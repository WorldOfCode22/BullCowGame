#pragma once
#include <string>
using FString = std::string; // to make Unreal friendly
using int32 = int; // to make Unreal friendly

enum class EWordStatus
{
	Ok,
	Not_Isogram,
	Space,
	Invalid_Length,
	Not_Lowercase
};

enum class EGameStatus
{
	Ongoing,
	Player_Won,
	Player_Lost
};

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

class FBullCowGame
{
public:
	FBullCowGame();
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	EGameStatus GetGameStatus() const;
	EWordStatus CheckValidGuess(FString) const;
	FBullCowCount SubmitGuess(FString);
	void SetGameStatus(FBullCowCount);
	void Reset();
private:
	int32 MyCurrentTry;
	EGameStatus MyGameStatus;
	FString MyHiddenWord;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	bool IsSpace(FString) const;
	void CreateHiddenWord();
};