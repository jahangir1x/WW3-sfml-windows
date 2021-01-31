#include "Level112.hpp" // level header file
using namespace std;
using namespace sf;

void Level112::Show(RenderWindow& window, Event& event)
{
	while (LevelHelper::shouldKeepPlaying())
	{
		cout << "in level 112" << endl;
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

		vector<pair<Enemy5,Enemy5>> first_enemies(2);  // create 2 enemies
		vector<pair<Enemy4,Enemy5>> second_enemies(2); // create 3 enemies
		vector<pair<Enemy4,Enemy4>> third_enemies(2);

		for (auto& enemy : first_enemies)
		{
			enemy.first.enemySprite.setScale(0.35,0.35);
			enemy.first.bulletLeft.sprite.setScale(1,1);
			enemy.first.bulletRight.sprite.setScale(1,1);
			enemy.first.missile.sprite.setScale(0.8,0.8);
			enemy.first.bigExplosion.sprite.setScale(1,1);
			enemy.second.enemySprite.setScale(0.35,0.35);
			enemy.second.bulletLeft.sprite.setScale(1,1);
			enemy.second.bulletRight.sprite.setScale(1,1);
			enemy.second.missile.sprite.setScale(0.8,0.8);
			enemy.second.bigExplosion.sprite.setScale(1,1);

		}
		for (auto& enemy : second_enemies)
		{
			enemy.first.enemySprite.setScale(0.35,0.35);
			enemy.first.bulletLeft.sprite.setScale(1,1);
			enemy.first.bulletRight.sprite.setScale(1,1);
			enemy.first.missile.sprite.setScale(0.8,0.8);
			enemy.first.bigExplosion.sprite.setScale(1,1);
			enemy.second.enemySprite.setScale(0.35,0.35);
			enemy.second.bulletLeft.sprite.setScale(1,1);
			enemy.second.bulletRight.sprite.setScale(1,1);
			enemy.second.missile.sprite.setScale(0.8,0.8);
			enemy.second.bigExplosion.sprite.setScale(1,1);
		}
		for (auto& enemy : third_enemies)
		{
			enemy.first.enemySprite.setScale(0.35,0.35);
			enemy.first.bulletLeft.sprite.setScale(1,1);
			enemy.first.bulletRight.sprite.setScale(1,1);
			enemy.first.missile.sprite.setScale(0.8,0.8);
			enemy.first.bigExplosion.sprite.setScale(1,1);
			enemy.second.enemySprite.setScale(0.35,0.35);
			enemy.second.bulletLeft.sprite.setScale(1,1);
			enemy.second.bulletRight.sprite.setScale(1,1);
			enemy.second.missile.sprite.setScale(0.8,0.8);
			enemy.second.bigExplosion.sprite.setScale(1,1);
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

			someone_is_alive = false; // আমরা চাচ্ছি প্রথমে 4 টা, তারপর 4 টা, তারপর 5  টা enemy একসাথে আসবে ।

			for (auto& this_enemy : first_enemies) // range based for loop + reference operator ফাস্ট হবে ।
			{
				if (this_enemy.first.isDead == false || this_enemy.second.isDead==false)
				{
				    custext1.Show(window,"Wave 1", 80, 200, 200, 2,true,0.1);
					cout << "first " << endl;
					if (someone_is_alive == false)
						someone_is_alive = true;
					this_enemy.first.move(340);
					this_enemy.first.fireBullet(yuri, 1200, 800, 400);
					this_enemy.first.fireMissile(yuri, 1000, 500, 400);
					levelhelp.isHitBody(yuri, this_enemy.first);
					levelhelp.isHitBullet(yuri, this_enemy.first);
					levelhelp.isHitMissile(yuri, this_enemy.first);
					this_enemy.first.Show(window);
					this_enemy.second.move(340);
					this_enemy.second.fireBullet(yuri, 1000, 800, 400);
					this_enemy.second.fireMissile(yuri, 1000, 500, 400);
					levelhelp.isHitBody(yuri, this_enemy.second);
					levelhelp.isHitBullet(yuri, this_enemy.second);
					levelhelp.isHitMissile(yuri, this_enemy.second);
					this_enemy.second.Show(window);
				}
			}

			if (someone_is_alive == false)
			{
				for (auto& this_enemy : second_enemies) // range based for loop + reference operator ফাস্ট হবে ।
			{
				if (this_enemy.first.isDead == false || this_enemy.second.isDead==false)
				{
				    custext1.Show(window,"Wave 2", 80, 200, 200, 2,true,0.1);
					cout << "Second " << endl;
					if (someone_is_alive == false)
						someone_is_alive = true;
					this_enemy.first.move(340);
					this_enemy.first.fireBullet(yuri, 2500, 1200, 400);
					this_enemy.first.fireMissile(yuri, 1000, 500, 400);
					levelhelp.isHitBody(yuri, this_enemy.first);
					levelhelp.isHitBullet(yuri, this_enemy.first);
					levelhelp.isHitMissile(yuri, this_enemy.first);
					this_enemy.first.Show(window);
					this_enemy.second.move(340);
					this_enemy.second.fireBullet(yuri, 1000, 800, 400);
					this_enemy.second.fireMissile(yuri, 1000, 500, 400);
					levelhelp.isHitBody(yuri, this_enemy.second);
					levelhelp.isHitBullet(yuri, this_enemy.second);
					levelhelp.isHitMissile(yuri, this_enemy.second);
					this_enemy.second.Show(window);
				}
			}
			}

			if (someone_is_alive == false)
			{
				for (auto& this_enemy : third_enemies) // range based for loop + reference operator ফাস্ট হবে ।
			{
				if (this_enemy.first.isDead == false || this_enemy.second.isDead==false)
				{

                     if (custext2.hidingFinished == true)
						{
							custext3.Show(window, "Wave 3", 80, 200, 200, 2, true, 0.1);
						}
					cout << "third " << endl;
					if (someone_is_alive == false)
						someone_is_alive = true;
					this_enemy.first.move(340);
					this_enemy.first.fireBullet(yuri, 2500, 1000, 400);
					this_enemy.first.fireMissile(yuri, 3000, 500, 400);
					levelhelp.isHitBody(yuri, this_enemy.first);
					levelhelp.isHitBullet(yuri, this_enemy.first);
					levelhelp.isHitMissile(yuri, this_enemy.first);
					this_enemy.first.Show(window);
					this_enemy.second.move(340);
					this_enemy.second.fireBullet(yuri, 2500, 1000, 400);
					this_enemy.second.fireMissile(yuri, 3000, 2000, 400);
					levelhelp.isHitBody(yuri, this_enemy.second);
					levelhelp.isHitBullet(yuri, this_enemy.second);
					levelhelp.isHitMissile(yuri, this_enemy.second);
					this_enemy.second.Show(window);
				}
			}
			}

			yuri.Show(window);
			if (Helper::enemiesDied() == 12)
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
