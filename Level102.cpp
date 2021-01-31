#include "Level102.hpp" // level header file
using namespace std;
using namespace sf;

void Level102::Show(RenderWindow& window, Event& event)
{
	while (LevelHelper::shouldKeepPlaying())
	{
		cout << "in level 102 " << endl;
		Success success;
		LevelFailed levelFailedObj;
		LevelHelper levelhelp;
		GameUI::init();
		Helper::resetEnemyDiedCounter();
		Player::resetMissileCounter();
		Background background;
		Player yuri;
		bool someone_is_alive;
		CustomText custext1;
		CustomText custext2;
		CustomText custext3;

		unsigned int i;
		vector<Enemy3> first_enemies(3);  // create 2 enemies
		vector<Enemy3> second_enemies(3); // create 3 enemies
		vector<Enemy3> third_enemies(4);

		for (auto& enemy : first_enemies)
		{
			enemy.setStyle(Enemy3::Style::RedRider);
		}
		for (auto& enemy : second_enemies)
		{
			enemy.setStyle(Enemy3::Style::PurplePunk);
		}
		for (auto& enemy : third_enemies)
		{
			enemy.setStyle(Enemy3::Style::GreenGwen);
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

			someone_is_alive = false; // আমরা চাচ্ছি প্রথমে 3 টা, তারপর ৩ টা, তারপর ৪ টা enemy একসাথে আসবে ।

			for (auto& this_enemy : first_enemies) // range based for loop + reference operator ফাস্ট হবে ।
			{
				if (this_enemy.isDead == false)
				{
					custext1.Show(window, "Wave 1", 80, 200, 200, 2, true, 0.1);
					cout << "first" << endl;
					if (someone_is_alive == false)
						someone_is_alive = true;
					this_enemy.move(300);
					this_enemy.fireBullet(yuri, 3000, 1200, 430);
					this_enemy.fireMissile(yuri, 4400, 1000, 330);
					levelhelp.isHitBody(yuri, this_enemy);
					levelhelp.isHitBullet(yuri, this_enemy);
					levelhelp.isHitMissile(yuri, this_enemy);
					this_enemy.Show(window);
				}
			}

			if (someone_is_alive == false)
			{
				for (i = 0; i < second_enemies.size(); i++)
				{
					if (custext1.hidingFinished == true)
					{
						custext2.Show(window, "Wave 2", 80, 200, 200, 2, true, 0.1);
					}
					if (second_enemies[i].isDead == false)
					{
						cout << "second" << endl;
						if (someone_is_alive == false)
							someone_is_alive = true;
						second_enemies[i].move(300);
						second_enemies[i].fireBullet(yuri, 3000, 1200, 430);
						second_enemies[i].fireMissile(yuri, 4400, 1000, 330);
						levelhelp.isHitBody(yuri, second_enemies[i]);
						levelhelp.isHitBullet(yuri, second_enemies[i]);
						levelhelp.isHitMissile(yuri, second_enemies[i]);
						second_enemies[i].Show(window);
					}
				}
			}

			if (someone_is_alive == false)
			{
				for (i = 0; i < third_enemies.size(); i++)
				{
					if (third_enemies[i].isDead == false)
					{
						if (custext2.hidingFinished == true)
						{
							custext3.Show(window, "Wave 3", 80, 200, 200, 2, true, 0.1);
						}
						cout << "third" << endl;
						if (someone_is_alive == false)
							someone_is_alive = true;
						third_enemies[i].move(290);
						third_enemies[i].fireBullet(yuri, 3000, 1200, 430);
						third_enemies[i].fireMissile(yuri, 4400, 1000, 330);
						levelhelp.isHitBody(yuri, third_enemies[i]);
						levelhelp.isHitBullet(yuri, third_enemies[i]);
						levelhelp.isHitMissile(yuri, third_enemies[i]);
						third_enemies[i].Show(window);
					}
				}
			}

			yuri.Show(window);
			if (Helper::enemiesDied() == 10)
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
