#include "LevelTutorial.hpp" // level header file
#include "CustomText.hpp"
#include "GameUI.hpp"
#include "Success.hpp"
using namespace std;
using namespace sf;

void LevelTutorial::Show(RenderWindow& window, Event& event)
{
	while (LevelHelper::shouldKeepPlaying())
	{
		////// mandatory //////
		cout << "in level tutorial " << endl;
		Success success;
		LevelFailed levelFailedObj;
		LevelHelper levelhelp;
		GameUI::init();
		Helper::resetEnemyDiedCounter();
		Player::resetMissileCounter();
		Background background;
		Player yuri;
		// yuri.healthValue = 500;
		CustomText custext1;
		CustomText custext2;
		CustomText custext3;
		CustomText custext4;
		bool playerMoved = false;
		bool playerFiredBullet = false;
		bool playerFiredMissile = false;
		bool shouldSpawnEnemy = false;
		Clock tutorialClock;
		Vector2f playerPos = yuri.playerSprite.getPosition();
		unsigned int missileCount = yuri.missileCount;
		Enemy1 enemy;

		////// mandatory //////
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
				else if (event.type == Event::MouseButtonReleased)
				{
					if (event.mouseButton.button == Mouse::Left)
					{
						yuri.startFiringBullet();
						GameUI::handleClose(window, window.mapPixelToCoords(Mouse::getPosition(window)));
						success.handleClose(window.mapPixelToCoords(Mouse::getPosition(window)));
						levelFailedObj.handleClose(window.mapPixelToCoords(Mouse::getPosition(window)));
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

			if (playerMoved == false)
			{
				custext1.Show(window, "Press W,S,A,D to move.", 40, 20, 120, -1.0, true, 0.01);

				if (Helper::pointsDistance(playerPos.x, playerPos.y, yuri.playerSprite.getPosition().x, yuri.playerSprite.getPosition().y) > 30)
				{
					playerMoved = true;
				}
			}

			if (playerFiredBullet == false && playerMoved == true)
			{
				custext2.Show(window, "Press Left mouse button to toggle firing bullets.", 40, 20, 220, -1, true, 0.01);
				if (yuri.startedFiring == true)
				{
					playerFiredBullet = true;
				}
			}

			if (playerFiredMissile == false && playerFiredBullet == true)
			{
				custext3.Show(window, "Press Right mouse button to fire missile.", 40, 20, 120, -1, true, 0.01);
				if (missileCount != yuri.missileCount)
				{
					playerFiredMissile = true;
				}
				else
				{
					tutorialClock.restart();
				}
			}

			if (shouldSpawnEnemy == false && playerFiredMissile == true)
			{
				custext4.Show(window, "Enemy approaching, prepare to engage.", 40, 20, 220, 5, true, 0.01);
				if (tutorialClock.getElapsedTime().asSeconds() > 2.0)
				{
					shouldSpawnEnemy = true;
				}
			}

			if (shouldSpawnEnemy == true)
			{
				enemy.move(400);
				enemy.fireBullet(yuri, 5000, 4000, 500);
				enemy.fireMissile(yuri, 6000, 3000, 400);
				levelhelp.isHitBody(yuri, enemy);
				levelhelp.isHitBullet(yuri, enemy);
				levelhelp.isHitMissile(yuri, enemy);
				enemy.Show(window);
			}

			yuri.Show(window);
			if (yuri.isDead)
			{
				if (levelFailedObj.isFinishedShowing(window))

				{
					break;
				}
			}

			if (Helper::enemiesDied() == 1)
			{
				if (success.isFinishedShowing(window))
				{
					return;
				}
			}

			GameUI::showPlayerUI(window);

			window.display();
		}
	}
}
