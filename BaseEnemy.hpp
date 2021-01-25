#ifndef BaseEnemy_air321
#define BaseEnemy_air321

#include "GameHandler.hpp"
#include "LevelFailed.hpp"
#include "Player.hpp"

using namespace sf; // don't forget this or you would have to initialize everything with sf::
using namespace std;
class BaseEnemy
{
public:
	BaseEnemy();
	void Show(RenderWindow& window);
	bool isDead;
	bool isDying;
	void show_explosion_bullet(Vector2f pos);
	void show_explosion_missile(Vector2f pos);
	void Die();
	float healthValue;
	float bulletDamage;	 //damage of player
	float missileDamage; //damage of player
	float hitBodyDamage;
	struct Bullet
	{
		Sprite sprite;
		float speed;
		Vector2f velocity; // need this for non vertical shooting
		float rotation;	   // need this for sine wave like shooting
	};
	struct Missile
	{
		int missileCount;
		Sprite sprite;
		float speed;
		Vector2f velocity; // need this for non vertical shooting
		float rotation;	   // need this for sine wave like shooting
	};
	struct Explosion
	{
		Clock clock;
		Sprite sprite;
		IntRect rect;
		Vector2f pos;
	};

	vector<Explosion> explosions;
	vector<Bullet> bulletsLeft;
	vector<Bullet> bulletsRight;
	vector<Missile> missiles;
	Sprite enemySprite;
	Explosion bigExplosion;
	Bullet bulletLeft;
	Bullet bulletRight;
	Missile missile;
	Explosion explosion;
	static bool shouldRemoveBullet(Bullet& bullet);
	static bool shouldRemoveMissile(Missile& missile);
	static bool shouldRemoveExplosion(Explosion& explosion);

protected:
	void moveLeft(float speed = 400);
	void moveRight(float speed = 400);
	void moveUp(float speed = 400);
	void moveDown(float speed = 400);
	unsigned int i;
	unsigned int j;
	int bulletInterval;
	int missileInterval;
	IntRect enemyRect;
	Clock enemyClock;
	Clock bulletClock;
	Clock missileClock;
	Clock moveClock;
	Clock hitClock;
	Clock bigExplosionClock;
	Vector2f movePos;
	Vector2f moveNorm;
	Vector2f tempVect;
	bool moveInit;
	bool isBulletIntervalSet;
	bool isMissileIntervalSet;
	bool firstTime;
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
