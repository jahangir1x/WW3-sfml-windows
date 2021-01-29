#include "Level3.hpp" // level header file
#include "GameUI.hpp"
#include "Success.hpp"
using namespace std;
using namespace sf;

void Level3::Show(RenderWindow& window, Event& event)
{
	while (LevelHelper::shouldKeepPlaying())
	{
		////// mandatory //////
		cout << "in level 3 " << endl;
		Success success;
		LevelFailed levelFailedObj;
		LevelHelper levelhelp;
		GameUI::init();
		Helper::resetEnemyDiedCounter();
		Player::resetMissileCounter();
		Background background;
		Player yuri;
		////// mandatory //////

		yuri.healthValue = 3;
		vector<Enemy3> enemies(1);

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
						GameUI::handleClose(window, Mouse::getPosition(window));
						success.handleClose(Mouse::getPosition(window));
						levelFailedObj.handleClose(Mouse::getPosition(window));
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

			// cout << "rand: " << Helper::randRange(-900.3, -400.9) << endl;

			for (auto& enemy : enemies)
			{
				// enemy.healthValue = 5;
				enemy.move(300);
				enemy.fireBullet(yuri, 4000, 2000, 400);
				enemy.fireMissile(yuri, 5000, 1000, 300);
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