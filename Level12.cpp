#include "Level12.hpp" // level header file
using namespace std;
using namespace sf;

void Level12::Show(RenderWindow& window, Event& event)
{
	while (LevelHelper::shouldKeepPlaying())
	{
		cout << "in level 108 " << endl;
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
		CustomText custext5;
		bool someone_is_alive;
		vector<Enemy6> first_enemies1(3);
		vector<Enemy3> first_enemies2(2);
		vector<Enemy1> first_enemies3(2);
		vector<Enemy3> second_enemies1(2);
		vector<Enemy2> second_enemies2(4);
		vector<Enemy1> third_enemies1(3);
		vector<Enemy6> third_enemies2(2);
		vector<Enemy5> third_enemies3(2);
		vector<Enemy3> fourth_enemies1(5);
		vector<Enemy5> fourth_enemies2(3);
		vector<Enemy5> fifth_enemies1(2);
		vector<Enemy3> fifth_enemies2(4);
		vector<Enemy6> fifth_enemies3(2);

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
					this_enemy.move(383);
					this_enemy.fireBullet(yuri, 6300, 5800, 760);
					this_enemy.fireMissile(yuri, 7000, 6000, 730);
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
					this_enemy.move(383);
					this_enemy.fireBullet(yuri, 6300, 5800, 760);
					this_enemy.fireMissile(yuri, 7000, 6000, 730);
					levelhelp.isHitBody(yuri, this_enemy);
					levelhelp.isHitBullet(yuri, this_enemy);
					levelhelp.isHitMissile(yuri, this_enemy);
					this_enemy.Show(window);
				}
			}
			for (auto& this_enemy : first_enemies3)
			{
				if (this_enemy.isDead == false)
				{

					if (someone_is_alive == false)
						someone_is_alive = true;
					this_enemy.move(383);
					this_enemy.fireBullet(yuri, 6300, 5800, 760);
					this_enemy.fireMissile(yuri, 7000, 6000, 730);
					levelhelp.isHitBody(yuri, this_enemy);
					levelhelp.isHitBullet(yuri, this_enemy);
					levelhelp.isHitMissile(yuri, this_enemy);
					this_enemy.Show(window);
				}
			}

			if (someone_is_alive == false)
			{
				for (auto& this_enemy : second_enemies1)
				{
					if (this_enemy.isDead == false)
					{
						if (custext1.hidingFinished == true)
						{
							custext2.Show(window, "Wave 2", 80, 200, 200, 2, true, 0.1);
						}

						if (someone_is_alive == false)
							someone_is_alive = true;
						this_enemy.move(383);
						this_enemy.fireBullet(yuri, 6300, 5800, 760);
						this_enemy.fireMissile(yuri, 7000, 6000, 730);
						levelhelp.isHitBody(yuri, this_enemy);
						levelhelp.isHitBullet(yuri, this_enemy);
						levelhelp.isHitMissile(yuri, this_enemy);
						this_enemy.Show(window);
					}
				}
				for (auto& this_enemy : second_enemies2)
				{
					if (this_enemy.isDead == false)
					{

						if (someone_is_alive == false)
							someone_is_alive = true;
						this_enemy.move(383);
						this_enemy.fireBullet(yuri, 6300, 5800, 760);
						this_enemy.fireMissile(yuri, 7000, 6000, 730);
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
						this_enemy.move(383);
						this_enemy.fireBullet(yuri, 6300, 5800, 760);
						this_enemy.fireMissile(yuri, 7000, 6000, 730);
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
						this_enemy.move(383);
						this_enemy.fireBullet(yuri, 6300, 5800, 760);
						this_enemy.fireMissile(yuri, 7000, 6000, 730);
						levelhelp.isHitBody(yuri, this_enemy);
						levelhelp.isHitBullet(yuri, this_enemy);
						levelhelp.isHitMissile(yuri, this_enemy);
						this_enemy.Show(window);
					}
				}

				for (auto& this_enemy : third_enemies3)
				{
					if (this_enemy.isDead == false)
					{

						if (someone_is_alive == false)
							someone_is_alive = true;
						this_enemy.move(383);
						this_enemy.fireBullet(yuri, 6300, 5800, 760);
						this_enemy.fireMissile(yuri, 7000, 6000, 730);
						levelhelp.isHitBody(yuri, this_enemy);
						levelhelp.isHitBullet(yuri, this_enemy);
						levelhelp.isHitMissile(yuri, this_enemy);
						this_enemy.Show(window);
					}
				}
			}

			if (someone_is_alive == false)
			{
				for (auto& this_enemy : fourth_enemies1)
				{
					if (this_enemy.isDead == false)
					{
						if (custext3.hidingFinished == true)
						{
							custext4.Show(window, "Wave 4", 80, 200, 200, 2, true, 0.1);
						}

						if (someone_is_alive == false)
							someone_is_alive = true;
						this_enemy.move(383);
						this_enemy.fireBullet(yuri, 6300, 5800, 760);
						this_enemy.fireMissile(yuri, 7000, 6000, 730);
						levelhelp.isHitBody(yuri, this_enemy);
						levelhelp.isHitBullet(yuri, this_enemy);
						levelhelp.isHitMissile(yuri, this_enemy);
						this_enemy.Show(window);
					}
				}
				for (auto& this_enemy : fourth_enemies2)
				{
					if (this_enemy.isDead == false)
					{

						if (someone_is_alive == false)
							someone_is_alive = true;
						this_enemy.move(383);
						this_enemy.fireBullet(yuri, 6300, 5800, 760);
						this_enemy.fireMissile(yuri, 7000, 6000, 730);
						levelhelp.isHitBody(yuri, this_enemy);
						levelhelp.isHitBullet(yuri, this_enemy);
						levelhelp.isHitMissile(yuri, this_enemy);
						this_enemy.Show(window);
					}
				}
			}

			if (someone_is_alive == false)
			{
				for (auto& this_enemy : fifth_enemies1)
				{
					if (this_enemy.isDead == false)
					{
						if (custext4.hidingFinished == true)
						{
							custext5.Show(window, "Wave 5", 80, 200, 200, 2, true, 0.1);
						}

						if (someone_is_alive == false)
							someone_is_alive = true;
						this_enemy.move(383);
						this_enemy.fireBullet(yuri, 6300, 5800, 760);
						this_enemy.fireMissile(yuri, 7000, 6000, 730);
						levelhelp.isHitBody(yuri, this_enemy);
						levelhelp.isHitBullet(yuri, this_enemy);
						levelhelp.isHitMissile(yuri, this_enemy);
						this_enemy.Show(window);
					}
				}
				for (auto& this_enemy : fifth_enemies2)
				{
					if (this_enemy.isDead == false)
					{

						if (someone_is_alive == false)
							someone_is_alive = true;
						this_enemy.move(383);
						this_enemy.fireBullet(yuri, 6300, 5800, 760);
						this_enemy.fireMissile(yuri, 7000, 6000, 730);
						levelhelp.isHitBody(yuri, this_enemy);
						levelhelp.isHitBullet(yuri, this_enemy);
						levelhelp.isHitMissile(yuri, this_enemy);
						this_enemy.Show(window);
					}
				}
				for (auto& this_enemy : fifth_enemies3)
				{
					if (this_enemy.isDead == false)
					{

						if (someone_is_alive == false)
							someone_is_alive = true;
						this_enemy.move(383);
						this_enemy.fireBullet(yuri, 6300, 5800, 760);
						this_enemy.fireMissile(yuri, 7000, 6000, 730);
						levelhelp.isHitBody(yuri, this_enemy);
						levelhelp.isHitBullet(yuri, this_enemy);
						levelhelp.isHitMissile(yuri, this_enemy);
						this_enemy.Show(window);
					}
				}
			}

			yuri.Show(window);
			if (Helper::enemiesDied() == 36)
			{
				if (success.isFinishedShowing(window))
				{
					return;
				}
			}
			if (yuri.isDead)
			{
				if (levelFailedObj.isFinishedShowing(window))
				{
					break;
				}
			}
			GameUI::showPlayerUI(window);
			window.display();
		}
	}
}
