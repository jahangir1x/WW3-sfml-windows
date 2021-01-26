#include "Level1.hpp" // level header file
using namespace std;
using namespace sf;

void Level1::Show(RenderWindow& window, Event& event)
{
	cout << "in level 1 " << endl;
	LevelFailed levelFailedObj; // create levelFailed object to show level failed message
	LevelHelper levelhelp;
	Success successObj;
	Helper::resetEnemyDiedCounter();

	Background background;
	Player yuri; // our hero
	vector<Enemy5> enemies(1);

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

		for (auto& enemy : enemies)
		{

			enemy.move(300);
			enemy.fireBullet(yuri, 4000, 2000, 400);
			enemy.fireMissile(yuri, 5000, 1000, 300);
			levelhelp.isHitBody(yuri, enemy);
			levelhelp.isHitBullet(yuri, enemy);
			levelhelp.isHitMissile(yuri, enemy);
			enemy.Show(window);
		}

		yuri.Show(window);

		// cout << "state: " << success.getState() << endl;
		if (yuri.isDead)
			levelFailedObj.Show(window, event); // show level failed
		if (Helper::enemiesDied() == 1)
		{
			successObj.Show(window);
			if (successObj.getState() == Success::Proceed)
			{
				return;
			}
		}
		window.display();
	}
}
