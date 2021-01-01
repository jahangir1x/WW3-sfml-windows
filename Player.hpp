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
	void isHit(Sprite& targetSprite, float damage); //damage of player
	bool isDead;									//isDead is check to show level failed scene
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void fireBullet();
	void fireMissile();
	Sprite playerSprite;
	float bulletDamage;	 //damage of enemy
	float missileDamage; //damage of enemy

private:
	void Die();
	int windowSizeX;
	int windowSizeY;
	float moveSpeed;
	unsigned int i;
	LevelFailed levelfailed;
	GameHandler gamehandler;
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
	};
	struct Missile
	{
		int missileCount;
		Text missileCountString;
		Text missileText;
		Texture texture;
		Sprite sprite;
		float speed;
	};
	Health playerHealth;
	Bullet bulletLeft;
	Bullet bulletRight;
	vector<Bullet> bulletsLeft;
	vector<Bullet> bulletsRight;
	Missile missile;
	vector<Missile> missiles;
	IntRect rect;
	Sprite* prevCollisionSprite; // store addres of previously collided object
	Clock hitClock;
	Clock playerClock;
	Clock bulletClock;
	Clock missileClock;
	Texture playerTexture;
};
#endif
