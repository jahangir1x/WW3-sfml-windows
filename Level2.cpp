#include "Level2.hpp" // level header file
using namespace std;
using namespace sf;

void Level2::Show(RenderWindow& window, Event& event)
{
    cout << "in level 2 " << endl;
	LevelFailed levelFailedObj; // create levelFailed object to show level failed message
	LevelHelper levelhelp;
	Helper::resetEnemyDiedCounter();
	Background background;
	Player yuri; // our hero
	Enemy1 enemy;

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
		enemy.fireBullet(yuri, 4000,2000,400);
		enemy.fireMissile(yuri, 5000,1000,300);
		levelhelp.isHitBody(yuri, enemy);
		levelhelp.isHitBullet(yuri, enemy);
		levelhelp.isHitMissile(yuri, enemy);

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
