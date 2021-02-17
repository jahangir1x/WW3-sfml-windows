#include "LevelInversed1.hpp" // level header file
using namespace std;
using namespace sf;

void LevelInversed1::Show(RenderWindow& window, Event& event)
{
	while (LevelHelper::shouldKeepPlaying())
	{
		cout << "in level 201 " << endl;
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

		vector<Enemy1> first_enemies1(3);
		vector<Enemy2> first_enemies2(1);
		vector<Enemy4> second_enemies(4);
		vector<Enemy5> third_enemies1(3);
		vector<Enemy2> third_enemies2(3);
		for (auto& enemy : first_enemies1)
		{
			enemy.setStyle(Enemy1::Style(6));
		}
		for (auto& enemy : first_enemies2)
		{
			enemy.setStyle(Enemy1::Style(4));
		}
		for (auto& enemy : second_enemies)
		{
			enemy.setStyle(Enemy1::Style(5));
		}
		for (auto& enemy : third_enemies1)
		{
			enemy.setStyle(Enemy1::Style(3));
		}
		for (auto& enemy : third_enemies2)
		{
			enemy.setStyle(Enemy1::Style(2));
		}

		bool someone_is_alive;
		bool inversed = false;
		float inverseStart = 90;
		float inverseEnd = 45;

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

			someone_is_alive = false;

			for (auto& this_enemy : first_enemies1)
			{
				if (this_enemy.isDead == false)
				{
					custext1.Show(window, "Wave 1", 80, 200, 200, 2, true, 0.1);

					if (someone_is_alive == false)
						someone_is_alive = true;
					this_enemy.move(300);
					this_enemy.fireBullet(yuri, 6800, 5500, 400);
					this_enemy.fireMissile(yuri, 4600, 4500, 410);
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
					this_enemy.move(300);
					this_enemy.fireBullet(yuri, 6800, 3500, 400);
					this_enemy.fireMissile(yuri, 4600, 4500, 410);
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
						this_enemy.move(300);
						this_enemy.fireBullet(yuri, 6800, 3500, 400);
						this_enemy.fireMissile(yuri, 4600, 4500, 410);
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
						this_enemy.move(320);
						this_enemy.fireBullet(yuri, 3800, 3500, 450);
						this_enemy.fireMissile(yuri, 4600, 4500, 410);
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
						this_enemy.move(320);
						this_enemy.fireBullet(yuri, 3800, 3500, 450);
						this_enemy.fireMissile(yuri, 4600, 4500, 410);
						levelhelp.isHitBody(yuri, this_enemy);
						levelhelp.isHitBullet(yuri, this_enemy);
						levelhelp.isHitMissile(yuri, this_enemy);
						this_enemy.Show(window);
					}
				}
			}

			if (inverseStart > yuri.healthValue && yuri.isDead == false)
			{
				if (inverseEnd > yuri.healthValue)
				{
					cout << "normal at: " << yuri.healthValue << endl;
					inversed = false;
				}
				else
				{
					custext4.Show(window, "Malfunction: Movement controls inversed.", 40, 20, 120, -1, true, 0.01);
					if (custext4.fullShowed)
					{
						cout << "inverting at: " << yuri.healthValue << endl;
						inversed = true;
					}
				}
			}

			yuri.Show(window);
			if (Helper::enemiesDied() == 14)
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
