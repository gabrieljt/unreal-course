#pragma once

#include <iostream>
#include <locale>
#include <map>
#include <set>
#include <string>
#include <unordered_set>

using FString = std::string;
using int32 = int;

struct EBullsAndCowsCount
{
public:
	EBullsAndCowsCount();

	EBullsAndCowsCount(const int32, const int32);

	int32 Bulls;
	int32 Cows;
};

enum EWordStatus;

class FBullCowGame
{
public:
	FBullCowGame(const FString, const int32);
	~FBullCowGame();

	static FString		GetIsogramWord();
	void				RunGame();
	bool				HasGuessedRight() const;
	bool				AskToPlayAgain() const;

private:
	void				WriteIntro() const;
	void				RunGuessLoop();
	FString				ReadValidGuessInput() const;
	bool				IsValidGuessInput(const FString) const;
	bool				CheckBullsAndCowsCount(const FString, EBullsAndCowsCount&);
	void				WriteBullsAndCowsCount(const FString, const EBullsAndCowsCount) const;
	void				WriteGuessedWords() const;
	void				WriteGuessedLetters() const;
	void				WriteResult() const;
	FString				ToLower(const FString) const;
	bool				IsIsogram(const FString) const;
	int32				GetMyGuessWordLength() const;

	const FString							MyGuess;
	const int32								MyMaximumTries;
	int32									MyCurrentTry;
	bool									bMyGuessedRight;
	std::set<char>							MyGuessedLetters;
	std::map<FString, EBullsAndCowsCount>	MyGuessedWords;
	static const FString					MyIsogramWords[];
};
