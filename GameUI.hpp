#ifndef GameUI_air321
#define GameUI_air321
#include "Player.hpp"

using namespace std;
using namespace sf;

class GameUI
{
public:
	static void init();
	static void reset();
	static void showPlayerUI(RenderWindow& window);
	static void showMenuUI(RenderWindow& window);
	static void handleClose(RenderWindow& window, Vector2i MousePos);

	enum CursorStates
	{
		Inactive = 0,
		Left = 1,
		Right = 2,
		Both = 3
	};
	static CursorStates cursorState;

private:
	static RectangleShape healthInsideRect;
	static RectangleShape healthOutsideRect;
	static Sprite retrySprite;
	static vector<Sprite> retrySprites;
	static Sprite missileSprite;
	static vector<Sprite> missileSprites;
	static Sprite cursorSprite;
	static IntRect cursorRect;
	static Sprite closeButton;
	static unsigned int i;
	static unsigned int j;
	static Sound clickSound;
};
#endif