#ifndef Player_air321
#define Player_air321

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

class Player
{
public:
	Player();
	void Show(RenderWindow& window);
	// void isHitBody(Enemy1& enemy);
	// void isHitBody(Enemy2& enemy);
	// void isHitBullet(Enemy1& enemy);
	// void isHitBullet(Enemy2& enemy);
	// void isHitMissile(Enemy1& enemy);
	// void isHitMissile(Enemy2& enemy);
	bool isDead;
	bool isDying; //isDead is check to show level failed scene
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void fireBullet();
	void fireMissile();
	void show_explosion_bullet(Vector2f pos);
	void show_explosion_missile(Vector2f pos);
	void Die();
	Sprite playerSprite;
	float bulletDamage;	 //damage of enemy
	float missileDamage; //damage of enemy
	float hitBodyDamage;
	struct Health
	{
		float healthValue;
		Font healthfont;
		Text healthtext;
		RectangleShape outsideRect;
		RectangleShape insideRect;
		Vector2f insideSize;
	};

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
		Text missileCountString;
		Text missileText;
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
	Health playerHealth;
	vector<Bullet> bulletsLeft;
	vector<Bullet> bulletsRight;
	Bullet bulletLeft;
	Bullet bulletRight;
	Missile missile;
	vector<Missile> missiles;
	vector<unsigned int> prevCollidedObj;
	Clock hitClock;

private:

	float moveSpeed;
	unsigned int i;
	unsigned int j;
	LevelFailed levelfailed;
	GameHandler gamehandler;
	IntRect rect;

	Clock playerClock;
	Clock bulletClock;
	Clock missileClock;
	Clock bigExplosionClock;
	Texture playerTexture;
	bool shouldDisappear;
	bool shouldExplode;

};
#endif
