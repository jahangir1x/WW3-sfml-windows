#include "Enemy4.hpp"
#include "GetRes.hpp"
#include "Helper.hpp"

using namespace std;
using namespace sf;

void Enemy4::Show(RenderWindow& window)
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
		bullet.sprite.move(bullet.velocity * Helper::SecondsPerFrame());
	}
	bulletsLeft.erase(remove_if(bulletsLeft.begin(), bulletsLeft.end(), Enemy4::shouldRemoveBullet), bulletsLeft.end());

	for (auto& bullet : bulletsRight)
	{
		bullet.sprite.move(bullet.velocity * Helper::SecondsPerFrame());
	}
	bulletsRight.erase(remove_if(bulletsRight.begin(), bulletsRight.end(), Enemy4::shouldRemoveBullet), bulletsRight.end());

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
		missile.sprite.move(missile.velocity * Helper::SecondsPerFrame());
	}
	missiles.erase(remove_if(missiles.begin(), missiles.end(), Enemy4::shouldRemoveMissile), missiles.end());

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

	explosions.erase(remove_if(explosions.begin(), explosions.end(), Enemy4::shouldRemoveExplosion), explosions.end());

	for (auto& explosion : explosions)
	{
		window.draw(explosion.sprite);
	}
}

void Enemy4::fireBullet(Player& player, int interval_milliseconds, int interval_offset, float speed)
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
			bulletLeft.sprite.setPosition(enemySprite.getGlobalBounds().left + enemySprite.getGlobalBounds().width / 8.0, enemySprite.getGlobalBounds().top + enemySprite.getGlobalBounds().height / 2.0);
			bulletLeft.sprite.setOrigin(bulletLeft.sprite.getGlobalBounds().width / 2, 0);

			tempVect = Vector2f(Helper::randRange(player.playerSprite.getGlobalBounds().left - player.playerSprite.getGlobalBounds().width, player.playerSprite.getGlobalBounds().left + player.playerSprite.getGlobalBounds().width * 2),
				Helper::randRange(player.playerSprite.getGlobalBounds().top - player.playerSprite.getGlobalBounds().height, player.playerSprite.getGlobalBounds().top + player.playerSprite.getGlobalBounds().height * 2)); // stores where to shoot

			bulletLeft.velocity = Helper::getNormalizedVector(tempVect, bulletLeft.sprite.getPosition());
			bulletLeft.sprite.setRotation(Helper::getRotation(tempVect.x, tempVect.y, bulletLeft.sprite.getPosition().x, bulletLeft.sprite.getPosition().y) - 90); // 'rotation - 90', since sprite texture is vertical by default
			bulletLeft.velocity *= speed;
			bulletsLeft.push_back(bulletLeft);
			bulletRight.sprite.setPosition(enemySprite.getGlobalBounds().left + enemySprite.getGlobalBounds().width * 7.0 / 8.0, enemySprite.getGlobalBounds().top + enemySprite.getGlobalBounds().height / 2.0);
			bulletRight.sprite.setOrigin(bulletRight.sprite.getGlobalBounds().width / 2, 0);

			tempVect = Vector2f(Helper::randRange(player.playerSprite.getGlobalBounds().left - player.playerSprite.getGlobalBounds().width, player.playerSprite.getGlobalBounds().left + player.playerSprite.getGlobalBounds().width * 2),
				Helper::randRange(player.playerSprite.getGlobalBounds().top - player.playerSprite.getGlobalBounds().height, player.playerSprite.getGlobalBounds().top + player.playerSprite.getGlobalBounds().height * 2)); // stores where to shoot

			bulletRight.velocity = Helper::getNormalizedVector(tempVect, bulletRight.sprite.getPosition());
			bulletRight.sprite.setRotation(Helper::getRotation(tempVect.x, tempVect.y, bulletRight.sprite.getPosition().x, bulletRight.sprite.getPosition().y) - 90); // 'rotation - 90', since sprite texture is vertical by default
			bulletRight.velocity *= speed;
			bulletsRight.push_back(bulletRight);
			bulletClock.restart();
			isBulletIntervalSet = false;
		}
	}
}

void Enemy4::fireMissile(Player& player, int interval_milliseconds, int interval_offset, float speed)
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
				missile.sprite.setOrigin(missile.sprite.getGlobalBounds().width / 2, 0);

				tempVect = Vector2f(Helper::randRange(player.playerSprite.getGlobalBounds().left - player.playerSprite.getGlobalBounds().width, player.playerSprite.getGlobalBounds().left + player.playerSprite.getGlobalBounds().width * 2),
					Helper::randRange(player.playerSprite.getGlobalBounds().top - player.playerSprite.getGlobalBounds().height, player.playerSprite.getGlobalBounds().top + player.playerSprite.getGlobalBounds().height * 2)); // stores where to shoot

				missile.velocity = Helper::getNormalizedVector(tempVect, missile.sprite.getPosition());
				missile.sprite.setRotation(Helper::getRotation(tempVect.x, tempVect.y, missile.sprite.getPosition().x, missile.sprite.getPosition().y) - 90); // 'rotation - 90', since sprite texture is vertical by default
				missile.velocity *= speed;
				missiles.push_back(missile);
				missileClock.restart();
				missileCount--;
				isMissileIntervalSet = false;
			}
		}
	}
}

void Enemy4::move(float speed)
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
		else if (Helper::pointsDistance(enemySprite.getGlobalBounds().left, enemySprite.getGlobalBounds().top, movePos.x, movePos.y) > 20)
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
			moveInit = false;
		}
	}
}