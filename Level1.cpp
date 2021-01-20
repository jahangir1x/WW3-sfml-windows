#include "Level1.hpp" // level header file
using namespace std;
using namespace sf;

void Level1::Show(RenderWindow& window, Event& event)
{
	LevelFailed levelFailedObj; // create levelFailed object to show level failed message
	LevelHelper levelhelper;
	Player yuri; // our hero
	Helper::resetEnemyDiedCounter();
	Enemy1 enemy1;
	Enemy2 enemy2;
	Enemy3 enemy3;
	Enemy4 enemy4;
	Enemy5 enemy5;
	Enemy6 enemy6;
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
		window.clear(Color::Black);
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

		if (!enemy1.isDead){
			enemy1.move(200);
			enemy1.fireBullet(yuri, 1000, 1000, 400);
			enemy1.fireMissile(yuri, 8000, 6000, 300);
			levelhelper.isHitBody(yuri, enemy1);
			levelhelper.isHitBullet(yuri, enemy1);
			levelhelper.isHitMissile(yuri, enemy1);
			enemy1.Show(window);
		}
		else if (!enemy2.isDead)
		{
			enemy2.move(200);
			enemy2.fireBullet(yuri, 1000, 1000, 400);
			enemy2.fireMissile(yuri, 8000, 6000, 300);
			levelhelper.isHitBody(yuri, enemy2);
			levelhelper.isHitBullet(yuri, enemy2);
			levelhelper.isHitMissile(yuri, enemy2);
			enemy2.Show(window);
		}
		else if (!enemy3.isDead)
		{
			enemy3.move(200);
			enemy3.fireBullet(yuri, 1000, 1000, 400);
			enemy3.fireMissile(yuri, 8000, 6000, 300);
			levelhelper.isHitBody(yuri, enemy3);
			levelhelper.isHitBullet(yuri, enemy3);
			levelhelper.isHitMissile(yuri, enemy3);
			enemy3.Show(window);
		}
		else if (!enemy4.isDead)
		{
			enemy4.move(200);
			enemy4.fireBullet(yuri, 1000, 1000, 400);
			enemy4.fireMissile(yuri, 8000, 6000, 300);
			levelhelper.isHitBody(yuri, enemy4);
			levelhelper.isHitBullet(yuri, enemy4);
			levelhelper.isHitMissile(yuri, enemy4);
			enemy4.Show(window);
		}
		else if (!enemy5.isDead)
		{
			enemy5.move(200);
			enemy5.fireBullet(yuri, 1000, 1000, 400);
			enemy5.fireMissile(yuri, 8000, 6000, 300);
			levelhelper.isHitBody(yuri, enemy5);
			levelhelper.isHitBullet(yuri, enemy5);
			levelhelper.isHitMissile(yuri, enemy5);
			enemy5.Show(window);
		}
		else if (!enemy6.isDead)
		{
			enemy6.move(200);
			enemy6.fireBullet(yuri, 1000, 1000, 400);
			enemy6.fireMissile(yuri, 8000, 6000, 300);
			levelhelper.isHitBody(yuri, enemy6);
			levelhelper.isHitBullet(yuri, enemy6);
			levelhelper.isHitMissile(yuri, enemy6);
			enemy6.Show(window);
		}

		if (Helper::enemiesDied() == 6)
		{
			return; // show next level
		}
		yuri.Show(window);
		if (yuri.isDead)
			levelFailedObj.Show(window, event); // show level failed
		window.display();
	}
}
