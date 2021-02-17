#include "Boss.hpp"
#include "GetRes.hpp"
#include "Helper.hpp"

using namespace std;
using namespace sf;

void Boss::Show(RenderWindow& window)
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

		enemySprite.setTexture(*chosenTexture);
		enemySprite.setTextureRect(enemyRect);
		enemyClock.restart();
	}

	for (auto& bullet : bulletsLeft)
	{
		if (bullet.shootingStyle == Circle)
		{
			if (bullet.shouldStopCircling == false)
			{
				temp = sqrt(
						   (bullet.radius * bullet.radius) - ((bullet.sprite.getPosition().y + Helper::SecondsPerFrame() * bullet.speed / 2.0 * bullet.y_sign) - bullet.center_y) * ((bullet.sprite.getPosition().y + Helper::SecondsPerFrame() * bullet.speed / 2.0 * bullet.y_sign) - bullet.center_y))
					+ bullet.center_x;
				temp = temp - bullet.sprite.getPosition().x;
				if (abs(bullet.sprite.getPosition().y + bullet.y_sign * bullet.speed * Helper::SecondsPerFrame() / 2.0 - bullet.playerPos.y) <= 10.0)
				{
					bullet.shouldStopCircling = true;
				}
			}
			else
			{
				temp = -1.0 * Helper::SecondsPerFrame() * bullet.speed;
			}
			bullet.sprite.setRotation(Helper::getRotation(bullet.sprite.getPosition().x + temp, bullet.sprite.getPosition().y + bullet.y_sign * bullet.speed * Helper::SecondsPerFrame() / 2.0, bullet.sprite.getPosition().x, bullet.sprite.getPosition().y) - 90);
			bullet.sprite.move(temp, bullet.y_sign * bullet.speed * Helper::SecondsPerFrame() / 2.0);
		}
		else if (bullet.shootingStyle == ToPlayer)
		{
			bullet.sprite.move(bullet.velocity * Helper::SecondsPerFrame());
		}
		else // sine
		{
			bullet.sprite.move(sin(bullet.rotation) * 100 * Helper::SecondsPerFrame(), bullet.speed * Helper::SecondsPerFrame());
			bullet.rotation += 400 * Helper::SecondsPerFrame() * pi / 180.0;
		}
	}
	bulletsLeft.erase(remove_if(bulletsLeft.begin(), bulletsLeft.end(), Boss::shouldRemoveBullet), bulletsLeft.end());

	for (auto& bullet : bulletsRight)
	{
		if (bullet.shootingStyle == Circle)
		{
			if (bullet.shouldStopCircling == false)
			{
				temp = -sqrt(
						   (bullet.radius * bullet.radius) - ((bullet.sprite.getPosition().y + Helper::SecondsPerFrame() * bullet.speed / 2.0 * bullet.y_sign) - bullet.center_y) * ((bullet.sprite.getPosition().y + Helper::SecondsPerFrame() * bullet.speed / 2.0 * bullet.y_sign) - bullet.center_y))
					+ bullet.center_x;
				// cout << "tempb: " << temp << endl;
				temp = temp - bullet.sprite.getPosition().x;
				// cout << "tempa: " << temp << endl;
				if (abs(bullet.sprite.getPosition().y + bullet.y_sign * bullet.speed * Helper::SecondsPerFrame() / 2.0 - bullet.playerPos.y) <= 10.0)
				{
					bullet.shouldStopCircling = true;
				}
			}
			else
			{
				temp = 1.0 * Helper::SecondsPerFrame() * bullet.speed;
			}
			bullet.sprite.setRotation(Helper::getRotation(bullet.sprite.getPosition().x + temp, bullet.sprite.getPosition().y + bullet.y_sign * bullet.speed * Helper::SecondsPerFrame() / 2.0, bullet.sprite.getPosition().x, bullet.sprite.getPosition().y) - 90);

			bullet.sprite.move(temp, bullet.y_sign * bullet.speed * Helper::SecondsPerFrame() / 2.0);
		}
		else if (bullet.shootingStyle == ToPlayer)
		{
			bullet.sprite.move(bullet.velocity * Helper::SecondsPerFrame());
		}
		else // sine
		{
			bullet.sprite.move(sin(bullet.rotation) * 100 * Helper::SecondsPerFrame(), bullet.speed * Helper::SecondsPerFrame());
			bullet.rotation += 400 * Helper::SecondsPerFrame() * pi / 180.0;
		}
	}
	bulletsRight.erase(remove_if(bulletsRight.begin(), bulletsRight.end(), Boss::shouldRemoveBullet), bulletsRight.end());

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
		if (missile.shootingStyle == ShootingType::Circle)
		{
			if (missile.shouldStopCircling == false)
			{
				temp = missile.sign * sqrt((missile.radius * missile.radius) - ((missile.sprite.getPosition().y + Helper::SecondsPerFrame() * missile.speed / 2.0 * missile.y_sign) - missile.center_y) * ((missile.sprite.getPosition().y + Helper::SecondsPerFrame() * missile.speed / 2.0 * missile.y_sign) - missile.center_y))
					+ missile.center_x;
				temp = temp - missile.sprite.getPosition().x;
				if (abs(missile.sprite.getPosition().y + missile.y_sign * missile.speed * Helper::SecondsPerFrame() / 2.0 - missile.playerPos.y) <= 10.0)
				{
					missile.shouldStopCircling = true;
				}
			}
			else
			{
				temp = missile.sign * -1.0 * Helper::SecondsPerFrame() * missile.speed;
			}
			missile.sprite.setRotation(Helper::getRotation(missile.sprite.getPosition().x + temp, missile.sprite.getPosition().y + missile.y_sign * missile.speed * Helper::SecondsPerFrame() / 2.0, missile.sprite.getPosition().x, missile.sprite.getPosition().y) - 90);
			missile.sprite.move(temp, missile.y_sign * missile.speed * Helper::SecondsPerFrame() / 2.0);
		}
		else if (missile.shootingStyle == ShootingType::ToPlayer)
		{
			missile.sprite.move(missile.velocity * Helper::SecondsPerFrame());
		}
		else // sine
		{
			missile.sprite.move(sin(missile.rotation) * 100 * Helper::SecondsPerFrame(), missile.speed * Helper::SecondsPerFrame());
			missile.rotation += 400 * Helper::SecondsPerFrame() * pi / 180.0;
		}
	}
	missiles.erase(remove_if(missiles.begin(), missiles.end(), Boss::shouldRemoveMissile), missiles.end());

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

	explosions.erase(remove_if(explosions.begin(), explosions.end(), Boss::shouldRemoveExplosion), explosions.end());

	for (auto& explosion : explosions)
	{
		window.draw(explosion.sprite);
	}
}

void Boss::fireBullet(Player& player, int interval_milliseconds, int interval_offset, float speed)
{

	// fireBulletCircle(player, interval_milliseconds, interval_offset, speed);
	// return;
	// fireBulletSine(player, interval_milliseconds, interval_offset, speed);

	switch (rand() % 3)
	{
		case 0:
			fireBulletCircle(player, interval_milliseconds, interval_offset, speed);
			break;
		case 1:
			fireBulletSine(player, interval_milliseconds, interval_offset, speed);
			break;
		case 2:
			fireBulletToPlayer(player, interval_milliseconds, interval_offset, speed);
			break;
		default:
			break;
	}
}

void Boss::fireMissile(Player& player, int interval_milliseconds, int interval_offset, float speed)
{

	// fireMissileCircle(player, interval_milliseconds, interval_offset, speed);
	// return;
	switch (rand() % 3)
	{
		case 0:
			fireMissileToPlayer(player, interval_milliseconds, interval_offset, speed);
			break;
		case 1:
			fireMissileSine(player, interval_milliseconds, interval_offset, speed);
			break;
		case 2:
			fireMissileCircle(player, interval_milliseconds, interval_offset, speed);
			break;
		default:
			break;
	}
}

void Boss::fireBulletCircle(Player& player, int interval_milliseconds, int interval_offset, float speed) // we don't need the player. we included it for easier level management
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
			bulletLeft.shootingStyle = Circle;
			bulletLeft.playerPos = Vector2f(Helper::randRange(player.playerSprite.getGlobalBounds().left, player.playerSprite.getGlobalBounds().left + player.playerSprite.getGlobalBounds().width),
				Helper::randRange(player.playerSprite.getGlobalBounds().top, player.playerSprite.getGlobalBounds().top + player.playerSprite.getGlobalBounds().height)); // stores where to shoot
			bulletLeft.sprite.setPosition(enemySprite.getGlobalBounds().left + enemySprite.getGlobalBounds().width / 8.0, enemySprite.getGlobalBounds().top + enemySprite.getGlobalBounds().height / 2.0);
			bulletLeft.speed = speed;

			bulletLeft.shouldStopCircling = false;
			bulletLeft.center_x = bulletLeft.sprite.getPosition().x;
			bulletLeft.center_y = (bulletLeft.playerPos.y + bulletLeft.sprite.getPosition().y) / 2.0;
			bulletLeft.radius = abs(bulletLeft.sprite.getPosition().y - bulletLeft.center_y);

			if (bulletLeft.sprite.getPosition().y < bulletLeft.playerPos.y)
			{
				bulletLeft.y_sign = 1;
			}
			else
			{
				bulletLeft.y_sign = -1;
			}

			bulletsLeft.push_back(bulletLeft);

			bulletRight.shootingStyle = Circle;
			bulletRight.playerPos = Vector2f(Helper::randRange(player.playerSprite.getGlobalBounds().left, player.playerSprite.getGlobalBounds().left + player.playerSprite.getGlobalBounds().width),
				Helper::randRange(player.playerSprite.getGlobalBounds().top, player.playerSprite.getGlobalBounds().top + player.playerSprite.getGlobalBounds().height)); // stores where to shoot
			bulletRight.sprite.setPosition(enemySprite.getGlobalBounds().left + enemySprite.getGlobalBounds().width * 7.0 / 8.0, enemySprite.getGlobalBounds().top + enemySprite.getGlobalBounds().height / 2.0);
			bulletRight.speed = speed;

			bulletRight.shouldStopCircling = false;
			bulletRight.center_x = bulletRight.sprite.getPosition().x;
			bulletRight.center_y = (bulletRight.playerPos.y + bulletRight.sprite.getPosition().y) / 2.0;
			bulletRight.radius = abs(bulletRight.sprite.getPosition().y - bulletRight.center_y);

			if (bulletRight.sprite.getPosition().y < bulletRight.playerPos.y)
			{
				bulletRight.y_sign = 1;
			}
			else
			{
				bulletRight.y_sign = -1;
			}

			bulletsRight.push_back(bulletRight);
			bulletClock.restart();
			isBulletIntervalSet = false;
			if (0)
				cout << "dummy: " << player.healthValue << endl;
		}
	}
}

void Boss::fireBulletSine(Player& player, int interval_milliseconds, int interval_offset, float speed) // we don't need the player. we included it for easier level management
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
			bulletLeft.shootingStyle = Sine;
			bulletLeft.sprite.setPosition(enemySprite.getGlobalBounds().left + enemySprite.getGlobalBounds().width / 8.0, enemySprite.getGlobalBounds().top + enemySprite.getGlobalBounds().height / 2.0);
			bulletLeft.speed = speed;
			bulletLeft.rotation = 0;
			bulletLeft.sprite.setRotation(0);
			bulletsLeft.push_back(bulletLeft);

			bulletRight.shootingStyle = Sine;
			bulletRight.sprite.setPosition(enemySprite.getGlobalBounds().left + enemySprite.getGlobalBounds().width * 7.0 / 8.0, enemySprite.getGlobalBounds().top + enemySprite.getGlobalBounds().height / 2.0);
			bulletRight.speed = speed;
			bulletRight.rotation = 0;
			bulletRight.sprite.setRotation(0);
			bulletsRight.push_back(bulletRight);
			bulletClock.restart();
			isBulletIntervalSet = false;
			if (0)
				cout << "dummy: " << player.healthValue << endl;
		}
	}
}

void Boss::fireBulletToPlayer(Player& player, int interval_milliseconds, int interval_offset, float speed)
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
			bulletLeft.shootingStyle = ToPlayer;
			bulletLeft.sprite.setPosition(enemySprite.getGlobalBounds().left + enemySprite.getGlobalBounds().width / 8.0, enemySprite.getGlobalBounds().top + enemySprite.getGlobalBounds().height / 2.0);
			bulletLeft.sprite.setOrigin(bulletLeft.sprite.getGlobalBounds().width / 2, 0);

			tempVect = Vector2f(Helper::randRange(player.playerSprite.getGlobalBounds().left, player.playerSprite.getGlobalBounds().left + player.playerSprite.getGlobalBounds().width),
				Helper::randRange(player.playerSprite.getGlobalBounds().top, player.playerSprite.getGlobalBounds().top + player.playerSprite.getGlobalBounds().height)); // stores where to shoot

			bulletLeft.velocity = Helper::getNormalizedVector(tempVect, bulletLeft.sprite.getPosition());
			bulletLeft.sprite.setRotation(Helper::getRotation(tempVect.x, tempVect.y, bulletLeft.sprite.getPosition().x, bulletLeft.sprite.getPosition().y) - 90); // 'rotation - 90', since sprite texture is vertical by default
			bulletLeft.velocity *= speed;
			bulletsLeft.push_back(bulletLeft);
			bulletRight.shootingStyle = ToPlayer;
			bulletRight.sprite.setPosition(enemySprite.getGlobalBounds().left + enemySprite.getGlobalBounds().width * 7.0 / 8.0, enemySprite.getGlobalBounds().top + enemySprite.getGlobalBounds().height / 2.0);
			bulletRight.sprite.setOrigin(bulletRight.sprite.getGlobalBounds().width / 2, 0);

			tempVect = Vector2f(Helper::randRange(player.playerSprite.getGlobalBounds().left, player.playerSprite.getGlobalBounds().left + player.playerSprite.getGlobalBounds().width),
				Helper::randRange(player.playerSprite.getGlobalBounds().top, player.playerSprite.getGlobalBounds().top + player.playerSprite.getGlobalBounds().height)); // stores where to shoot

			bulletRight.velocity = Helper::getNormalizedVector(tempVect, bulletRight.sprite.getPosition());
			bulletRight.sprite.setRotation(Helper::getRotation(tempVect.x, tempVect.y, bulletRight.sprite.getPosition().x, bulletRight.sprite.getPosition().y) - 90); // 'rotation - 90', since sprite texture is vertical by default
			bulletRight.velocity *= speed;
			bulletsRight.push_back(bulletRight);
			bulletClock.restart();
			isBulletIntervalSet = false;
		}
	}
}

void Boss::fireMissileSine(Player& player, int interval_milliseconds, int interval_offset, float speed) // we don't need the player. we included it for easier level management
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
				missile.shootingStyle = Sine;
				missile.sprite.setPosition(enemySprite.getPosition().x + enemySprite.getGlobalBounds().width / 2 - 5, enemySprite.getPosition().y + 40);
				missile.speed = speed;
				missile.rotation = 0;
				missile.sprite.setRotation(0);
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

void Boss::fireMissileToPlayer(Player& player, int interval_milliseconds, int interval_offset, float speed)
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
				missile.shootingStyle = ToPlayer;
				missile.sprite.setPosition(enemySprite.getPosition().x + enemySprite.getGlobalBounds().width / 2 - 5, enemySprite.getPosition().y + 40);
				missile.sprite.setOrigin(missile.sprite.getGlobalBounds().width / 2, 0);

				tempVect = Vector2f(Helper::randRange(player.playerSprite.getGlobalBounds().left, player.playerSprite.getGlobalBounds().left + player.playerSprite.getGlobalBounds().width),
					Helper::randRange(player.playerSprite.getGlobalBounds().top, player.playerSprite.getGlobalBounds().top + player.playerSprite.getGlobalBounds().height)); // stores where to shoot

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

void Boss::fireMissileCircle(Player& player, int interval_milliseconds, int interval_offset, float speed) // we don't need the player. we included it for easier level management
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
				missile.shootingStyle = Circle;
				missile.playerPos = Vector2f(Helper::randRange(player.playerSprite.getGlobalBounds().left, player.playerSprite.getGlobalBounds().left + player.playerSprite.getGlobalBounds().width),
					Helper::randRange(player.playerSprite.getGlobalBounds().top, player.playerSprite.getGlobalBounds().top + player.playerSprite.getGlobalBounds().height)); // stores where to shoot
				missile.sprite.setPosition(enemySprite.getPosition().x + enemySprite.getGlobalBounds().width / 2 - 5, enemySprite.getPosition().y + 40);
				missile.speed = speed;

				missile.shouldStopCircling = false;
				missile.center_x = missile.sprite.getPosition().x;
				missile.center_y = (missile.playerPos.y + missile.sprite.getPosition().y) / 2.0;
				missile.radius = abs(missile.sprite.getPosition().y - missile.center_y);

				if (missile.sprite.getPosition().y < missile.playerPos.y)
				{
					missile.y_sign = 1;
				}
				else
				{
					missile.y_sign = -1;
				}

				if (bool(rand() % 2) == true)
				{
					missile.sign = 1;
				}
				else
				{
					missile.sign = -1;
				}
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

void Boss::move(float speed)
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
