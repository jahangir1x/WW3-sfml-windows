#ifndef CustomText_air321
#define CustomText_air321

using namespace std;
using namespace sf;

class CustomText
{
public:
	CustomText();
	void Show(RenderWindow& window, sf::String str, unsigned int char_size, float pos_x, float pos_y, float hide_after_seconds = -1.0, bool shouldHighlight = false, float text_popping_delay = 0.1, sf::Color color = sf::Color(255, 174, 174));
	Text text;
	bool fullShowed;
	bool hidingFinished;
	bool shouldMute;

private:
	unsigned int currentLength;
	Clock clock;
	int sign;
	int green_blue;
	unsigned int index;
	std::string test;
	bool waiting_finished;
	float time_to_wait;
	Clock highlightClock;
	Sound typeWrite;
};
#endif