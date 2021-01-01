#include "Player.hpp"
#include "Collision.h"
#include "GameHandler.hpp"
#include "LevelFailed.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <bits/stdc++.h>
using namespace std;
using namespace sf;

Player::Player(RenderWindow& window)
{
	windowSizeX = window.getSize().x;
	windowSizeY = window.getSize().y;

	playerTexture.loadFromFile("res/player_spritesheet.png");
	playerSprite.setTexture(playerTexture);
	rect.left = 0;
	rect.top = 0;
	rect.height = 118;
	rect.width = 88;
	playerSprite.setTextureRect(rect);
	playerSprite.setPosition(windowSizeX / 2 - rect.width / 2, windowSizeY - rect.height - 30);

	prevCollisionSprite = 0;

	playerHealth.healthValue = 100;
	playerHealth.outsideRect.setPosition(33, 9);
	playerHealth.outsideRect.setSize(Vector2f(198, 12));
	playerHealth.outsideRect.setFillColor(Color(255, 0, 0, 190));
	playerHealth.insideRect.setPosition(36, 11);
	playerHealth.insideRect.setSize(Vector2f(192, 8));
	playerHealth.insideRect.setFillColor(Color(0, 255, 0, 190));
	playerHealth.healthfont.loadFromFile("res/Roboto-Regular.ttf");
	playerHealth.healthtext.setFont(playerHealth.healthfont);
	playerHealth.healthtext.setCharacterSize(12);
	playerHealth.healthtext.setFillColor(Color(0, 255, 0, 190));
	playerHealth.healthtext.setString("HP :");
	playerHealth.healthtext.setPosition(5, 8);
	playerHealth.healthtext.setStyle(Text::Bold);

	moveSpeed = 400;
	isDead = false;
	bulletDamage = 5;
	missileDamage = 8;

	bulletLeft.speed = 500;
	bulletLeft.texture.loadFromFile("res/player_bullet.png");
	bulletLeft.sprite.setTexture(bulletLeft.texture);

	bulletRight.speed = 500;
	bulletRight.texture.loadFromFile("res/player_bullet.png");
	bulletRight.sprite.setTexture(bulletRight.texture);

	missile.speed = 400;
	missile.texture.loadFromFile("res/player_missile.png");
	missile.sprite.setTexture(missile.texture);
	missile.missileText.setFont(playerHealth.healthfont);
	missile.missileText.setCharacterSize(14);
	missile.missileText.setFillColor(Color(255, 0, 0, 190));
	missile.missileText.setString("Missile :");
	missile.missileText.setPosition(5, 25);
	missile.missileText.setStyle(Text::Bold);
	missile.missileCount = 9;
	missile.missileCountString.setFont(playerHealth.healthfont);
	missile.missileCountString.setCharacterSize(14);
	missile.missileCountString.setFillColor(Color(255, 0, 0, 190));
	missile.missileCountString.setString(to_string(missile.missileCount));
	missile.missileCountString.setPosition(70, 25);
	missile.missileCountString.setStyle(Text::Bold);
}

void Player::Show(RenderWindow& window)
{
	if (playerSprite.getPosition().x < 0)
	{
		playerSprite.setPosition(0, playerSprite.getPosition().y);
	}
	if (playerSprite.getPosition().x + playerSprite.getGlobalBounds().width > windowSizeX)
	{
		playerSprite.setPosition(windowSizeX - playerSprite.getGlobalBounds().width, playerSprite.getPosition().y);
	}
	if (playerSprite.getPosition().y < 0)
	{
		playerSprite.setPosition(playerSprite.getPosition().x, 0);
	}
	if (playerSprite.getPosition().y + playerSprite.getGlobalBounds().height > windowSizeY)
	{
		playerSprite.setPosition(playerSprite.getPosition().x, windowSizeY - playerSprite.getGlobalBounds().height);
	}

	if (playerClock.getElapsedTime().asSeconds() > 0.2)
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
		playerSprite.setTexture(playerTexture);
		playerSprite.setTextureRect(rect);
		playerClock.restart();
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

	playerHealth.insideRect.setSize(Vector2f(192 * playerHealth.healthValue / 100, 8));

	// cout << "missile: " << missiles.size() << endl;
	// cout << "bullets: " << bulletsLeft.size() << endl;
	window.draw(playerSprite);
	window.draw(playerHealth.healthtext);
	window.draw(missile.missileText);
	window.draw(missile.missileCountString);
	window.draw(playerHealth.outsideRect);
	window.draw(playerHealth.insideRect);
	// window.draw(collisionCircle);
}

void Player::isHit(Sprite& targetSprite, float damage)
{
	if (Collision::BoundingBoxTest(playerSprite, targetSprite))
	{
		if (Collision::PixelPerfectTest(playerSprite, targetSprite))
		{
			if (prevCollisionSprite != &targetSprite)
			{
				if (playerHealth.healthValue > 0)
				{
					cout << "in different" << endl;
					playerHealth.healthValue -= damage;
					cout << "plh: " << playerHealth.healthValue << endl;
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
					if (playerHealth.healthValue > 0)
					{
						cout << "in same" << endl;
						playerHealth.healthValue -= damage;
						cout << "plh: " << playerHealth.healthValue << endl;
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

void Player::Die()
{
	cout << "player dead" << endl;
}

void Player::fireBullet()
{
	if (bulletClock.getElapsedTime().asSeconds() > 0.2)
	{
		bulletLeft.sprite.setPosition(playerSprite.getPosition().x + 16, playerSprite.getPosition().y + 68);
		bulletsLeft.push_back(bulletLeft);
		bulletRight.sprite.setPosition(playerSprite.getPosition().x + 66, playerSprite.getPosition().y + 68);
		bulletsRight.push_back(bulletRight);
		cout << "player fired bullet" << endl;
		bulletClock.restart();
	}
	for (i = 0; i < bulletsLeft.size(); i++)
	{
		bulletsLeft[i].sprite.move(0, -bulletsLeft[i].speed * gamehandler.getElapsedTime());
		if (bulletsLeft[i].sprite.getPosition().x < 0 || bulletsLeft[i].sprite.getPosition().x > windowSizeX || bulletsLeft[i].sprite.getPosition().y < 0 || bulletsLeft[i].sprite.getPosition().y > windowSizeY)
		{
			bulletsLeft.erase(bulletsLeft.begin() + i);
		}
		bulletsRight[i].sprite.move(0, -bulletsRight[i].speed * gamehandler.getElapsedTime());
		if (bulletsRight[i].sprite.getPosition().x < 0 || bulletsRight[i].sprite.getPosition().x > windowSizeX || bulletsRight[i].sprite.getPosition().y < 0 || bulletsRight[i].sprite.getPosition().y > windowSizeY)
		{
			bulletsRight.erase(bulletsRight.begin() + i);
		}
	}
}

void Player::fireMissile()
{
	if (missile.missileCount > 0)
	{
		if (missileClock.getElapsedTime().asSeconds() > 0.5)
		{
			missile.sprite.setPosition(playerSprite.getPosition().x + rect.width / 2 - 5, playerSprite.getPosition().y + 20);
			missiles.push_back(missile);
			missileClock.restart();
			missile.missileCount--;
			missile.missileCountString.setString(to_string(missile.missileCount));
			cout << "player fired missile" << endl;
		}
	}
	for (i = 0; i < missiles.size(); i++)
	{
		missiles[i].sprite.move(0, -missiles[i].speed * gamehandler.getElapsedTime());
		if (missiles[i].sprite.getPosition().x < 0 || missiles[i].sprite.getPosition().x > windowSizeX || missiles[i].sprite.getPosition().y < 0 || missiles[i].sprite.getPosition().y > windowSizeY)
		{
			missiles.erase(missiles.begin() + i);
		}
	}
}

void Player::moveDown()
{
	// cout << "player moved down" << endl;
	// playerMovementDT = playerMovementClock.restart().asSeconds();
	playerSprite.move(0, moveSpeed * gamehandler.getElapsedTime());
}

void Player::moveUp()
{
	// cout << "player moved up" << endl;
	playerSprite.move(0, -moveSpeed * gamehandler.getElapsedTime());
}

void Player::moveLeft()
{
	playerSprite.move(-moveSpeed * gamehandler.getElapsedTime(), 0);
	// cout << "player moved left" << endl;
}

void Player::moveRight()
{
	playerSprite.move(moveSpeed * gamehandler.getElapsedTime(), 0);
	// cout << "player moved right" << endl;
}
