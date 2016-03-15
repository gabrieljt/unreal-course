#pragma once

#include <iostream>
#include <locale>
#include <map>
#include <set>
#include <string>
#include <unordered_set>

using FString = std::string;
using int32 = int;

struct EBullsAndCows
{
public:
	EBullsAndCows(const int32 Bulls, const int32 Cows)
		: Bulls(Bulls)
		, Cows(Cows)
	{
	}

	const int32 Bulls;
	const int32 Cows;
};

enum class EGuessStatus
{
	OK,
	WrongLength,
	NotIsogram,
	AlreadyGuessed,
};

class FBullCowGame
{
public:
	FBullCowGame(const FString, const int32);
	~FBullCowGame();

	static FString		GetIsogramWord();
	void				PlayGame();
	bool				HasGuessedRight() const;
	bool				AskToPlayAgain() const;

private:
	void				WriteIntro() const;
	void				RunGuessLoop();
	FString				ReadGuessInput() const;
	EGuessStatus		ProcessInput(const FString) const;
	EBullsAndCows		ProcessBullsAndCows(const FString);
	void				SaveBullsAndCows(const FString, const EBullsAndCows);
	void				WriteBullsAndCows(const FString, const EBullsAndCows) const;
	void				WriteGuessedWords() const;
	void				WriteGuessedLetters() const;
	bool				GuessedRight(const int32) const;
	void				WriteResult() const;
	FString				ToLower(const FString) const;
	bool				IsIsogram(const FString) const;
	bool				WasAlreadyGuessed(const FString) const;
	int32				GetMyIsogramWordLength() const;

	const FString							MyIsogramWord;
	const int32								MyMaximumTries;
	int32									MyCurrentTry;
	bool									bMyGuessedRight;
	std::set<char>							MyGuessedLetters;
	std::map <FString, EBullsAndCows>	MyGuessedWords;
	static const FString					MyIsogramWords[];
};
