#include "LevelPuzzle2.hpp" // level header file
#include "Puzzle.hpp"
using namespace std;
using namespace sf;

void LevelPuzzle2::Show(RenderWindow& window, Event& event)
{
	while (LevelHelper::shouldKeepPlaying())
	{
		Puzzle puzzle;
		puzzle.make(14, 6, 9, 3, 9, 5, 60);
		cout << "in level 101 " << endl;
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

		bool someone_is_alive;

		vector<Enemy1> first_enemies1(3);
		vector<Enemy3> first_enemies2(2);
		vector<Enemy4> second_enemies(4);
		vector<Enemy6> third_enemies1(3);
		vector<Enemy2> third_enemies2(4);

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

			someone_is_alive = false;

			for (auto& this_enemy : first_enemies1)
			{
				if (this_enemy.isDead == false)
				{
					custext1.Show(window, "Wave 1", 80, 200, 200, 2, true, 0.1);

					if (someone_is_alive == false)
						someone_is_alive = true;
					this_enemy.move(360);
					this_enemy.fireBullet(yuri, 3500, 3300, 520);
					this_enemy.fireMissile(yuri, 4900, 4700, 500);
					levelhelp.isHitBody(yuri, this_enemy);
					levelhelp.isHitBullet(yuri, this_enemy);
					levelhelp.isHitMissile(yuri, this_enemy);
					this_enemy.Show(window);
				}
			}
			for (auto& this_enemy : first_enemies2)
			{
				if (this_enemy.isDead == false)
				{

					if (someone_is_alive == false)
						someone_is_alive = true;
					this_enemy.move(360);
					this_enemy.fireBullet(yuri, 3500, 3300, 520);
					this_enemy.fireMissile(yuri, 4900, 4700, 500);
					levelhelp.isHitBody(yuri, this_enemy);
					levelhelp.isHitBullet(yuri, this_enemy);
					levelhelp.isHitMissile(yuri, this_enemy);
					this_enemy.Show(window);
				}
			}

			if (someone_is_alive == false)
			{
				for (auto& this_enemy : second_enemies)
				{
					if (this_enemy.isDead == false)
					{
						if (custext1.hidingFinished == true)
						{
							custext2.Show(window, "Wave 2", 80, 200, 200, 2, true, 0.1);
						}

						if (someone_is_alive == false)
							someone_is_alive = true;
						this_enemy.move(360);
						this_enemy.fireBullet(yuri, 3500, 3300, 520);
						this_enemy.fireMissile(yuri, 4900, 4700, 500);
						levelhelp.isHitBody(yuri, this_enemy);
						levelhelp.isHitBullet(yuri, this_enemy);
						levelhelp.isHitMissile(yuri, this_enemy);
						this_enemy.Show(window);
					}
				}
			}

			if (someone_is_alive == false)
			{
				for (auto& this_enemy : third_enemies1)
				{
					if (this_enemy.isDead == false)
					{
						if (custext2.hidingFinished == true)
						{
							custext3.Show(window, "Wave 3", 80, 200, 200, 2, true, 0.1);
						}

						if (someone_is_alive == false)
							someone_is_alive = true;
						this_enemy.move(360);
						this_enemy.fireBullet(yuri, 3500, 3300, 520);
						this_enemy.fireMissile(yuri, 4900, 4700, 500);
						levelhelp.isHitBody(yuri, this_enemy);
						levelhelp.isHitBullet(yuri, this_enemy);
						levelhelp.isHitMissile(yuri, this_enemy);
						this_enemy.Show(window);
					}
				}
				for (auto& this_enemy : third_enemies2)
				{
					if (this_enemy.isDead == false)
					{

						if (someone_is_alive == false)
							someone_is_alive = true;
						this_enemy.move(360);
						this_enemy.fireBullet(yuri, 3500, 3300, 520);
						this_enemy.fireMissile(yuri, 4900, 4700, 500);
						levelhelp.isHitBody(yuri, this_enemy);
						levelhelp.isHitBullet(yuri, this_enemy);
						levelhelp.isHitMissile(yuri, this_enemy);
						this_enemy.Show(window);
					}
				}
			}

			if (playerHealth > yuri.healthValue && isHit == false)
			{
				isHit = true;
			}

			if (isHit == true && custext4.hidingFinished == false)
			{
				custext4.Show(window, "ZenMeter failed to calibrate. You need to calibrate manually.", 40, 20, 120, 4, true, 0.01);
			}

			if (custext4.hidingFinished == true && puzzle.getState() == Puzzle::Nothing && yuri.isDead == false && Helper::enemiesDied() < 16)
			{
				puzzle.Show(window, event);
			}

			yuri.Show(window);

			if (yuri.isDead || puzzle.getState() == Puzzle::Failed)
			{
				if (levelFailedObj.isFinishedShowing(window))
				{
					break;
				}
			}
			if (Helper::enemiesDied() == 16)
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
