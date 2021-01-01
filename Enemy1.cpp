#include "Enemy1.hpp" // fix level with intervals
#include "Collision.h"
#include "GameHandler.hpp"
#include "LevelFailed.hpp"
#include "helperFunc.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <bits/stdc++.h>
using namespace std;
using namespace sf;

Enemy1::Enemy1(RenderWindow& window)
{
	srand(time(NULL));
	windowSizeX = window.getSize().x;
	windowSizeY = window.getSize().y;

	enemy1Texture.loadFromFile("res/enemy1_spritesheet.png");
	enemy1Sprite.setTexture(enemy1Texture);
	rect.left = 0;
	rect.top = 0;
	rect.height = 118;
	rect.width = 88;
	enemy1Sprite.setTextureRect(rect);
	enemy1Sprite.setPosition(windowSizeX / 2 - rect.width / 2, windowSizeY - rect.height - 30);

	healthValue = 100;
	bulletInterval = 0.8;
	missileInterval = 1.5;
	isDead = false;
	bulletDamage = 5;
	missileDamage = 8;

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

void Enemy1::Show(RenderWindow& window)
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
		window.draw(bulletsLeft[i].sprite);
		window.draw(bulletsRight[i].sprite);
	}

	for (i = 0; i < missiles.size(); i++)
	{
		window.draw(missiles[i].sprite);
	}

	// cout << "missile: " << missiles.size() << endl;
	// cout << "bullets: " << bulletsLeft.size() << endl;
	window.draw(enemy1Sprite);
}

void Enemy1::isHit(Sprite& targetSprite, float damage)
{
	if (Collision::BoundingBoxTest(enemy1Sprite, targetSprite))
	{
		if (Collision::PixelPerfectTest(enemy1Sprite, targetSprite))
		{
			if (prevCollisionSprite != &targetSprite)
			{
				if (healthValue > 0)
				{
					cout << "in different" << endl;
					healthValue -= damage;
					cout << "plh: " << healthValue << endl;
					prevCollisionSprite = &targetSprite;
					hitClock.restart();
				}
				else
				{
					isDead = true;
					Die();
				}
			}
			else
			{
				if (hitClock.getElapsedTime().asSeconds() > 1.5)
				{
					if (healthValue > 0)
					{
						cout << "in same" << endl;
						healthValue -= damage;
						cout << "plh: " << healthValue << endl;
						hitClock.restart();
					}
					else
					{
						isDead = true;
						Die();
					}
				}
			}
		}
	}
	// cout << "object: " << collisionCircle.getGlobalBounds().left << " " << collisionCircle.getGlobalBounds().top << " " << collisionCircle.getGlobalBounds().width << " " << collisionCircle.getGlobalBounds().height << endl;
	// cout << "target: " << targetCircleShape.getGlobalBounds().left << " " << targetCircleShape.getGlobalBounds().top << " " << targetCircleShape.getGlobalBounds().width << " " << targetCircleShape.getGlobalBounds().height << endl;
}

void Enemy1::Die()
{
	cout << "enemy dead" << endl;
}

void Enemy1::fireBullet_to(Vector2f targetPos, int interval_milliseconds, int interval_offset, float speed, int offset)
{
	if (bulletClock.getElapsedTime().asMilliseconds() > helperFunc::randRange(interval_milliseconds - interval_offset, interval_milliseconds + interval_offset))
	{
		bulletOriginPosLeft = Vector2f(enemy1Sprite.getPosition().x + 16, enemy1Sprite.getPosition().y + 68);
		bulletLeft.sprite.setPosition(bulletOriginPosLeft);
		// bulletsLeft.push_back(bulletLeft);

		bulletOriginPosRight = Vector2f(enemy1Sprite.getPosition().x + 66, enemy1Sprite.getPosition().y + 68);

		bulletRight.sprite.setPosition(bulletOriginPosRight);
		// bulletsRight.push_back(bulletRight);
		cout << "enemy fired bullet" << endl;
		bulletClock.restart();
	}
	for (i = 0; i < bulletsLeft.size(); i++)
	{
		shootPos.x = helperFunc::randRange(targetPos.x - offset, targetPos.x + offset);
		shootPos.y = helperFunc::randRange(targetPos.y - offset, targetPos.y + offset);

		shootBulletTemp = helperFunc::getNormalizedVector(shootPos, bulletOriginPosLeft);
		shootBulletTemp.x *= gamehandler.getElapsedTime() * speed;
		shootBulletTemp.y *= gamehandler.getElapsedTime() * speed;

		bulletsLeft[i].sprite.move(shootBulletTemp);

		if (bulletsLeft[i].sprite.getPosition().x < 0 || bulletsLeft[i].sprite.getPosition().x > windowSizeX || bulletsLeft[i].sprite.getPosition().y < 0 || bulletsLeft[i].sprite.getPosition().y > windowSizeY)
		{
			bulletsLeft.erase(bulletsLeft.begin() + i);
		}

		shootBulletTemp = helperFunc::getNormalizedVector(shootPos, bulletOriginPosRight);
		shootBulletTemp.x *= gamehandler.getElapsedTime() * speed;
		shootBulletTemp.y *= gamehandler.getElapsedTime() * speed;

		bulletsRight[i].sprite.move(shootBulletTemp); // need to calculate vector shoot pos according to left

		if (bulletsRight[i].sprite.getPosition().x < 0 || bulletsRight[i].sprite.getPosition().x > windowSizeX || bulletsRight[i].sprite.getPosition().y < 0 || bulletsRight[i].sprite.getPosition().y > windowSizeY)
		{
			bulletsRight.erase(bulletsRight.begin() + i);
		}
	}
}

void Enemy1::fireMissile_to(Vector2f targetPos, int interval_milliseconds, int interval_offset, float speed, int offset)
{
	if (missile.missileCount > 0)
	{
		if (missileClock.getElapsedTime().asMilliseconds() > helperFunc::randRange(interval_milliseconds - interval_offset, interval_milliseconds + interval_offset))
		{
			missileOriginPos = Vector2f(enemy1Sprite.getPosition().x + rect.width / 2 - 5, enemy1Sprite.getPosition().y + 20);
			missile.sprite.setPosition(missileOriginPos);
			// missiles.push_back(missile);
			missile.missileCount--;
			missileClock.restart();
			cout << "enemy fired missile" << endl;
		}

		for (i = 0; i < missiles.size(); i++)
		{
			shootPos.x = helperFunc::randRange(targetPos.x - offset, targetPos.x + offset);
			shootPos.y = helperFunc::randRange(targetPos.y - offset, targetPos.y + offset);

			shootMissileTemp = helperFunc::getNormalizedVector(shootPos, missileOriginPos);
			shootMissileTemp.x *= gamehandler.getElapsedTime() * speed;
			shootMissileTemp.y *= gamehandler.getElapsedTime() * speed;

			missiles[i].sprite.move(shootMissileTemp);
			if (missiles[i].sprite.getPosition().x < 0 || missiles[i].sprite.getPosition().x > windowSizeX || missiles[i].sprite.getPosition().y < 0 || missiles[i].sprite.getPosition().y > windowSizeY)
			{
				missiles.erase(missiles.begin() + i);
			}
		}
	}
}

void Enemy1::moveDown(float speed)
{
	cout << "player moved down" << endl;
	enemy1Sprite.move(0, speed * gamehandler.getElapsedTime());
}

void Enemy1::moveUp(float speed)
{
	cout << "player moved up" << endl;
	enemy1Sprite.move(0, -speed * gamehandler.getElapsedTime());
}

void Enemy1::moveLeft(float speed)
{
	enemy1Sprite.move(-speed * gamehandler.getElapsedTime(), 0);
	cout << "player moved left" << endl;
}

void Enemy1::moveRight(float speed)
{
	enemy1Sprite.move(speed * gamehandler.getElapsedTime(), 0);
	cout << "player moved right" << endl;
}

void Enemy1::move_to(Vector2f targetPos, int interval_milliseconds, int interval_offset, float speed, int offset)
{
	if (moveClock.getElapsedTime().asMilliseconds() > helperFunc::randRange(interval_milliseconds - interval_offset, interval_milliseconds + interval_offset))
	{
		if (moveInit != targetPos){
			movePos.x = helperFunc::randRange(targetPos.x - offset, targetPos.x + offset);
			movePos.y = helperFunc::randRange(targetPos.y - offset, targetPos.y + offset);
			cout << "init: " << movePos.x << " " << movePos.y << endl;

			moveNorm = helperFunc::getNormalizedVector(movePos, enemy1Sprite.getPosition());
			moveNorm.x *= gamehandler.getElapsedTime() * speed;
			moveNorm.y *= gamehandler.getElapsedTime() * speed;

			enemy1Sprite.move(moveNorm);
			moveClock.restart();
			moveInit = targetPos;
		}
		else
		{
			movePos.x = helperFunc::randRange(windowSizeX - offset, windowSizeX + offset);
			movePos.y = helperFunc::randRange(windowSizeY - offset, windowSizeY + offset);

			cout << "rand: " << movePos.x << " " << movePos.y << endl;
			moveNorm = helperFunc::getNormalizedVector(movePos, enemy1Sprite.getPosition());
			moveNorm.x *= gamehandler.getElapsedTime() * speed;
			moveNorm.y *= gamehandler.getElapsedTime() * speed;

			enemy1Sprite.move(moveNorm);
			moveClock.restart();
		}

	}
	else
	{
		enemy1Sprite.move(moveNorm);
	}
}
