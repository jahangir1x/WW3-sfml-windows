#ifndef LevelHelper_air321
#define LevelHelper_air321

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <bits/stdc++.h>

#include "Enemy1.hpp"
#include "Enemy2.hpp"
#include "Player.hpp"
using namespace std;
using namespace sf;

class LevelHelper
{
public:

	void isHitBody(Player& player, Enemy1& enemy);
	void isHitBody(Player& player, Enemy2& enemy);

	void isHitBullet(Player& player, Enemy1& enemy);
	void isHitBullet(Player& player, Enemy2& enemy);

	void isHitMissile(Player& player, Enemy1& enemy);
	void isHitMissile(Player& player, Enemy2& enemy);


private:
	unsigned int i;
};

#endif