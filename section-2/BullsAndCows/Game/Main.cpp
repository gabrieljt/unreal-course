#include "FBullCowGame.h"

int main()
{
	int32 Score = 0, TimesPlayed = 0, MaximumTries = 5;
	bool bWantsToPlayAgain = true;

	do
	{
		FBullCowGame BullCowGame(FBullCowGame::GetIsogramWord(), MaximumTries);
		BullCowGame.RunGame();
		if (BullCowGame.HasGuessedRight())
		{
			++Score;
		}
		++TimesPlayed;

		bWantsToPlayAgain = BullCowGame.AskToPlayAgain();
	} while (bWantsToPlayAgain);

	std::cout << "Your final score was " << Score << " / " << TimesPlayed << std::endl;

	return 0;
}