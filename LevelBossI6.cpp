#include "LevelBossI6.hpp" // level header file
#include "Puzzle.hpp"
using namespace std;
using namespace sf;

void LevelBossI6::Show(RenderWindow& window, Event& event)
{
	while (LevelHelper::shouldKeepPlaying())
	{
		cout << "in level 101 " << endl;
		Success success;
		LevelFailed levelFailedObj;
		LevelHelper levelhelp;
		GameUI::init();
		Helper::resetEnemyDiedCounter();
		Player::resetMissileCounter();
		Background background;
		Player yuri;

		CustomText custext1;
		CustomText custext4;

		bool inversed = false;
		float inverseStart = 90;

		Enemy6 enemy;

		enemy.enemySprite.setScale(1, 1);
		enemy.bulletLeft.sprite.setScale(1, 1);
		enemy.bulletRight.sprite.setScale(1, 1);
		enemy.missile.sprite.setScale(1, 1);

		enemy.bulletDamage = 10;
		enemy.missileDamage = 22;
		enemy.healthValue = 800;
		Music music;
		music.openFromFile("res/music/boss.wav");
		music.setVolume(80);
		music.play();

		while (window.isOpen())
		{
			Helper::resetClock();
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					window.close();
					exit(0);
				}
				else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
				{
					yuri.startFiringBullet();
					GameUI::handleClose(window, window.mapPixelToCoords(Mouse::getPosition(window)));
					success.handleClose(window.mapPixelToCoords(Mouse::getPosition(window)));
					levelFailedObj.handleClose(window.mapPixelToCoords(Mouse::getPosition(window)));
				}
			}
			window.clear(Color::Blue);
			background.Show(window);
			if (Mouse::isButtonPressed(Mouse::Right))
			{
				yuri.fireMissile();
			}
			yuri.fireBullet();
			if (!inversed)
			{
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
			}
			else
			{
				if (Keyboard::isKeyPressed(Keyboard::D))
				{
					yuri.moveLeft();
				}
				if (Keyboard::isKeyPressed(Keyboard::A))
				{
					yuri.moveRight();
				}
				if (Keyboard::isKeyPressed(Keyboard::S))
				{
					yuri.moveUp();
				}
				if (Keyboard::isKeyPressed(Keyboard::W))
				{
					yuri.moveDown();
				}
			}

			custext1.Show(window, "Caution: IMNIL3 approaching", 80, 200, 200, 2, true, 0.1);

			if (custext1.hidingFinished)
			{
				enemy.move(400);
			}
			enemy.missileCount = 10; // infinite missile
			enemy.fireBullet(yuri, 1000, 800, 760);
			enemy.fireMissile(yuri, 1000, 700, 755);
			levelhelp.isHitBody(yuri, enemy);
			levelhelp.isHitBullet(yuri, enemy);
			levelhelp.isHitMissile(yuri, enemy);
			enemy.Show(window);

			if (inverseStart > yuri.healthValue && yuri.isDead == false)
			{
				// if (inverseEnd > yuri.healthValue)
				// {
				// 	cout << "normal at: " << yuri.healthValue << endl;
				// 	inversed = false;
				// }
				// else
				// {
				custext4.Show(window, "Malfunction: Movement controls inversed.", 40, 20, 120, -1, true, 0.01);
				if (custext4.fullShowed)
				{
					cout << "inverting at: " << yuri.healthValue << endl;
					inversed = true;
				}
				// }
			}

			yuri.Show(window);
			if (yuri.isDead)
			{
				if (levelFailedObj.isFinishedShowing(window))
				{
					break;
				}
			}
			//            enemies[0].healthValue = 3;
			if (Helper::enemiesDied() == 1)
			{
				if (success.isFinishedShowing(window) == true)
				{
					return;
				}
			}
			GameUI::showPlayerUI(window);
			window.display();
		}
	}
}
