#ifndef Success_air321
#define Success_air321

using namespace std;
using namespace sf;

class Success
{
public:
	Success();
	void Show(RenderWindow& window);
	void textShow(RenderWindow& window, String str, unsigned int char_size, float pos_x, float pos_y);
	enum State
	{
		Nothing = 0,
		Proceed = 1
	};
	State getState();

protected:
	Sprite bodySprite;
	Sprite starSprite;
	Sprite textSprite;
	Sprite buttonSprite;

	IntRect buttonRect;
	RectangleShape screenRect;

	State currentState;

	Text completeText;
	sf::String completeString = "Objective Complete";
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