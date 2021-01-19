#include "Enemy1.hpp"
#include "Helper.hpp"

using namespace std;
using namespace sf;

void Enemy1::Show(RenderWindow& window)
{
	if (enemyClock.getElapsedTime().asSeconds() > 0.2)
	{
		if (enemyRect.left == 264)
		{
			enemyRect.left = 0;
		}
		else
		{
			enemyRect.left += 88;
		}
		// cout << "left: " << playerRect.left << endl;
		enemySprite.setTexture(enemyTexture);
		enemySprite.setTextureRect(enemyRect);
		enemyClock.restart();
	}

	for (auto& bullet : bulletsLeft)
	{
		bullet.sprite.move(0, bullet.speed * Helper::SecondsPerFrame());
	}
	bulletsLeft.erase(remove_if(bulletsLeft.begin(), bulletsLeft.end(), Enemy1::shouldRemoveBullet), bulletsLeft.end());

	for (auto& bullet : bulletsRight)
	{
		bullet.sprite.move(0, bullet.speed * Helper::SecondsPerFrame());
	}
	bulletsRight.erase(remove_if(bulletsRight.begin(), bulletsRight.end(), Enemy1::shouldRemoveBullet), bulletsRight.end());

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
		missile.sprite.move(0, missile.speed * Helper::SecondsPerFrame());
	}
	missiles.erase(remove_if(missiles.begin(), missiles.end(), Enemy1::shouldRemoveMissile), missiles.end());

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

	explosions.erase(remove_if(explosions.begin(), explosions.end(), Enemy1::shouldRemoveExplosion), explosions.end());

	for (auto& explosion : explosions)
	{
		window.draw(explosion.sprite);
	}
}

void Enemy1::fireBullet(int interval_milliseconds, int interval_offset, float speed)
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
			bulletLeft.sprite.setPosition(enemySprite.getPosition().x + 16, enemySprite.getPosition().y + 60);
			bulletLeft.speed = speed;
			bulletsLeft.push_back(bulletLeft);
			bulletRight.sprite.setPosition(enemySprite.getPosition().x + 66, enemySprite.getPosition().y + 60);
			bulletRight.speed = speed;
			bulletsRight.push_back(bulletRight);
			bulletClock.restart();
			isBulletIntervalSet = false;
		}
	}
}

void Enemy1::fireMissile(int interval_milliseconds, int interval_offset, float speed)
{
	if (!isDying)
	{
		if (missile.missileCount > 0)
		{
			if (!isMissileIntervalSet)
			{
				missileInterval = Helper::randRange(interval_milliseconds - interval_offset, interval_milliseconds + interval_offset);
				isMissileIntervalSet = true;
			}
			else if (missileClock.getElapsedTime().asMilliseconds() > missileInterval)
			{
				missile.sprite.setPosition(enemySprite.getPosition().x + enemyRect.width / 2 - 5, enemySprite.getPosition().y + 40);
				missile.speed = speed;
				missiles.push_back(missile);
				missileClock.restart();
				missile.missileCount--;
				isMissileIntervalSet = false;
			}
		}
	}
}

void Enemy1::move(float speed)
{
	if (!firstTime)
	{
		if (!isDying)
		{
			if (moveInit == false)
			{
				movePos.x = Helper::randRange(0, Helper::windowWidth() - enemySprite.getGlobalBounds().width);
				movePos.y = Helper::randRange(0, Helper::windowHeight() - (enemySprite.getGlobalBounds().height * 4));

				moveNorm = Helper::getNormalizedVector(movePos, enemySprite.getPosition());
				moveNorm *= Helper::SecondsPerFrame() * speed;

				enemySprite.move(moveNorm);
				for (auto& explosion : explosions)
				{
					explosion.sprite.move(moveNorm);
				}
				moveClock.restart();
				moveInit = true;
			}
			else
			{
				if (Helper::pointsDistance(enemySprite.getGlobalBounds().left, enemySprite.getGlobalBounds().top, movePos.x, movePos.y) > 6 && moveFin == false)
				{
					// moveNorm = Helper::getNormalizedVector(movePos, enemySprite.getPosition());
					// moveNorm.x *= Helper::SecondsPerFrame() * speed;
					// moveNorm.y *= Helper::SecondsPerFrame() * speed;
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
	else
	{
		firstTime = false;
	}
}