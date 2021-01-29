#ifndef Background_air321
#define Background_air321

#include "Helper.hpp"

using namespace sf; // don't forget this or you would have to initialize everything with sf::
using namespace std;
class Background
{
public:
	Background();
	void Show(RenderWindow& window);
	static bool shouldRemoveElement(Sprite& sprite);

private:
	struct Scene
	{
		Sprite backSprite;
		float blending_pos; // to avoid background sprite glitch
		Sprite element1Sprite;
		Sprite element2Sprite;
		Sprite element3Sprite;
		Sprite element4Sprite;
		Sprite element5Sprite;
	};
	Scene backScene;
	bool shouldRenewElements;
	vector<Sprite> elements;
	unsigned int j;
	unsigned int i;
	int k;

	enum Scenes
	{
		Sea = 0,
		Land = 1
	};
	Scenes scenery;
};
#endif
