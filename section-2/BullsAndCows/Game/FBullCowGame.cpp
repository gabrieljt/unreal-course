#include "FBullCowGame.h"

FBullCowGame::FBullCowGame(const FString Guess, const int32 MaximumTries)
	: MyIsogramWord(ToLower(Guess))
	, MyMaximumTries(MaximumTries)
	, MyCurrentTry(0)
	, bMyGuessedRight(false)
	, MyGuessedLetters()
	, MyGuessedWords()
{
}

FBullCowGame::~FBullCowGame()
{
}

FString FBullCowGame::GetIsogramWord()
{
	const int32 Index = std::rand() % 3;
	return MyIsogramWords[Index];
}

const FString FBullCowGame::MyIsogramWords[] = { "play", "plot", "puny" };

void FBullCowGame::PlayGame()
{
	WriteIntro();
	RunGuessLoop();
	WriteResult();
	return;
}

bool FBullCowGame::HasGuessedRight() const
{
	return bMyGuessedRight;
}

void FBullCowGame::WriteIntro() const
{
	std::cout << "Welcome to Bulls and Cows!" << std::endl;
	std::cout << "Can you guess the " << GetMyIsogramWordLength() << " letter isogram I'm thinking of?" << std::endl << std::endl;;
	return;
}

void FBullCowGame::RunGuessLoop()
{
	do
	{
		std::cout << "Try " << MyCurrentTry + 1 << " of " << MyMaximumTries << ". Type your guess: ";
		FString Guess = ToLower(ReadGuessInput());
		EGuessStatus GuessStatus = ProcessInput(Guess);
		switch (GuessStatus)
		{
		case EGuessStatus::WrongLength:
			std::cout << "Your guess must have " << GetMyIsogramWordLength() << " letters." << std::endl;
			break;

		case EGuessStatus::NotIsogram:
			std::cout << "Your guess must be an isogram (no repeated letters)." << std::endl;
			break;

		case EGuessStatus::AlreadyGuessed:
			std::cout << "The word '" << Guess << "' was already guessed!" << std::endl;
			break;

		case EGuessStatus::OK:
			++MyCurrentTry;
			EBullsAndCows BullsAndCows = ProcessBullsAndCows(Guess);
			SaveBullsAndCows(Guess, BullsAndCows);
			std::cout << std::endl;
			WriteBullsAndCows(Guess, BullsAndCows);
			std::cout << std::endl;
			WriteGuessedLetters();
			std::cout << std::endl;
			WriteGuessedWords();
			std::cout << std::endl;
			bMyGuessedRight = GuessedRight(BullsAndCows.Bulls);
			break;
		}
	} while (MyCurrentTry < MyMaximumTries && !bMyGuessedRight);

	return;
}

FString FBullCowGame::ReadGuessInput() const
{
	FString Guess;
	std::getline(std::cin, Guess);
	return Guess;
}

EGuessStatus FBullCowGame::ProcessInput(const FString Word) const
{
	if (Word.length() != GetMyIsogramWordLength())
	{
		return EGuessStatus::WrongLength;
	}
	else if (!IsIsogram(Word))
	{
		return EGuessStatus::NotIsogram;
	}
	else if (WasAlreadyGuessed(Word))
	{
		return EGuessStatus::AlreadyGuessed;
	}

	return  EGuessStatus::OK;
}

EBullsAndCows FBullCowGame::ProcessBullsAndCows(const FString Guess)
{
	int32 Bulls = 0, Cows = 0;

	for (int32 i = 0; i < GetMyIsogramWordLength(); ++i)
	{
		MyGuessedLetters.insert(Guess[i]);
		for (int32 j = 0; j < GetMyIsogramWordLength(); ++j)
		{
			if (Guess[i] == MyIsogramWord[j])
			{
				i == j ? ++Bulls : ++Cows;
			}
		}
	}

	return EBullsAndCows(Bulls, Cows);
}

void FBullCowGame::SaveBullsAndCows(const FString Guess, const EBullsAndCows BullsAndCows)
{
	MyGuessedWords.insert(std::pair<FString, EBullsAndCows>(Guess, BullsAndCows));
	return;
}

void FBullCowGame::WriteBullsAndCows(const FString Guess, const EBullsAndCows BullsAndCowsCount) const
{
	std::cout << Guess << " has " << BullsAndCowsCount.Bulls + BullsAndCowsCount.Cows << " of " << GetMyIsogramWordLength() << " correct letters; " << BullsAndCowsCount.Bulls << " Bulls and " << BullsAndCowsCount.Cows << " Cows." << std::endl;
	return;
}

void FBullCowGame::WriteGuessedWords() const
{
	std::cout << "Guessed Words: " << std::endl;
	for (auto i = MyGuessedWords.begin(); i != MyGuessedWords.end(); ++i)
	{
		i->first == MyIsogramWord ? std::cout << "	-> " : std::cout << "	";
		std::cout << i->first << " Bulls: " << i->second.Bulls << " Cows: " << i->second.Cows << std::endl;
	}
}

void FBullCowGame::WriteGuessedLetters() const
{
	std::cout << "Guessed Letters: " << std::endl;
	for (auto i = MyGuessedLetters.begin(); i != MyGuessedLetters.end(); ++i)
	{
		std::cout << *i << " ";
	}
	std::cout << std::endl;
}

bool FBullCowGame::GuessedRight(const int32 Bulls) const
{
	return Bulls == GetMyIsogramWordLength();
}

void FBullCowGame::WriteResult() const
{
	if (bMyGuessedRight)
	{
		std::cout << "You win!" << std::endl;
	}
	else
	{
		std::cout << "You lose..." << std::endl;
	}
	return;
}

bool FBullCowGame::AskToPlayAgain() const
{
	const std::locale Locale;
	FString Answer = "";
	char cAnswer = ' ';

	while (true)
	{
		std::cout << "Do you want to play again? (y/n)" << std::endl;
		std::getline(std::cin, Answer);
		cAnswer = ToLower(Answer)[0];

		if (cAnswer == 'y' || cAnswer == 'n')
		{
			return cAnswer == 'y';
		}
	}
}

FString FBullCowGame::ToLower(const FString Word) const
{
	std::locale Locale;
	FString WordToLower(Word);
	for (int32 i = 0; i < Word.length(); ++i)
	{
		WordToLower[i] = std::tolower(Word[i], Locale);
	}

	return WordToLower;
}

bool FBullCowGame::IsIsogram(const FString Word) const
{
	std::unordered_set<char> DistinctLetters;

	for (char Letter : Word)
	{
		if (!DistinctLetters.insert(Letter).second)
		{
			return false;
		}
	}

	return true;
}

bool FBullCowGame::WasAlreadyGuessed(const FString Guess) const
{
	return MyGuessedWords.find(Guess) != MyGuessedWords.end();
}

int32 FBullCowGame::GetMyIsogramWordLength() const
{
	return MyIsogramWord.length();
}