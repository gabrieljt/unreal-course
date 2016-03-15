#pragma once

#include <iostream>
#include <locale>
#include <map>
#include <set>
#include <string>
#include <unordered_set>

using FString = std::string;
using int32 = int;

struct EBullsAndCowsGuess
{
public:
	EBullsAndCowsGuess(const int32 Bulls, const int32 Cows, const FString Guess)
		: Bulls(Bulls)
		, Cows(Cows)
		, Guess(Guess)
	{
	}

	const FString Guess;
	const int32 Bulls;
	const int32 Cows;
};

enum class EGuessStatus
{
	OK,
	Wrong_Length,
	Not_Isogram
};

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
	FString				ReadGuessInput() const;
	EGuessStatus		ProcessInput(const FString) const;
	EBullsAndCowsGuess	ProcessBullsAndCowsGuess(const FString);
	void				SaveBullsAndCowsGuess(const FString, const EBullsAndCowsGuess);
	void				WriteBullsAndCowsGuess(const EBullsAndCowsGuess) const;
	void				WriteGuessedWords() const;
	void				WriteGuessedLetters() const;
	bool				GuessedRight(const FString) const;
	void				WriteResult() const;
	FString				ToLower(const FString) const;
	bool				IsIsogram(const FString) const;
	int32				GetMyIsogramWordLength() const;

	const FString							MyIsogramWord;
	const int32								MyMaximumTries;
	int32									MyCurrentTry;
	bool									bMyGuessedRight;
	std::set<char>							MyGuessedLetters;
	std::map<FString, EBullsAndCowsGuess>	MyGuessedWords;
	static const FString					MyIsogramWords[];
};
