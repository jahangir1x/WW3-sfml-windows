#include "Level1.hpp" // level header file
#include "Boss.hpp"
#include "CustomText.hpp"
#include "GameUI.hpp"
#include "Puzzle.hpp"
#include "Success.hpp"
using namespace std;
using namespace sf;

void Level1::Show(RenderWindow& window, Event& event)
{
	while (LevelHelper::shouldKeepPlaying())
	{
		Puzzle puzzle;
		puzzle.make(3, 4, 5, 21, 7, 7, 60);

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
		Boss boss;

		Music music;
		music.openFromFile("res/music/boss.wav");
		music.setVolume(20);
		music.play();

		boss.setStyle(Boss::Style::ShakaLala);
		boss.enemySprite.setScale(0.6, 0.6);
		boss.bulletDamage = 15;
		boss.missileDamage = 25;
		boss.healthValue = 500;

		boss.healthValue = 800;
		bool isHit = false;
		float playerHealth = 90;

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

			custext1.Show(window, "Caution: MIG93 approaching", 80, 200, 200, 2, true, 0.1);
			cout << "first" << endl;

			if (custext1.hidingFinished)
			{
				boss.move(400);
			}
			boss.missileCount = 10;
			boss.fireBullet(yuri, 2000, 100, 550);
			boss.fireMissile(yuri, 3000, 2000, 400);

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
