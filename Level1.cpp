#include "Level1.hpp" // level header file
using namespace std;
using namespace sf;

void Level1::Show(RenderWindow& window, Event& event)
{
	LevelFailed levelFailedObj; // create levelFailed object to show level failed message
	LevelHelper levelhelper;
	Player yuri; // our hero
	Helper::resetEnemyDiedCounter();
	vector<Enemy2> enemies2(3);
	while (window.isOpen())
	{
		Helper::resetClock();
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}
		window.clear(Color::Black);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			yuri.fireBullet();
		}
		if (Mouse::isButtonPressed(Mouse::Right))
		{
			yuri.fireMissile();
		}
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
		for (auto& enemy : enemies2)
		{
			enemy.move(200);
			enemy.fireBullet(yuri, 7000, 5000, 400);
			enemy.fireMissile(yuri, 8000, 6000, 300);
			levelhelper.isHitBody(yuri, enemy);
			levelhelper.isHitBullet(yuri, enemy);
			levelhelper.isHitMissile(yuri, enemy);
			enemy.Show(window);
		}
		if (Helper::enemiesDied() == 3)
		{
			return; // show next level
		}
		yuri.Show(window);
		if (yuri.isDead)
			levelFailedObj.Show(window, event); // show level failed
		window.display();
	}
}
