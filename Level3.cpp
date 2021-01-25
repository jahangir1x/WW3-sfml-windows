#include "Level3.hpp" // level header file
using namespace std;
using namespace sf;

void Level3::Show(RenderWindow& window, Event& event)
{
	cout << "in level 3 " << endl;
	LevelFailed levelFailedObj; // create levelFailed object to show level failed message
	LevelHelper levelhelp;
	Helper::resetEnemyDiedCounter();
	Helper::resetClock();
	Background background;
	Player yuri; // our hero
	Enemy5 enemy;
	enemy.enemySprite.setScale(2, 2);		// 2x enemy.
	enemy.bulletLeft.sprite.setScale(2, 2); // 2x left bullets < notice: it is bulletLeft not bulletsLeft >
	enemy.bulletRight.sprite.setScale(2, 2);
	enemy.missile.sprite.setScale(2, 2);
	enemy.bigExplosion.sprite.setScale(2, 2);
	enemy.bulletDamage = 20;  // একটা বুলেট প্লেয়ারের গায়ে লাগলে প্লেয়ারের ২০ লাইফ কমবে...
	enemy.missileDamage = 30; // একটা মিসাইল প্লেয়ারের গায়ে লাগলে প্লেয়ারের ৩০ লাইফ কমবে...
	enemy.healthValue = 300;  // enemey এর লাইফ এখন ৩০০

	while (window.isOpen())
	{
		Helper::resetClock();
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			else if (event.type == Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					yuri.startFiringBullet();
				}
			}
		}
		window.clear(Color::Blue);
		background.Show(window);
		if (Mouse::isButtonPressed(Mouse::Right))
		{
			yuri.fireMissile();
		}
		yuri.fireBullet();
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			yuri.moveLeft();
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			yuri.moveRight();
		}
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			yuri.moveUp();
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			yuri.moveDown();
		}

		enemy.move(300);
		enemy.fireBullet(yuri, 4000, 2000, 400);
		enemy.fireMissile(yuri, 5000, 1000, 300);
		levelhelp.isHitBody(yuri, enemy);
		levelhelp.isHitBullet(yuri, enemy);
		levelhelp.isHitMissile(yuri, enemy);

		cout << "enemy health: " << enemy.healthValue << endl;
		cout << "player health: " << yuri.playerHealth.healthValue << endl;

		if (Helper::enemiesDied() == 1)
		{
			return; // show next level
		}
		enemy.Show(window);
		yuri.Show(window);
		if (yuri.isDead)
			levelFailedObj.Show(window, event); // show level failed
		window.display();
	}
}
