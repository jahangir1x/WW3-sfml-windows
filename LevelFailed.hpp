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
	vector<sf::String> quotes = { "Only the dead have seen the end of war.\n\t\t\t\t\t\t\t\t\t\t\t\t- George Santayana",
		"The two most powerful warriors are patience and time.\n\t\t\t\t\t\t\t\t\t\t\t\t- Leo Tolstoy",
		"The more you sweat in peace, the less you bleed in war.\n\t\t\t\t\t\t\t\t\t\t\t\t- Norman Schwarzkopf",
		"In peace, sons bury their fathers. In war, fathers bury their sons.\n\t\t\t\t\t\t\t\t\t\t\t\t- Herodotus",
		"All wars are civil wars, because all men are brothers.\n\t\t\t\t\t\t\t\t\t\t\t\t- Francois Fenelon",
		"The military don't start wars. Politicians start wars.\n\t\t\t\t\t\t\t\t\t\t\t\t- William Westmoreland",
		"War does not determine who is right - only who is left.\n\t\t\t\t\t\t\t\t\t\t\t\t- Bertrand Russell",
		"Ambition is the path to success. Persistence is the vehicle you\narrive in.\n\t\t\t\t\t\t\t\t\t\t\t\t- Bill Bradley",
		"Success is not the absence of failure; it's the persistence through\nfailure.\n\t\t\t\t\t\t\t\t\t\t\t\t- Aisha Tyler",
		"The art of love is largely the art of persistence.\n\t\t\t\t\t\t\t\t\t\t\t\t- Albert Ellis",
		"The definition of insanity is doing the same thing over and over again\nand expecting different results\n\t\t\t\t\t\t\t\t\t\t\t\t- Albert Einstein"
		"The greatest glory in living lies not in never falling, but in\nrising every time we fall.\n\t\t\t\t\t\t\t\t\t\t\t\t- Nelson Mandela",
		"The way to get started is to quit talking and begin doing.\n\t\t\t\t\t\t\t\t\t\t\t\t- Walt Disney",
		"If life were predictable it would cease to be life, and be without\n flavor.\n\t\t\t\t\t\t\t\t\t\t\t\t- Eleanor Roosevelt",
		"When you reach the end of your rope, tie a knot in it and hang on.\n\t\t\t\t\t\t\t\t\t\t\t\t- Franklin D. Roosevelt",
		"It is during our darkest moments that we must focus to see\nthe light.\n\t\t\t\t\t\t\t\t\t\t\t\t- Aristotle",
		"You will face many defeats in life, but never let yourself\nbe defeated.\n\t\t\t\t\t\t\t\t\t\t\t\t- Maya Angelou",
		"Never let the fear of striking out keep you from playing the game.\n\t\t\t\t\t\t\t\t\t\t\t\t- Babe Ruth",
		"Life is either a daring adventure or nothing at all.\n\t\t\t\t\t\t\t\t\t\t\t\t- Helen Keller",
		"Many of life's failures are people who did not realize how\nclose they were to success when they gave up.\n\t\t\t\t\t\t\t\t\t\t\t\t- Thomas A. Edison",
		"Life is a succession of lessons which must be lived to\nbe understood.\n\t\t\t\t\t\t\t\t\t\t\t\t- Ralph Waldo Emerson",
		"Success is not final; failure is not fatal: It is the courage\nto continue that counts.\n\t\t\t\t\t\t\t\t\t\t\t\t- Winston S. Churchill",
		"Success usually comes to those who are too busy to be looking\nfor it.\n\t\t\t\t\t\t\t\t\t\t\t\t- Henry David Thoreau",
		"If you really look closely, most overnight successes took\na long time.\n\t\t\t\t\t\t\t\t\t\t\t\t- Steve Jobs",
		"The secret of success is to do the common thing\nuncommonly well.\n\t\t\t\t\t\t\t\t\t\t\t\t- John D. Rockefeller Jr.",
		"I find that the harder I work, the more luck I seem to have.\n\t\t\t\t\t\t\t\t\t\t\t\t- Thomas Jefferson",
		"Success is walking from failure to failure with no loss\nof enthusiasm.\n\t\t\t\t\t\t\t\t\t\t\t\t- Winston Churchill",
		"The only place where success comes before work is in\nthe dictionary.\n\t\t\t\t\t\t\t\t\t\t\t\t- Vidal Sassoon",
		"Nothing is impossible, the word itself says, I'm possible!\n\t\t\t\t\t\t\t\t\t\t\t\t- Audrey Hepburn",
		"Believe you can and you're halfway there.\n\t\t\t\t\t\t\t\t\t\t\t\t- Theodore Roosevelt",
		"Winning isn't everything, but wanting to win is.\n\t\t\t\t\t\t\t\t\t\t\t\t- Vince Lombardi",
		"Get busy living or get busy dying.\n\t\t\t\t\t\t\t\t\t\t\t\t- Stephen King",
		"Turn your wounds into wisdom.\n\t\t\t\t\t\t\t\t\t\t\t\t- Oprah Winfrey",
		"Everything negative – pressure, challenges – is all an\nopportunity for me to rise.\n\t\t\t\t\t\t\t\t\t\t\t\t- Kobe Bryant",
		"I like criticism. It makes you strong.\n\t\t\t\t\t\t\t\t\t\t\t\t- LeBron James" };

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
