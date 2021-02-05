#ifndef LevelFailed_air321
#define LevelFailed_air321

#include "CustomText.hpp"
using namespace std;
using namespace sf;

class LevelFailed
{
public:
	LevelFailed();
	bool isFinishedShowing(RenderWindow& window);
	void handleClose(Vector2f mousePos);

protected:
	CustomText custext;
	CustomText custextquote;
	vector<sf::String> quotes = { "Only the dead have seen the end of war.\n\t\t\t\t\t\t\t- George Santayana",
		"The two most powerful warriors are patience and time.\n\t\t\t\t\t\t\t- Leo Tolstoy",
		"The more you sweat in peace, the less you bleed in war.\n\t\t\t\t\t\t\t- Norman Schwarzkopf",
		"In peace, sons bury their fathers. In war, fathers bury their sons.\n\t\t\t\t\t\t\t- Herodotus",
		"All wars are civil wars, because all men are brothers.\n\t\t\t\t\t\t\t- Francois Fenelon",
		"The military don't start wars. Politicians start wars.\n\t\t\t\t\t\t\t- William Westmoreland",
		"War does not determine who is right - only who is left.\n\t\t\t\t\t\t\t- Bertrand Russell",
		"Ambition is the path to success. Persistence is the vehicle you\narrive in.\n\t\t\t\t\t\t\t- Bill Bradley",
		"Success is not the absence of failure; it's the persistence through\nfailure.\n\t\t\t\t\t\t\t- Aisha Tyler",
		"The art of love is largely the art of persistence.\n\t\t\t\t\t\t\t- Albert Ellis",
		"The definition of insanity is doing the same thing over and over again\nand expecting different results\n\t\t\t\t\t\t\t- Albert Einstein" };

	Vector2i mousePos;
	bool clicked;
	Sprite titleSprite;
	Sprite bodySprite;
	Sprite starSprite;
	Sprite textSprite;
	Sprite buttonSprite;

	IntRect buttonRect;
	int playAgainWidth = 315;
	int tryAgainWidth = 304;
	RectangleShape screenRect;

	Text quoteText;
	sf::String completeString;
	sf::String quoteString;
	unsigned int completeStringLength;
	unsigned int quoteStringLength;

	float bodyScale;
	float starScale;
	float buttonScale;
	float textScale;

	float time;
	int sign;
	bool shouldClose;
	float alpha;

	Clock bodyClock;
	Clock rectClock;
	Clock textClock;
	Clock buttonClock;
	Sound failedSound;
	Sound clickSound;
	bool soundPlayed;
	bool clickSoundPlayed;
	bool shouldRetry;
};

#endif
