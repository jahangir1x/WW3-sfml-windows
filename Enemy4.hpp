#ifndef Enemy4_air321
#define Enemy4_air321

#include "BaseEnemy.hpp"
#include "GameHandler.hpp"
#include "LevelFailed.hpp"
#include "Player.hpp"

using namespace sf; // don't forget this or you would have to initialize everything with sf::
using namespace std;
class Enemy4 : public BaseEnemy // code name: rando_sharpshooter
{
public:
	void Show(RenderWindow& window);
	void move(float speed = 400);
	void fireBullet(Player& player, int interval_milliseconds, int interval_offset, float speed = 500);
	void fireMissile(Player& player, int interval_milliseconds, int interval_offset, float speed = 400);
};
#endif
