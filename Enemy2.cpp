#include "Enemy2.hpp" // fix level with intervals

#include "Collision.h"
#include "GameHandler.hpp"
#include "Helper.hpp"
#include "LevelFailed.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <bits/stdc++.h>
using namespace std;
using namespace sf;

Enemy2::Enemy2()
{
	srand(time(NULL));

	enemy1Texture.loadFromFile("res/enemy1_spritesheet.png");
	enemy1Sprite.setTexture(enemy1Texture);
	rect.left = 0;
	rect.top = 0;
	rect.height = 118;
	rect.width = 88;
	enemy1Sprite.setTextureRect(rect);
	enemy1Sprite.setPosition(Helper::windowWidth() / 2 - rect.width / 2, Helper::windowHeight() - rect.height - 30);

	explosion.texture.loadFromFile("res/explosion.png");
	explosion.sprite.setTexture(explosion.texture);
	explosion.rect.left = 0;
	explosion.rect.top = 0;
	explosion.rect.height = 65;
	explosion.rect.width = 51;
	explosion.sprite.setTextureRect(explosion.rect);

	bigExplosion.sprite.setTexture(explosion.texture);
	bigExplosion.rect.left = 0;
	bigExplosion.rect.top = 0;
	bigExplosion.rect.height = 65;
	bigExplosion.rect.width = 51;
	bigExplosion.sprite.setTextureRect(explosion.rect);

	healthValue = 100;
	bulletInterval = 0.8;
	missileInterval = 1.5;
	isDead = false;
	isDying = false;
	moveInit = false;
	moveFin = false;
	moveLeftFin = true;
	moveRightFin = false;
	shouldDisappear = false;
	shouldExplode = false;
	bulletDamage = 5;
	missileDamage = 8;
	hitBodyDamage = 9;

	bulletLeft.speed = 500;
	bulletLeft.texture.loadFromFile("res/enemy1_bullet.png");
	bulletLeft.sprite.setTexture(bulletLeft.texture);

	bulletRight.speed = 500;
	bulletRight.texture.loadFromFile("res/enemy1_bullet.png");
	bulletRight.sprite.setTexture(bulletRight.texture);

	missile.speed = 400;
	missile.texture.loadFromFile("res/enemy1_missile.png");
	missile.sprite.setTexture(missile.texture);
	missile.missileCount = 9;
}

void Enemy2::Show(RenderWindow& window)
{
	if (enemy1Clock.getElapsedTime().asSeconds() > 0.2)
	{
		if (rect.left == 264)
		{
			rect.left = 0;
		}
		else
		{
			rect.left += 88;
		}
		// cout << "left: " << playerRect.left << endl;
		enemy1Sprite.setTexture(enemy1Texture);
		enemy1Sprite.setTextureRect(rect);
		enemy1Clock.restart();
	}

	for (i = 0; i < bulletsLeft.size(); i++)
	{
		bulletsLeft[i].sprite.move(0, bulletsLeft[i].speed * Helper::SecondsPerFrame());
		if (bulletsLeft[i].sprite.getPosition().x < 0 || bulletsLeft[i].sprite.getPosition().x > Helper::windowWidth() || bulletsLeft[i].sprite.getPosition().y < 0 || bulletsLeft[i].sprite.getPosition().y > Helper::windowHeight())
		{
			bulletsLeft.erase(bulletsLeft.begin() + i);
		}
		bulletsRight[i].sprite.move(0, bulletsRight[i].speed * Helper::SecondsPerFrame());
		if (bulletsRight[i].sprite.getPosition().x < 0 || bulletsRight[i].sprite.getPosition().x > Helper::windowWidth() || bulletsRight[i].sprite.getPosition().y < 0 || bulletsRight[i].sprite.getPosition().y > Helper::windowHeight())
		{
			bulletsRight.erase(bulletsRight.begin() + i);
		}
	}

	for (i = 0; i < bulletsLeft.size(); i++)
	{
		window.draw(bulletsLeft[i].sprite);
		window.draw(bulletsRight[i].sprite);
	}

	for (i = 0; i < missiles.size(); i++)
	{
		missiles[i].sprite.move(0, missiles[i].speed * Helper::SecondsPerFrame());
		if (missiles[i].sprite.getPosition().x < 0 || missiles[i].sprite.getPosition().x > Helper::windowWidth() || missiles[i].sprite.getPosition().y < 0 || missiles[i].sprite.getPosition().y > Helper::windowHeight())
		{
			missiles.erase(missiles.begin() + i);
		}
	}

	for (i = 0; i < missiles.size(); i++)
	{
		window.draw(missiles[i].sprite);
	}
	if (!shouldDisappear)
	{
		window.draw(enemy1Sprite);
	}

	if (shouldExplode == true && isDead == false)
	{
		if (bigExplosion.rect.left >= 255)
		{
			shouldDisappear = true;
			enemy1Sprite.setColor(Color(0, 0, 0, 0));
			enemy1Sprite.setPosition(Helper::windowWidth() + 10, Helper::windowHeight() + 10);
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

	for (i = 0; i < explosions.size(); i++)
	{
		if (explosions[i].rect.left >= 306)
		{
			explosions.erase(explosions.begin() + i);
		}
		if (explosions[i].clock.getElapsedTime().asSeconds() > 0.2)
		{
			explosions[i].rect.left += 51;
			explosions[i].sprite.setTextureRect(explosions[i].rect);
			explosions[i].clock.restart();
		}
	}
	for (i = 0; i < explosions.size(); i++)
	{
		window.draw(explosions[i].sprite);
	}
}

void Enemy2::setPosition(int targetPos_x, int targetPos_y, int offset)
{

	targetPos = Vector2f(Helper::randRange(targetPos_x - offset, targetPos_x + offset), Helper::randRange(targetPos_y - offset, targetPos_y + offset));
	if (targetPos.y > -120)
		targetPos.y = -120; // since height of enemysprite is 118
	enemy1Sprite.setPosition(targetPos);
}

void Enemy2::Die()
{
	bigExplosion.sprite.setOrigin(25.5, 32.5);
	bigExplosion.sprite.setPosition(enemy1Sprite.getGlobalBounds().left + enemy1Sprite.getGlobalBounds().width / 2, enemy1Sprite.getGlobalBounds().top + enemy1Sprite.getGlobalBounds().height / 2);
	bigExplosion.sprite.setScale(3, 3);
	if (!shouldExplode)
	{
		shouldExplode = true;
	}
}

void Enemy2::fireBullet(int interval_milliseconds, int interval_offset, float speed)
{
	if (!isDying)
	{
		if (bulletClock.getElapsedTime().asMilliseconds() > Helper::randRange(interval_milliseconds - interval_offset, interval_milliseconds + interval_offset))
		{
			bulletLeft.sprite.setPosition(enemy1Sprite.getPosition().x + 16, enemy1Sprite.getPosition().y + 60);
			bulletLeft.speed = speed;
			bulletLeft.id = rand() + rand() + rand();
			bulletsLeft.push_back(bulletLeft);
			bulletRight.sprite.setPosition(enemy1Sprite.getPosition().x + 66, enemy1Sprite.getPosition().y + 60);
			bulletRight.speed = speed;
			bulletRight.id = rand() + rand() + rand();
			bulletsRight.push_back(bulletRight);
			bulletClock.restart();
		}
	}
}

void Enemy2::fireMissile(int interval_milliseconds, int interval_offset, float speed)
{
	if (!isDying)
	{
		if (missile.missileCount > 0)
		{
			if (missileClock.getElapsedTime().asMilliseconds() > Helper::randRange(interval_milliseconds - interval_offset, interval_milliseconds + interval_offset))
			{
				missile.sprite.setPosition(enemy1Sprite.getPosition().x + rect.width / 2 - 5, enemy1Sprite.getPosition().y + 40);
				missile.speed = speed;
				missile.id = rand() + rand() + rand();
				missiles.push_back(missile);
				missileClock.restart();
				missile.missileCount--;
			}
		}
	}
}

void Enemy2::fireBullet_to(Vector2f targetPos, int interval_milliseconds, int interval_offset, float speed, int offset)
{
	if (bulletClock.getElapsedTime().asMilliseconds() > Helper::randRange(interval_milliseconds - interval_offset, interval_milliseconds + interval_offset))
	{
		bulletOriginPosLeft = Vector2f(enemy1Sprite.getPosition().x + 16, enemy1Sprite.getPosition().y + 68);
		bulletLeft.sprite.setPosition(bulletOriginPosLeft);

		bulletOriginPosRight = Vector2f(enemy1Sprite.getPosition().x + 66, enemy1Sprite.getPosition().y + 68);

		bulletRight.sprite.setPosition(bulletOriginPosRight);
		bulletClock.restart();
	}
	for (i = 0; i < bulletsLeft.size(); i++)
	{
		shootPos.x = Helper::randRange(targetPos.x - offset, targetPos.x + offset);
		shootPos.y = Helper::randRange(targetPos.y - offset, targetPos.y + offset);

		tempVect = Helper::getNormalizedVector(shootPos, bulletOriginPosLeft);
		tempVect.x *= Helper::SecondsPerFrame() * speed;
		tempVect.y *= Helper::SecondsPerFrame() * speed;

		bulletsLeft[i].sprite.move(tempVect);

		if (bulletsLeft[i].sprite.getPosition().x < 0 || bulletsLeft[i].sprite.getPosition().x > Helper::windowWidth() || bulletsLeft[i].sprite.getPosition().y < 0 || bulletsLeft[i].sprite.getPosition().y > Helper::windowHeight())
		{
			bulletsLeft.erase(bulletsLeft.begin() + i);
		}

		tempVect = Helper::getNormalizedVector(shootPos, bulletOriginPosRight);
		tempVect.x *= Helper::SecondsPerFrame() * speed;
		tempVect.y *= Helper::SecondsPerFrame() * speed;

		bulletsRight[i].sprite.move(tempVect); // need to calculate vector shoot pos according to left

		if (bulletsRight[i].sprite.getPosition().x < 0 || bulletsRight[i].sprite.getPosition().x > Helper::windowWidth() || bulletsRight[i].sprite.getPosition().y < 0 || bulletsRight[i].sprite.getPosition().y > Helper::windowHeight())
		{
			bulletsRight.erase(bulletsRight.begin() + i);
		}
	}
}

void Enemy2::fireMissile_to(Vector2f targetPos, int interval_milliseconds, int interval_offset, float speed, int offset)
{
	if (missile.missileCount > 0)
	{
		if (missileClock.getElapsedTime().asMilliseconds() > Helper::randRange(interval_milliseconds - interval_offset, interval_milliseconds + interval_offset))
		{
			missileOriginPos = Vector2f(enemy1Sprite.getPosition().x + rect.width / 2 - 5, enemy1Sprite.getPosition().y + 20);
			missile.sprite.setPosition(missileOriginPos);
			missile.missileCount--;
			missileClock.restart();
		}

		for (i = 0; i < missiles.size(); i++)
		{
			shootPos.x = Helper::randRange(targetPos.x - offset, targetPos.x + offset);
			shootPos.y = Helper::randRange(targetPos.y - offset, targetPos.y + offset);

			tempVect = Helper::getNormalizedVector(shootPos, missileOriginPos);
			tempVect.x *= Helper::SecondsPerFrame() * speed;
			tempVect.y *= Helper::SecondsPerFrame() * speed;

			missiles[i].sprite.move(tempVect);
			if (missiles[i].sprite.getPosition().x < 0 || missiles[i].sprite.getPosition().x > Helper::windowWidth() || missiles[i].sprite.getPosition().y < 0 || missiles[i].sprite.getPosition().y > Helper::windowHeight())
			{
				missiles.erase(missiles.begin() + i);
			}
		}
	}
}

void Enemy2::moveDown(float speed)
{
	if (!isDying)
	{
		tempVect = Helper::getNormalizedVector(Vector2f(enemy1Sprite.getPosition().x, Helper::windowHeight() + 100), Vector2f(enemy1Sprite.getPosition().x, enemy1Sprite.getPosition().y));
		tempVect.x *= Helper::SecondsPerFrame() * speed;
		tempVect.y *= Helper::SecondsPerFrame() * speed;

		enemy1Sprite.move(tempVect);
		for (i = 0; i < explosions.size(); i++)
		{
			explosions[i].sprite.move(tempVect);
		}
	}
}

void Enemy2::moveUp(float speed)
{
	if (!isDying)
	{
		tempVect = Helper::getNormalizedVector(Vector2f(enemy1Sprite.getPosition().x, -Helper::windowHeight()), Vector2f(enemy1Sprite.getPosition().x, enemy1Sprite.getPosition().y));
		tempVect.x *= Helper::SecondsPerFrame() * speed;
		tempVect.y *= Helper::SecondsPerFrame() * speed;

		enemy1Sprite.move(tempVect);
		for (i = 0; i < explosions.size(); i++)
		{
			explosions[i].sprite.move(tempVect);
		}
	}
}

void Enemy2::moveLeft(float speed)
{
	if (!isDying)
	{
		tempVect = Helper::getNormalizedVector(Vector2f(-Helper::windowWidth(), enemy1Sprite.getPosition().y), Vector2f(enemy1Sprite.getPosition().x, enemy1Sprite.getPosition().y));
		tempVect.x *= Helper::SecondsPerFrame() * speed;
		tempVect.y *= Helper::SecondsPerFrame() * speed;

		enemy1Sprite.move(tempVect);
		for (i = 0; i < explosions.size(); i++)
		{
			explosions[i].sprite.move(tempVect);
		}
	}
}

void Enemy2::moveRight(float speed)
{
	if (!isDying)
	{
		tempVect = Helper::getNormalizedVector(Vector2f(Helper::windowWidth() + 100, enemy1Sprite.getPosition().y), Vector2f(enemy1Sprite.getPosition().x, enemy1Sprite.getPosition().y));
		tempVect.x *= Helper::SecondsPerFrame() * speed;
		tempVect.y *= Helper::SecondsPerFrame() * speed;

		enemy1Sprite.move(tempVect);
		for (i = 0; i < explosions.size(); i++)
		{
			explosions[i].sprite.move(tempVect);
		}
	}
}

void Enemy2::move(float speed)
{
	if (!isDying)
	{
		if (moveInit == false)
		{
			movePos.x = Helper::randRange(0, Helper::windowWidth() - enemy1Sprite.getGlobalBounds().width);
			movePos.y = Helper::randRange(0, Helper::windowHeight() - (enemy1Sprite.getGlobalBounds().height * 4));


			moveNorm = Helper::getNormalizedVector(movePos, enemy1Sprite.getPosition());
			moveNorm.x *= Helper::SecondsPerFrame() * speed;
			moveNorm.y *= Helper::SecondsPerFrame() * speed;

			enemy1Sprite.move(moveNorm);
			for (i = 0; i < explosions.size(); i++)
			{
				explosions[i].sprite.move(moveNorm);
			}
			moveClock.restart();
			moveInit = true;
		}
		else
		{
			if (Helper::pointsDistance(enemy1Sprite.getGlobalBounds().left, enemy1Sprite.getGlobalBounds().top, movePos.x, movePos.y) > 6 && moveFin == false)
			{
				moveNorm = Helper::getNormalizedVector(movePos, enemy1Sprite.getPosition());
				moveNorm.x *= Helper::SecondsPerFrame() * speed;
				moveNorm.y *= Helper::SecondsPerFrame() * speed;
				enemy1Sprite.move(moveNorm);
				for (i = 0; i < explosions.size(); i++)
				{
					explosions[i].sprite.move(moveNorm);
				}
			}
			else
			{
				moveFin = true;

				if (moveRightFin == false)
				{
					moveRight(speed);

					if (abs(enemy1Sprite.getGlobalBounds().left + enemy1Sprite.getGlobalBounds().width - Helper::windowWidth()) < 6)
					{
						moveLeftFin = false;
						moveRightFin = true;
					}
				}
				else if (moveLeftFin == false)
				{
					moveLeft(speed);
					if (abs(enemy1Sprite.getGlobalBounds().left - 0) < 6)
					{
						moveLeftFin = true;
						moveRightFin = false;
					}
				}
			}
		}
	}
}

void Enemy2::show_explosion_bullet(Vector2f pos)
{
	explosion.sprite.setOrigin(25.5, 32.5);
	explosion.sprite.setScale(1, 1);
	explosion.sprite.setPosition(pos);
	explosions.push_back(explosion);
}
void Enemy2::show_explosion_missile(Vector2f pos)
{
	explosion.sprite.setOrigin(25.5, 32.5);
	explosion.sprite.setScale(2, 2);
	explosion.sprite.setPosition(pos);
	explosions.push_back(explosion);
}