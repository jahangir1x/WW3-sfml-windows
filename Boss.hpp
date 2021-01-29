// code name: boss rando_arc_vertical
// movement: 	random
// shooting:	circle arc player y pos

#ifndef Boss_air321
#define Boss_air321

#include "BaseEnemy.hpp"
#include "GameHandler.hpp"
#include "LevelFailed.hpp"
#include "Player.hpp"

using namespace sf; // don't forget this or you would have to initialize everything with sf::
using namespace std;
class Boss : public BaseEnemy
{
public:
	void Show(RenderWindow& window);
	void move(float speed = 400);

	void fireBullet(Player& player, int interval_milliseconds, int interval_offset, float speed = 500);
	void fireBulletCircle(Player& player, int interval_milliseconds, int interval_offset, float speed = 500);
	void fireBulletToPlayer(Player& player, int interval_milliseconds, int interval_offset, float speed = 500);
	void fireBulletSine(Player& player, int interval_milliseconds, int interval_offset, float speed = 500);

	void fireMissile(Player& player, int interval_milliseconds, int interval_offset, float speed = 400);
	void fireMissileCircle(Player& player, int interval_milliseconds, int interval_offset, float speed = 400);
	void fireMissileToPlayer(Player& player, int interval_milliseconds, int interval_offset, float speed = 400);
	void fireMissileSine(Player& player, int interval_milliseconds, int interval_offset, float speed = 400);

private:
};
#endif
