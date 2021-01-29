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
	void handleClose(Vector2i mousePos);

protected:
	CustomText custext;
	CustomText custextquote;
	vector<sf::String> quotes = { "The definition of insanity is doing the same thing over and over again\nand expecting different results.\n \t\t- Albert Einstein","HSdfosdifosidofisdf","sdofsdiofiosdfiosdoif" };

	Vector2i mousePos;
	bool clicked;
	Sprite titleSprite;
	Sprite bodySprite;
	Sprite starSprite;
	Sprite textSprite;
	Sprite buttonSprite;

	IntRect buttonRect;
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
};

#endif
