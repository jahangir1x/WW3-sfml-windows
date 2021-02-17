#ifndef Player_air321
#define Player_air321

#include "GameHandler.hpp"
#include "LevelFailed.hpp"

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
	void startFiringBullet();
	void fireBullet();
	void fireMissile();
	void show_explosion_bullet(Vector2f pos);
	void show_explosion_missile(Vector2f pos);
	void Die();
	Sprite playerSprite;
	float bulletDamage;	 //damage of enemy
	float missileDamage; //damage of enemy
	float hitBodyDamage;
	static float healthValue;

	struct Bullet
	{
		Sprite sprite;
		float speed;
	};
	static unsigned int missileCount;
	struct Missile
	{
		Sprite sprite;
		float speed;
	};
	struct Explosion
	{
		Clock clock;
		Sprite sprite;
		IntRect rect;
		Vector2f pos;
	};
	Explosion explosion;
	Explosion bigExplosion;
	vector<Explosion> explosions;
	vector<Bullet> bulletsLeft;
	vector<Bullet> bulletsRight;
	Bullet bulletLeft;
	Bullet bulletRight;
	Missile missile;
	vector<Missile> missiles;
	Clock hitClock;
	static bool shouldRemoveBullet(Bullet& bullet);
	static bool shouldRemoveMissile(Missile& missile);
	static bool shouldRemoveExplosion(Explosion& explosion);
	static void resetMissileCounter();
	static bool startedFiring;
	static bool isMute;

private:
	float moveSpeed;
	unsigned int i;
	unsigned int j;
	IntRect playerRect;
	Clock playerClock;
	Clock bulletClock;
	Clock missileClock;
	Clock bigExplosionClock;
	bool shouldDisappear;
	bool shouldExplode;
	bool firstTime;
	Sound bulletSound;
	Sound missileSound;
	Sound bulletHitSound;
	Sound missileHitSound;
	Sound explodedSound;
};
#endif
