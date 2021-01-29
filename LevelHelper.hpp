#ifndef LevelHelper_air321
#define LevelHelper_air321

#include "BaseEnemy.hpp"
#include "Boss.hpp"
#include "Collision.h"
#include "Enemy1.hpp"
#include "Enemy2.hpp"
#include "Enemy3.hpp"
#include "Enemy4.hpp"
#include "Enemy5.hpp"
#include "Enemy6.hpp"
#include "Helper.hpp"
#include "Player.hpp"
using namespace std;
using namespace sf;

class LevelHelper
{
public:
	static unsigned int retriesLeft;
	static bool shouldKeepPlaying();
	void isHitBody(Player& player, Enemy1& enemy);
	void isHitBullet(Player& player, Enemy1& enemy);
	void isHitMissile(Player& player, Enemy1& enemy);

	void isHitBody(Player& player, Enemy2& enemy);
	void isHitBullet(Player& player, Enemy2& enemy);
	void isHitMissile(Player& player, Enemy2& enemy);

	void isHitBody(Player& player, Enemy3& enemy);
	void isHitBullet(Player& player, Enemy3& enemy);
	void isHitMissile(Player& player, Enemy3& enemy);

	void isHitBody(Player& player, Enemy4& enemy);
	void isHitBullet(Player& player, Enemy4& enemy);
	void isHitMissile(Player& player, Enemy4& enemy);

	void isHitBody(Player& player, Enemy5& enemy);
	void isHitBullet(Player& player, Enemy5& enemy);
	void isHitMissile(Player& player, Enemy5& enemy);

	void isHitBody(Player& player, Enemy6& enemy);
	void isHitBullet(Player& player, Enemy6& enemy);
	void isHitMissile(Player& player, Enemy6& enemy);

	void isHitBody(Player& player, Boss& enemy);
	void isHitBullet(Player& player, Boss& enemy);
	void isHitMissile(Player& player, Boss& enemy);

private:
	vector<String> quotes;
	// unsigned int i;
};

#endif