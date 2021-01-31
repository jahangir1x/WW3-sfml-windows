#include "Enemy5.hpp"
#include "GetRes.hpp"
#include "Helper.hpp"

using namespace std;
using namespace sf;

void Enemy5::Show(RenderWindow& window)
{
	if (enemyClock.getElapsedTime().asSeconds() > 0.2)
	{
		if (enemyRect.left == 510)
		{
			enemyRect.left = 0;
		}
		else
		{
			enemyRect.left += enemyRect.width;
		}
		// cout << "left: " << playerRect.left << endl;
		enemySprite.setTexture(*chosenTexture);
		enemySprite.setTextureRect(enemyRect);
		enemyClock.restart();
	}

	for (auto& bullet : bulletsLeft)
	{
		bullet.sprite.move(sin(bullet.rotation) * 100 * Helper::SecondsPerFrame(), bullet.speed * Helper::SecondsPerFrame());

		bullet.rotation += 400 * Helper::SecondsPerFrame() * pi / 180.0;
	}
	bulletsLeft.erase(remove_if(bulletsLeft.begin(), bulletsLeft.end(), Enemy5::shouldRemoveBullet), bulletsLeft.end());

	for (auto& bullet : bulletsRight)
	{
		bullet.sprite.move(sin(bullet.rotation) * 100 * Helper::SecondsPerFrame(), bullet.speed * Helper::SecondsPerFrame());
		bullet.rotation += 400 * Helper::SecondsPerFrame() * pi / 180.0;
	}
	bulletsRight.erase(remove_if(bulletsRight.begin(), bulletsRight.end(), Enemy5::shouldRemoveBullet), bulletsRight.end());

	for (auto& bullet : bulletsLeft)
	{
		window.draw(bullet.sprite);
	}

	for (auto& bullet : bulletsRight)
	{
		window.draw(bullet.sprite);
	}

	for (auto& missile : missiles)
	{
		missile.sprite.move(sin(missile.rotation) * 100 * Helper::SecondsPerFrame(), missile.speed * Helper::SecondsPerFrame());
		missile.rotation += 400 * Helper::SecondsPerFrame() * pi / 180.0;
	}
	missiles.erase(remove_if(missiles.begin(), missiles.end(), Enemy5::shouldRemoveMissile), missiles.end());

	for (auto& missile : missiles)
	{
		window.draw(missile.sprite);
	}

	if (!shouldDisappear)
	{
		window.draw(enemySprite);
	}

	if (shouldExplode == true && isDead == false)
	{
		if (bigExplosion.rect.left >= 255)
		{
			shouldDisappear = true;
			enemySprite.setPosition(Helper::windowWidth() + 10, Helper::windowHeight() + 10);
		}
		if (bigExplosionClock.getElapsedTime().asSeconds() > 0.2)
		{
			if (bigExplosion.rect.left <= 306)
			{
				bigExplosion.rect.left += 51;
			}
			else
			{
				isDead = true;
				Helper::newEnemyDied();
			}
			bigExplosion.sprite.setTextureRect(bigExplosion.rect);
			window.draw(bigExplosion.sprite);
			bigExplosionClock.restart();
		}
		window.draw(bigExplosion.sprite);
	}

	for (auto& explosion : explosions)
	{
		if (explosion.clock.getElapsedTime().asSeconds() > 0.2)
		{
			explosion.rect.left += 51;
			explosion.sprite.setTextureRect(explosion.rect);
			explosion.clock.restart();
		}
	}

	explosions.erase(remove_if(explosions.begin(), explosions.end(), Enemy5::shouldRemoveExplosion), explosions.end());

	for (auto& explosion : explosions)
	{
		window.draw(explosion.sprite);
	}
}

void Enemy5::fireBullet(Player& player, int interval_milliseconds, int interval_offset, float speed) // we don't need the player. we included it for easier level management
{

	if (!isDying)
	{
		if (!isBulletIntervalSet)
		{
			bulletInterval = Helper::randRange(interval_milliseconds - interval_offset, interval_milliseconds + interval_offset);
			isBulletIntervalSet = true;
		}
		else if (bulletClock.getElapsedTime().asMilliseconds() > bulletInterval)
		{
			if (isMute == false)
			{
				bulletSound.play();
			}
			bulletLeft.sprite.setPosition(enemySprite.getPosition().x + 16, enemySprite.getPosition().y + 60);
			bulletLeft.speed = speed;
			bulletLeft.rotation = 0;
			bulletsLeft.push_back(bulletLeft);

			bulletRight.sprite.setPosition(enemySprite.getPosition().x + 66, enemySprite.getPosition().y + 60);
			bulletRight.speed = speed;
			bulletRight.rotation = 0;
			bulletsRight.push_back(bulletRight);
			bulletClock.restart();
			isBulletIntervalSet = false;
			if (0)
				cout << "dummy: " << player.healthValue << endl;
		}
	}
}

void Enemy5::fireMissile(Player& player, int interval_milliseconds, int interval_offset, float speed) // we don't need the player. we included it for easier level management
{

	if (!isDying)
	{
		if (missileCount > 0)
		{
			if (!isMissileIntervalSet)
			{
				missileInterval = Helper::randRange(interval_milliseconds - interval_offset, interval_milliseconds + interval_offset);
				isMissileIntervalSet = true;
			}
			else if (missileClock.getElapsedTime().asMilliseconds() > missileInterval)
			{
				if (isMute == false)
				{
					missileSound.play();
				}
				missile.sprite.setPosition(enemySprite.getPosition().x + enemySprite.getGlobalBounds().width / 2 - 5, enemySprite.getPosition().y + 40);
				missile.speed = speed;
				missile.rotation = 0;
				missiles.push_back(missile);
				missileClock.restart();
				missileCount--;
				isMissileIntervalSet = false;
				if (0) // to bypass g++ -Werror=unused-variable
					cout << "dummy: " << player.healthValue << endl;
			}
		}
	}
}

void Enemy5::move(float speed)
{

	if (!isDying)
	{
		if (moveInit == false)
		{
			movePos.x = Helper::randRange(0, Helper::windowWidth() - enemySprite.getGlobalBounds().width);
			movePos.y = Helper::randRange(0, Helper::windowHeight() - (Helper::getPlayerHeight() * 2 + enemySprite.getGlobalBounds().height)); // we don't want to collide with the player and shoot at nothing

			moveNorm = Helper::getNormalizedVector(movePos, enemySprite.getPosition());
			moveNorm *= Helper::SecondsPerFrame() * speed;

			enemySprite.move(moveNorm);
			for (auto& explosion : explosions)
			{
				explosion.sprite.move(moveNorm);
			}
			moveInit = true;
		}
		else
		{
			if (Helper::pointsDistance(enemySprite.getGlobalBounds().left, enemySprite.getGlobalBounds().top, movePos.x, movePos.y) > 6 && moveFin == false)
			{
				moveNorm = Helper::getNormalizedVector(movePos, enemySprite.getPosition());
				moveNorm *= Helper::SecondsPerFrame() * speed;

				enemySprite.move(moveNorm);
				for (auto& explosion : explosions)
				{
					explosion.sprite.move(moveNorm);
				}
			}
			else
			{
				moveFin = true;

				if (moveRightFin == false)
				{
					moveRight(speed);

					if (abs(enemySprite.getGlobalBounds().left + enemySprite.getGlobalBounds().width - Helper::windowWidth()) < 6)
					{
						moveLeftFin = false;
						moveRightFin = true;
					}
				}
				else if (moveLeftFin == false)
				{
					moveLeft(speed);
					if (abs(enemySprite.getGlobalBounds().left - 0) < 6)
					{
						moveLeftFin = true;
						moveRightFin = false;
					}
				}
			}
		}
	}
}