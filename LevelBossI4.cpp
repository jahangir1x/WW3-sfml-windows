#include "LevelBossI4.hpp" // level header file
#include "Puzzle.hpp"
using namespace std;
using namespace sf;

void LevelBossI4::Show(RenderWindow& window, Event& event)
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
		bool inversed = false;
		float playerHealth = 90;
		CustomText custext4;
		bool isHit = false;

		Enemy4 enemy;

		enemy.enemySprite.setScale(1 * Helper::getWidthScalingFactor(), 1 * Helper::getWidthScalingFactor());
		enemy.bulletLeft.sprite.setScale(2 * Helper::getWidthScalingFactor(), 2 * Helper::getWidthScalingFactor());
		enemy.bulletRight.sprite.setScale(2 * Helper::getWidthScalingFactor(), 2 * Helper::getWidthScalingFactor());
		enemy.missile.sprite.setScale(2 * Helper::getWidthScalingFactor(), 2 * Helper::getWidthScalingFactor());
		enemy.bigExplosion.sprite.setScale(2 * Helper::getWidthScalingFactor(), 2 * Helper::getWidthScalingFactor());
		enemy.bulletDamage = 10;
		enemy.missileDamage = 20;
		enemy.healthValue = 700;
		Music music;
		music.openFromFile("res/music/boss.wav");
		music.setVolume(60);
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
					GameUI::handleClose(window, Mouse::getPosition(window));
					success.handleClose(Mouse::getPosition(window));
					levelFailedObj.handleClose(Mouse::getPosition(window));
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

			custext1.Show(window, "Caution: IMIVGK963 approaching", 80, 200, 200, 2, true, 0.1);

			if (custext1.hidingFinished)
			{
				enemy.move(370);
			}
			enemy.fireBullet(yuri, 4000, 3800, 690);
			enemy.fireMissile(yuri, 5000, 4900, 695);
			levelhelp.isHitBody(yuri, enemy);
			levelhelp.isHitBullet(yuri, enemy);
			levelhelp.isHitMissile(yuri, enemy);
			enemy.Show(window);

			yuri.Show(window);

			if (playerHealth > yuri.healthValue && isHit == false && yuri.isDead == false)
			{
				isHit = true;
			}

			if (isHit == true && custext4.hidingFinished == false)
			{
				custext4.Show(window, "Malfunction: Movement controls inversed.", 40, 20, 120, -1, true, 0.01);
			}

			if (custext4.fullShowed)
			{
				inversed = true;
			}

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
