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
		puzzle.make(3, 4, 5, 21, 7, 7, 10000);

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
		CustomText custext1;
		CustomText custext2;
		CustomText custext3;
		////// mandatory //////

		// yuri.healthValue = 4;
		vector<Boss> enemies(1);
		for (auto& boss : enemies)
		{
			boss.setStyle(Boss::Style::ShakaLala);
			boss.healthValue=800;

		}
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

			for (auto& enemy : enemies)
			{
				// enemy.healthValue = 5;
				enemy.move(300);
				enemy.missileCount = 10;
				enemy.fireBullet(yuri, 1000, 0, 500);
				enemy.fireMissile(yuri, 1000, 0, 400);

				levelhelp.isHitBody(yuri, enemy);
				levelhelp.isHitBullet(yuri, enemy);
				levelhelp.isHitMissile(yuri, enemy);
				enemy.Show(window);
			}

			yuri.Show(window);

			// cout << "state: " << success.getState() << endl;
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
				 if (puzzle.getState() == Puzzle::Nothing)
				 {

				 	puzzle.Show(window, event);
				 	cout << "fin" << endl;
				 }
				 if (puzzle.getState() == Puzzle::Solved)
				 {
                    if (success.isFinishedShowing(window) == true)
                    {
                        return;
                    }
				 }

                else
                {
                    if (levelFailedObj.isFinishedShowing(window))
                    {
                        cout << "showing failed" << endl;
                        break;
                    }
                }
			}
			GameUI::showPlayerUI(window);
			window.display();
		}
	}
}
