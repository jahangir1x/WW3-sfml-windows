#include "Player.hpp"
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

Player::Player()
{
	playerTexture.loadFromFile("res/player_spritesheet.png");
	playerSprite.setTexture(playerTexture);
	rect.left = 0;
	rect.top = 0;
	rect.height = 118;
	rect.width = 88;
	playerSprite.setTextureRect(rect);
	playerSprite.setPosition(Helper::windowWidth() / 2 - rect.width / 2, Helper::windowHeight() - rect.height - 30);

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

	moveSpeed = 400;
	isDead = false;
	isDying = false;
	shouldDisappear = false;
	shouldExplode = false;
	bulletDamage = 5;
	missileDamage = 8;
	hitBodyDamage = 9;

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
		playerSprite.setTexture(playerTexture);
		playerSprite.setTextureRect(rect);
		playerClock.restart();
	}

	for (i = 0; i < bulletsLeft.size(); i++)
	{
		bulletsLeft[i].sprite.move(0, -bulletsLeft[i].speed * Helper::SecondsPerFrame());
		if (bulletsLeft[i].sprite.getPosition().x < 0 || bulletsLeft[i].sprite.getPosition().x > Helper::windowWidth() || bulletsLeft[i].sprite.getPosition().y < 0 || bulletsLeft[i].sprite.getPosition().y > Helper::windowHeight())
		{
			bulletsLeft.erase(bulletsLeft.begin() + i);
		}
		bulletsRight[i].sprite.move(0, -bulletsRight[i].speed * Helper::SecondsPerFrame());
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
		missiles[i].sprite.move(0, -missiles[i].speed * Helper::SecondsPerFrame());
		if (missiles[i].sprite.getPosition().x < 0 || missiles[i].sprite.getPosition().x > Helper::windowWidth() || missiles[i].sprite.getPosition().y < 0 || missiles[i].sprite.getPosition().y > Helper::windowHeight())
		{
			missiles.erase(missiles.begin() + i);
		}
	}
	for (i = 0; i < missiles.size(); i++)
	{
		window.draw(missiles[i].sprite);
	}

	playerHealth.insideRect.setSize(Vector2f(192 * playerHealth.healthValue / 100, 8));

	if (!shouldDisappear)
	{
		window.draw(playerSprite);
	}

	if (shouldExplode == true && isDead == false)
	{
		if (bigExplosion.rect.left >= 255)
		{
			cout << "disappear" << endl;
			shouldDisappear = true;
		}
		if (bigExplosionClock.getElapsedTime().asSeconds() > 0.2)
		{
			if (bigExplosion.rect.left <= 306)
			{
				bigExplosion.rect.left += 51;
			}
			else
			{
				cout << "player dead" << endl;
				isDead = true;
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

	window.draw(playerHealth.healthtext);
	window.draw(missile.missileText);
	window.draw(missile.missileCountString);
	window.draw(playerHealth.outsideRect);
	window.draw(playerHealth.insideRect);
	if (prevCollidedObj.size() > 100)
	{
		prevCollidedObj.erase(prevCollidedObj.begin(), prevCollidedObj.begin() + 30);
	}
}

void Player::Die()
{
	bigExplosion.sprite.setOrigin(25.5, 32.5);
	bigExplosion.sprite.setPosition(playerSprite.getGlobalBounds().left + playerSprite.getGlobalBounds().width / 2, playerSprite.getGlobalBounds().top + playerSprite.getGlobalBounds().height / 2);
	bigExplosion.sprite.setScale(3, 3);
	if (!shouldExplode)
	{
		shouldExplode = true;
	}
}

void Player::fireBullet()
{
	if (!isDying)
	{
		if (bulletClock.getElapsedTime().asSeconds() > 0.2)
		{
			bulletLeft.sprite.setPosition(playerSprite.getPosition().x + 16, playerSprite.getPosition().y + 68);
			bulletLeft.id = rand() + rand() + rand();
			bulletsLeft.push_back(bulletLeft);
			bulletRight.sprite.setPosition(playerSprite.getPosition().x + 66, playerSprite.getPosition().y + 68);
			bulletRight.id = rand() + rand() + rand();
			bulletsRight.push_back(bulletRight);
			bulletClock.restart();
		}
	}
}

void Player::fireMissile()
{
	if (!isDying)
	{
		if (missile.missileCount > 0)
		{
			if (missileClock.getElapsedTime().asSeconds() > 0.5)
			{
				missile.sprite.setPosition(playerSprite.getPosition().x + rect.width / 2 - 5, playerSprite.getPosition().y + 20);
				missile.id = rand() + rand() + rand();
				missiles.push_back(missile);
				missileClock.restart();
				missile.missileCount--;
				missile.missileCountString.setString(to_string(missile.missileCount));
			}
		}
	}
}

void Player::moveDown()
{
	if (!isDying)
	{
		if (playerSprite.getPosition().y + playerSprite.getGlobalBounds().height < Helper::windowHeight())
		{
			playerSprite.move(0, moveSpeed * Helper::SecondsPerFrame());
			for (i = 0; i < explosions.size(); i++)
			{
				explosions[i].sprite.move(0, moveSpeed * Helper::SecondsPerFrame());
			}
		}
	}
}

void Player::moveUp()
{
	if (!isDying)
	{
		if (playerSprite.getPosition().y > 0)
		{
			playerSprite.move(0, -moveSpeed * Helper::SecondsPerFrame());
			for (i = 0; i < explosions.size(); i++)
			{
				explosions[i].sprite.move(0, -moveSpeed * Helper::SecondsPerFrame());
			}
		}
	}
}

void Player::moveLeft()
{
	if (!isDying)
	{
		if (playerSprite.getPosition().x > 0)
		{
			playerSprite.move(-moveSpeed * Helper::SecondsPerFrame(), 0);
			// cout << "player moved left" << endl;
			for (i = 0; i < explosions.size(); i++)
			{
				explosions[i].sprite.move(-moveSpeed * Helper::SecondsPerFrame(), 0);
			}
		}
	}
}

void Player::moveRight()
{
	if (!isDying)
	{
		if (playerSprite.getPosition().x + playerSprite.getGlobalBounds().width < Helper::windowWidth())
		{
			playerSprite.move(moveSpeed * Helper::SecondsPerFrame(), 0);
			for (i = 0; i < explosions.size(); i++)
			{
				explosions[i].sprite.move(moveSpeed * Helper::SecondsPerFrame(), 0);
			}
		}
	}
}

void Player::show_explosion_bullet(Vector2f pos)
{
	explosion.sprite.setOrigin(25.5, 32.5);
	explosion.sprite.setScale(1, 1);
	explosion.sprite.setPosition(pos);
	explosions.push_back(explosion);
}
void Player::show_explosion_missile(Vector2f pos)
{
	explosion.sprite.setOrigin(25.5, 32.5);
	explosion.sprite.setScale(2, 2);
	explosion.sprite.setPosition(pos);
	explosions.push_back(explosion);
}