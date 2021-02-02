#include "LevelBossFinal.hpp" // level header file
#include "Boss.hpp"
#include "CustomText.hpp"
#include "GameUI.hpp"
#include "Puzzle.hpp"
#include "Success.hpp"
using namespace std;
using namespace sf;

void LevelBossFinal::Show(RenderWindow& window, Event& event)
{
	while (LevelHelper::shouldKeepPlaying())
	{
		Puzzle puzzle;
		puzzle.make(3, 4, 5, 4, 7, 7, 60);

		////// mandatory //////
		cout << "in level 1 " << endl;
		Success success;
		LevelFailed levelFailedObj;
		LevelHelper levelhelp;
		GameUI::init();
		Helper::resetEnemyDiedCounter();
		Player::resetMissileCounter();
		Background background;
		Player yuri;
		////// mandatory //////

		// yuri.healthValue = 4;
		CustomText custext1;
		CustomText custext2;
		CustomText custext3;

		Boss boss;

		Music music;
		music.openFromFile("res/music/boss.wav");
		music.setVolume(60);
		music.play();

		boss.setStyle(Boss::Style::ShakaLala);
		boss.enemySprite.setScale(0.6 * Helper::getWidthScalingFactor(), 0.6 * Helper::getWidthScalingFactor());
		boss.bulletDamage = 18;
		boss.missileDamage = 32;

		boss.healthValue = 1000;
		bool isHit = false;
		bool isHitAgain = false;
		bool inversed = false;
		float playerHealth = 90;
		float playerHealthInverse = 70;

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

			custext1.Show(window, "Caution: MSHPGX7C approaching", 80, 200, 200, 2, true, 0.1);

			if (custext1.hidingFinished)
			{
				boss.move(400);
			}
			boss.missileCount = 10;
			boss.fireBullet(yuri, 3000, 2800, 800);
			boss.fireMissile(yuri, 3000, 2800, 780);

			levelhelp.isHitBody(yuri, boss);
			levelhelp.isHitBullet(yuri, boss);
			levelhelp.isHitMissile(yuri, boss);
			boss.Show(window);
			if (playerHealth > yuri.healthValue && isHit == false)
			{
				isHit = true;
			}

			if (isHit == true && custext2.hidingFinished == false)
			{
				custext2.Show(window, "ZenMeter failed to calibrate. You need to calibrate manually.", 40, 20, 120, 4, true, 0.01);
			}

			if (custext2.hidingFinished == true && puzzle.getState() == Puzzle::Nothing && yuri.isDead == false)
			{
				puzzle.Show(window, event);
			}

			if (playerHealthInverse > yuri.healthValue && puzzle.getState() == Puzzle::Solved)
			{
				isHitAgain = true;
			}

			if (isHitAgain == true && custext2.hidingFinished == true && custext3.hidingFinished == false)
			{
				custext3.Show(window, "Malfunction: Movement controls inversed.", 40, 20, 120, -1, true, 0.01);
			}

			if (custext3.fullShowed)
			{
				inversed = true;
			}

			yuri.Show(window);

			// cout << "state: " << success.getState() << endl;
			if (yuri.isDead || puzzle.getState() == Puzzle::Failed)
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
