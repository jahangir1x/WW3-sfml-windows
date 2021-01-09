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
	Player(RenderWindow& window);
	void Show(RenderWindow& window);
	void isHitBody(Sprite& targetSprite, float damage);
	void isHitBullet(Sprite& targetSprite, unsigned int id, float damage);
	void isHitMissile(Sprite& targetSprite, unsigned int id, float damage);
	bool isDead;																							 //isDead is check to show level failed scene
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void fireBullet();
	void fireMissile();
	void show_explosion_bullet(Vector2f pos);
	void show_explosion_missile(Vector2f pos);
	Sprite playerSprite;
	float bulletDamage;	 //damage of enemy
	float missileDamage; //damage of enemy
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
	bool explosionFin;

private:
	void Die();
	int windowSizeX;
	int windowSizeY;
	float moveSpeed;
	unsigned int i;
	unsigned int j;
	LevelFailed levelfailed;
	GameHandler gamehandler;
	IntRect rect;
	Clock hitClock;
	Clock playerClock;
	Clock bulletClock;
	Clock missileClock;
	Clock bigExplosionClock;
	Texture playerTexture;
	bool shouldDisappear;
	bool shouldExplode;
};
#endif
