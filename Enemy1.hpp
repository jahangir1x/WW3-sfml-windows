#ifndef Enemy1_air321
#define Enemy1_air321

#include "BaseEnemy.hpp"
#include "GameHandler.hpp"
#include "LevelFailed.hpp"

using namespace sf; // don't forget this or you would have to initialize everything with sf::
using namespace std;
class Enemy1 : public BaseEnemy
{
public:
	void Show(RenderWindow& window);
	void move(float speed = 400);
	void fireBullet(int interval_milliseconds, int interval_offset, float speed = 500);
	void fireMissile(int interval_milliseconds, int interval_offset, float speed = 400);
};
#endif
