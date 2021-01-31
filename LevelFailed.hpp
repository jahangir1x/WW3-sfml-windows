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
	vector<sf::String> quotes = { "The definition of insanity is doing the same thing over and over again\nand expecting different results.\n \t\t- Albert Einstein",
	"The art of love is largely the art of persistence. - Albert Ellis",
	"Success is not the absence of failure;\nit's the persistence through failure",
	"Ambition is the path to success.\nPersistence is the vehicle you arrive in.",
	"War does not determine who is right - only who is left.",
	"The military don't start wars. Politicians start wars.",
	"All wars are civil wars, because all men are brothers.",
	"In peace,sons bury their fathers.In war, fathers bury their sons.",
	"The more you sweat in peace,the less you bleed in war.",
	"The two most powerful warriors are patience and time.",
	"Only the dead have seen the end of war." };
	//"You can be the winner if you are a shit!--Md.Sourav;
	//"Go fuck your gf--Rocky

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
