#include "Level9.hpp" // level header file
using namespace std;
using namespace sf;

void Level9::Show(RenderWindow& window, Event& event)
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

		CustomText custext1;
		CustomText custext2;
		CustomText custext3;
		CustomText custext4;
		bool someone_is_alive;
		vector<Enemy5> first_enemies1(3);
		vector<Enemy6> first_enemies2(4);
		vector<Enemy4> second_enemies1(3);
		vector<Enemy1> second_enemies2(3);
		vector<Enemy1> third_enemies1(4);
		vector<Enemy6> third_enemies2(4);
		vector<Enemy6> fourth_enemies1(5);
		vector<Enemy4> fourth_enemies2(3);
		for (auto& enemy : first_enemies1)
		{
			enemy.setStyle(Enemy1::Style(1));
		}
		for (auto& enemy : first_enemies2)
		{
			enemy.setStyle(Enemy1::Style(0));
		}
		for (auto& enemy : second_enemies1)
		{
			enemy.setStyle(Enemy1::Style(2));
		}
		for (auto& enemy : second_enemies2)
		{
			enemy.setStyle(Enemy1::Style(3));
		}
		for (auto& enemy : third_enemies1)
		{
			enemy.setStyle(Enemy1::Style(4));
		}
		for (auto& enemy : third_enemies2)
		{
			enemy.setStyle(Enemy1::Style(6));
		}
		for (auto& enemy : fourth_enemies1)
		{
			enemy.setStyle(Enemy1::Style(5));
		}
		for (auto& enemy : fourth_enemies2)
		{
			enemy.setStyle(Enemy1::Style(0));
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
					this_enemy.move(361);
					this_enemy.fireBullet(yuri, 6300, 5800, 710);
					this_enemy.fireMissile(yuri, 7000, 6000, 670);
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
					this_enemy.move(361);
					this_enemy.fireBullet(yuri, 6300, 5800, 710);
					this_enemy.fireMissile(yuri, 7000, 6000, 670);
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
						this_enemy.move(361);
						this_enemy.fireBullet(yuri, 6300, 5800, 710);
						this_enemy.fireMissile(yuri, 7000, 6000, 670);
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
						this_enemy.move(361);
						this_enemy.fireBullet(yuri, 6300, 5800, 710);
						this_enemy.fireMissile(yuri, 7000, 6000, 670);
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
						this_enemy.move(361);
						this_enemy.fireBullet(yuri, 6300, 5800, 710);
						this_enemy.fireMissile(yuri, 7000, 6000, 670);
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
						this_enemy.move(361);
						this_enemy.fireBullet(yuri, 6300, 5800, 710);
						this_enemy.fireMissile(yuri, 7000, 6000, 670);
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
						this_enemy.move(361);
						this_enemy.fireBullet(yuri, 6300, 5800, 710);
						this_enemy.fireMissile(yuri, 7000, 6000, 670);
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
						this_enemy.move(361);
						this_enemy.fireBullet(yuri, 6300, 5800, 710);
						this_enemy.fireMissile(yuri, 7000, 6000, 670);
						levelhelp.isHitBody(yuri, this_enemy);
						levelhelp.isHitBullet(yuri, this_enemy);
						levelhelp.isHitMissile(yuri, this_enemy);
						this_enemy.Show(window);
					}
				}
			}

			yuri.Show(window);
			if (Helper::enemiesDied() == 29)
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
