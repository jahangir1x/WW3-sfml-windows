#include "LevelInversed4.hpp" // level header file
using namespace std;
using namespace sf;

void LevelInversed4::Show(RenderWindow& window, Event& event)
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
		bool someone_is_alive;
		vector<Enemy1> first_enemies1(2);
		vector<Enemy2> first_enemies2(2);
		vector<Enemy3> first_enemies3(2);
		vector<Enemy3> second_enemies1(3);
		vector<Enemy6> second_enemies2(4);
		vector<Enemy5> third_enemies1(4);
		vector<Enemy1> third_enemies2(3);
		vector<Enemy4> third_enemies3(1);
		vector<Enemy4> fourth_enemies1(3);
		vector<Enemy1> fourth_enemies2(3);
		vector<Enemy2> fourth_enemies3(2);

		bool inversed = false;
		float playerHealth = 90;
		bool isHit = false;

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
					this_enemy.move(380);
					this_enemy.fireBullet(yuri, 3800, 3500, 750);
					this_enemy.fireMissile(yuri, 5000, 3000, 720);
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
					this_enemy.move(380);
					this_enemy.fireBullet(yuri, 3800, 3500, 750);
					this_enemy.fireMissile(yuri, 5000, 3000, 720);
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
					this_enemy.move(380);
					this_enemy.fireBullet(yuri, 3800, 3500, 750);
					this_enemy.fireMissile(yuri, 5000, 3000, 720);
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
						this_enemy.move(380);
						this_enemy.fireBullet(yuri, 3800, 3500, 750);
						this_enemy.fireMissile(yuri, 5000, 3000, 720);
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
						this_enemy.move(380);
						this_enemy.fireBullet(yuri, 3800, 3500, 750);
						this_enemy.fireMissile(yuri, 5000, 3000, 720);
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
						this_enemy.move(380);
						this_enemy.fireBullet(yuri, 3800, 3500, 750);
						this_enemy.fireMissile(yuri, 5000, 3000, 720);
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
						this_enemy.move(380);
						this_enemy.fireBullet(yuri, 3800, 3500, 750);
						this_enemy.fireMissile(yuri, 5000, 3000, 720);
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
						this_enemy.move(380);
						this_enemy.fireBullet(yuri, 3800, 3500, 750);
						this_enemy.fireMissile(yuri, 5000, 3000, 720);
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
						this_enemy.move(380);
						this_enemy.fireBullet(yuri, 3800, 3500, 750);
						this_enemy.fireMissile(yuri, 5000, 3000, 720);
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
						this_enemy.move(380);
						this_enemy.fireBullet(yuri, 3800, 3500, 750);
						this_enemy.fireMissile(yuri, 5000, 3000, 720);
						levelhelp.isHitBody(yuri, this_enemy);
						levelhelp.isHitBullet(yuri, this_enemy);
						levelhelp.isHitMissile(yuri, this_enemy);
						this_enemy.Show(window);
					}
				}

				for (auto& this_enemy : fourth_enemies3)
				{
					if (this_enemy.isDead == false)
					{
						if (someone_is_alive == false)
							someone_is_alive = true;
						this_enemy.move(380);
						this_enemy.fireBullet(yuri, 3800, 3500, 750);
						this_enemy.fireMissile(yuri, 5000, 3000, 720);
						levelhelp.isHitBody(yuri, this_enemy);
						levelhelp.isHitBullet(yuri, this_enemy);
						levelhelp.isHitMissile(yuri, this_enemy);
						this_enemy.Show(window);
					}
				}
			}

			if (playerHealth > yuri.healthValue && isHit == false && yuri.isDead == false)
			{
				isHit = true;
			}

			if (isHit == true && custext4.hidingFinished == false)
			{
				custext4.Show(window, "Malfunction: Movement controls inversed.", 40, 20, 120, -1, true, 0.01);
			}

			if (custext4.fullShowed)
			{
				inversed = true;
			}

			yuri.Show(window);
			if (Helper::enemiesDied() == 8)
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
