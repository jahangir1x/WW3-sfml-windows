#include "Level105.hpp"
#include "Puzzle.hpp"// level header file
using namespace std;
using namespace sf;

void Level105::Show(RenderWindow& window, Event& event)
{
	while (LevelHelper::shouldKeepPlaying())
	{

        Puzzle puzzle;

		puzzle.make(23, 9, 0, 9, 0, 11, 10000);
		cout << "in level 105 " << endl;
		Success success;
		LevelFailed levelFailedObj;
		LevelHelper levelhelp;
		GameUI::init();
		Helper::resetEnemyDiedCounter();
		Player::resetMissileCounter();
		Background background;
		Player yuri;
		bool someone_is_alive;
		unsigned int i;

		CustomText custext1;
		CustomText custext2;
		CustomText custext3;

		vector<Enemy5> first_enemies(1);  // create 2 enemies
		for (auto& enemy : first_enemies)
		{
			enemy.setStyle(Enemy3::Style::GreenGwen);
			enemy.enemySprite.setScale(1,1);
			enemy.bulletLeft.sprite.setScale(2,2);
			enemy.bulletRight.sprite.setScale(2,2);
			enemy.missile.sprite.setScale(1.5,1.5);
			enemy.bigExplosion.sprite.setScale(2,2);
			enemy.bulletDamage=20;
			enemy.missileDamage=30;
			enemy.healthValue=500;

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
				if (this_enemy.isDead == false)
				{
				    custext1.Show(window,"Behold! it's Geyhatu!", 80, 200, 200, 2,true,0.1);
					cout << "first " << endl;
					if (someone_is_alive == false)
						someone_is_alive = true;
					this_enemy.move(310);
					this_enemy.fireBullet(yuri, 500, 400, 440);
					this_enemy.fireMissile(yuri, 500, 300, 400);
					levelhelp.isHitBody(yuri, this_enemy);
					levelhelp.isHitBullet(yuri, this_enemy);
					levelhelp.isHitMissile(yuri, this_enemy);
					this_enemy.Show(window);
				}
			}



			 yuri.Show(window);

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
