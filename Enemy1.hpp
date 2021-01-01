#ifndef Enemy1_air321
#define Enemy1_air321

#include "GameHandler.hpp"
#include "LevelFailed.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <bits/stdc++.h>
using namespace sf; // don't forget this or you would have to initialize everything with sf::
using namespace std;
class Enemy1
{
public:
	Enemy1(RenderWindow& window);
	void Show(RenderWindow& window);
	void isHit(Sprite& targetSprite, float damage);
	bool isDead;
	void moveLeft(float speed = 400);
	void moveRight(float speed = 400);
	void moveUp(float speed = 400);
	void moveDown(float speed = 400);
	void move_to(Vector2f targetPos, int interval_milliseconds, int interval_offset, float speed = 400, int offset = 0);
	void fireBullet_to(Vector2f targetPos, int interval_milliseconds, int interval_offset, float speed = 500, int offset = 0);
	void fireMissile_to(Vector2f targetPos, int interval_milliseconds, int interval_offset, float speed = 400, int offset = 0);
	float healthValue;
	float bulletDamage;	 //damage of player
	float missileDamage; //damage of player
	struct Bullet
	{
		Texture texture;
		Sprite sprite;
		float speed;
	};
	struct Missile
	{
		int missileCount;
		Texture texture;
		Sprite sprite;
		float speed;
	};
	Bullet bulletLeft;
	Bullet bulletRight;
	vector<Bullet> bulletsLeft;
	vector<Bullet> bulletsRight;
	Missile missile;
	vector<Missile> missiles;
	Sprite enemy1Sprite;
	Texture enemy1Texture;
	float bulletInterval;
	float missileInterval;

private:
	void Die();
	int windowSizeX;
	int windowSizeY;
	unsigned int i;
	GameHandler gamehandler;
	IntRect rect;
	Sprite* prevCollisionSprite; // store addres of previously collided object
	Clock hitClock;
	Clock enemy1Clock;
	Clock bulletClock;
	Clock missileClock;
	Clock moveClock;
	Vector2f shootPos;
	Vector2f movePos;
	Vector2f shootBulletTemp;
	Vector2f shootMissileTemp;
	Vector2f moveNorm;
	Vector2f moveInit;
	// int speedInit;
	Vector2f bulletOriginPosLeft;
	Vector2f bulletOriginPosRight;
	Vector2f missileOriginPos;
};
#endif
