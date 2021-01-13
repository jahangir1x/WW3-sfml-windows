#ifndef Enemy2_air321
#define Enemy2_air321

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
class Enemy2
{
public:
	Enemy2();
	void Show(RenderWindow& window);
	void setPosition(int targetPos_x, int targetPos_y, int offset);
	// void isHitBody(Player& player);
	// void isHitBullet(Player& player);
	// void isHitMissile(Player& player);
	bool isDead;
	bool isDying;
	void moveLeft(float speed = 400);
	void moveRight(float speed = 400);
	void moveUp(float speed = 400);
	void moveDown(float speed = 400);
	void move(float speed = 400);
	void fireBullet(int interval_milliseconds, int interval_offset, float speed = 500);
	void fireMissile(int interval_milliseconds, int interval_offset, float speed = 400);
	void fireBullet_to(Vector2f targetPos, int interval_milliseconds, int interval_offset, float speed = 500, int offset = 0);
	void fireMissile_to(Vector2f targetPos, int interval_milliseconds, int interval_offset, float speed = 400, int offset = 0);
	void show_explosion_bullet(Vector2f pos);
	void show_explosion_missile(Vector2f pos);
	void Die();
	float healthValue;
	float bulletDamage;	 //damage of player
	float missileDamage; //damage of player
	float hitBodyDamage;
	struct Bullet
	{
		Texture texture;
		Sprite sprite;
		float speed;
		unsigned int id;
	};
	struct Missile
	{
		int missileCount;
		Texture texture;
		Sprite sprite;
		float speed;
		unsigned int id;
	};
	struct Explosion
	{
		Clock clock;
		Sprite sprite;
		Texture texture;
		IntRect rect;
		Vector2f pos;
	};
	Explosion explosion;
	Explosion bigExplosion;
	vector<Explosion> explosions;
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
	vector<unsigned int> prevCollidedObj;

private:

	unsigned int i;
	unsigned int j;
	GameHandler gamehandler;
	IntRect rect;
	Sprite* prevCollisionSprite; // store addres of previously collided object
	Clock enemy1Clock;
	Clock bulletClock;
	Clock missileClock;
	Clock moveClock;
	Clock hitClock;
	Clock bigExplosionClock;
	Vector2f shootPos;
	Vector2f movePos;
	Vector2f moveNorm;
	Vector2f tempVect;
	Vector2f targetPos;
	bool moveInit;
	bool moveFin;
	bool moveLeftFin;
	bool moveRightFin;
	bool shouldDisappear;
	bool shouldExplode;
	// int speedInit;
	Vector2f bulletOriginPosLeft;
	Vector2f bulletOriginPosRight;
	Vector2f missileOriginPos;
};
#endif
