#pragma once

#include <iostream>
#include <locale>
#include <map>
#include <set>
#include <string>
#include <unordered_set>

using FString = std::string;
using int32 = int;

struct EBullsAndCowsCount;

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
	bool				CheckBullsAndCowsCount(const FString);
	void				WriteBullsAndCowsCount(const FString);
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
