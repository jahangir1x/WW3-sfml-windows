#ifndef MainMenu_air321
#define MainMenu_air321

using namespace std;
using namespace sf;

class MainMenu
{
public:
	enum MenuResult
	{
		Nothing,
		Play,
		Help,
		Credits,
		Exit
	};

	MenuResult Show(RenderWindow& window, Event& menuEvent);

private:
	Vector2f mousePosition;
	Vector2f mousePositionClicked;
	bool clicked;
	MenuResult result;
	Sprite menuBackSprite;
	float widthScale;
	float heightScale;

	Sprite gameLogoSprite;

	IntRect playRect;
	Sprite playSprite;
	Clock playClock;

	IntRect helpRect;
	Sprite helpSprite;
	Clock helpClock;

	IntRect creditsRect;
	Sprite creditsSprite;
	Clock creditsClock;

	IntRect exitRect;
	Sprite exitSprite;
	Clock exitClock;

	Clock menuClock;
	Sound menuHover;
	Sound menuClick;
	bool hoverSoundPlayed;
	bool clickSoundPlayed;
};
#endif
