#ifndef Success_air321
#define Success_air321
#include "CustomText.hpp"

using namespace std;
using namespace sf;

class Success
{
public:
	Success();
	bool isFinishedShowing(RenderWindow& window);
	void textShow(RenderWindow& window, String str, unsigned int char_size, float pos_x, float pos_y);
	void handleClose(Vector2i mousePos);
	Sprite buttonSprite;

protected:
	CustomText custext;
	Vector2i mousePos;
	bool clicked;
	Sprite titleSprite;
	Sprite bodySprite;
	Sprite starSprite;
	Sprite textSprite;

	IntRect buttonRect;
	RectangleShape screenRect;

	Text completeText;
	sf::String completeString;
	unsigned int length;

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