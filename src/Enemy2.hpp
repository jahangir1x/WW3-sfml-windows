// code name: dabbu_sharpShooter
// movement: 	Left, Right
// shooting:	player position

#ifndef Enemy2_air321
#define Enemy2_air321

#include "BaseEnemy.hpp"
#include "GameHandler.hpp"
#include "Helper.hpp"
#include "LevelFailed.hpp"
#include "Player.hpp"

using namespace sf; // don't forget this or you would have to initialize everything with sf::
using namespace std;
class Enemy2 : public BaseEnemy
{
public:
	void Show(RenderWindow& window);
	void move(float speed = 400);
	void fireBullet(Player& player, int interval_milliseconds, int interval_offset, float speed = 500);
	void fireMissile(Player& player, int interval_milliseconds, int interval_offset, float speed = 400);
};
#endif
