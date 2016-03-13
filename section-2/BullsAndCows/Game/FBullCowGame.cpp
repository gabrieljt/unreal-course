#include "FBullCowGame.h"

struct EBullsAndCowsCount
{
public:
	EBullsAndCowsCount()
		: Bulls(0)
		, Cows(0)
	{}

	EBullsAndCowsCount(const int32 Bulls, const int32 Cows)
		: Bulls(Bulls)
		, Cows(Cows)
	{
	}

	const int32 Bulls;
	const int32 Cows;
};

FBullCowGame::FBullCowGame(const FString Guess, const int32 MaximumTries)
	: MyGuess(ToLower(Guess))
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
	const int Index = std::rand() % 3;
	return MyIsogramWords[Index];
}

const FString FBullCowGame::MyIsogramWords[] = { "play", "plot", "puny" };

void FBullCowGame::RunGame()
{
	WriteIntro();
	RunGuessLoop();
	WriteResult();
}

bool FBullCowGame::HasGuessedRight() const
{
	return bMyGuessedRight;
}

void FBullCowGame::WriteIntro() const
{
	std::cout << "Welcome to Bulls and Cows!" << std::endl;
	std::cout << "Can you guess the " << GetMyGuessWordLength() << " letter isogram I'm thinking of?" << std::endl;
	return;
}

void FBullCowGame::RunGuessLoop()
{
	FString Guess = "";
	for (int32 i = 0; i < MyMaximumTries; ++i)
	{
		MyCurrentTry = i + 1;
		Guess = ToLower(ReadValidGuessInput());
		bMyGuessedRight = CheckBullsAndCowsCount(Guess);
		WriteBullsAndCowsCount(Guess);
		WriteGuessedWords();
		WriteGuessedLetters();

		if (bMyGuessedRight)
		{
			break;
		}
	}

	return;
}

FString FBullCowGame::ReadValidGuessInput() const
{
	bool bIsValidGuess = false;
	FString Guess = "";
	const std::locale Locale;

	do
	{
		std::cout << "Try " << MyCurrentTry << " of " << MyMaximumTries << ". Type your guess: ";
		std::getline(std::cin, Guess);

		bIsValidGuess = IsValidGuessInput(Guess);
		if (!bIsValidGuess)
		{
			std::cout << "Your guess must be an isogram (no repeated letters) and must have " << GetMyGuessWordLength() << " letters." << std::endl;
		}
	} while (!bIsValidGuess);

	return Guess;
}

bool FBullCowGame::IsValidGuessInput(const FString Word) const
{
	return Word.length() == GetMyGuessWordLength() && IsIsogram(Word);
}

bool FBullCowGame::CheckBullsAndCowsCount(const FString Guess)
{
	int32 Bulls = 0, Cows = 0;

	for (int32 i = 0; i < GetMyGuessWordLength(); ++i)
	{
		MyGuessedLetters.insert(Guess[i]);
		for (int32 j = 0; j < GetMyGuessWordLength(); ++j)
		{
			if (Guess[i] == MyGuess[j])
			{
				i == j ? ++Bulls : ++Cows;
			}
		}
	}
	MyGuessedWords.insert(std::pair<FString, EBullsAndCowsCount>(Guess, EBullsAndCowsCount(Bulls, Cows)));

	return Guess == MyGuess;
}

void FBullCowGame::WriteBullsAndCowsCount(const FString Guess)
{
	EBullsAndCowsCount Result = MyGuessedWords[Guess];
	std::cout << Guess << " has " << Result.Bulls + Result.Cows << " of " << GetMyGuessWordLength() << " correct letters; " << Result.Bulls << " Bulls and " << Result.Cows << " Cows." << std::endl;
	return;
}

void FBullCowGame::WriteGuessedWords() const
{
	std::cout << "Guessed Words: " << std::endl;
	for (auto i = MyGuessedWords.begin(); i != MyGuessedWords.end(); ++i)
	{
		i->first == MyGuess ? std::cout << "	-> " : std::cout << "	";
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
		Answer = ToLower(Answer);
		cAnswer = Answer[0];

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
	std::unordered_set<char> Letters;

	for (int32 i = 0; i < Word.length(); ++i)
	{
		Letters.insert(Word[i]);
	}

	return Letters.size() == Word.length();
}

int32 FBullCowGame::GetMyGuessWordLength() const
{
	return MyGuess.length();
}