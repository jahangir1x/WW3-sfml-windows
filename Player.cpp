#include "Player.hpp"
#include "Collision.h"
#include "GameHandler.hpp"
#include "Helper.hpp"
#include "LevelFailed.hpp"

using namespace std;
using namespace sf;

Player::Player()
{
	playerTexture.loadFromFile("res/player_spritesheet.png");
	playerSprite.setTexture(playerTexture);
	playerRect.left = 0;
	playerRect.top = 0;
	playerRect.height = 118;
	playerRect.width = 88;
	playerSprite.setTextureRect(playerRect);
	playerSprite.setPosition(Helper::windowWidth() / 2 - playerRect.width / 2, Helper::windowHeight() - playerRect.height - 30);

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
	explosion.rect.left = -51;
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

bool Player::shouldRemoveBullet(Bullet& bullet)
{
	if (bullet.sprite.getPosition().x < 0 || bullet.sprite.getPosition().x > Helper::windowWidth() || bullet.sprite.getPosition().y < 0 || bullet.sprite.getPosition().y > Helper::windowHeight())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Player::shouldRemoveMissile(Missile& missile)
{
	if (missile.sprite.getPosition().x < 0 || missile.sprite.getPosition().x > Helper::windowWidth() || missile.sprite.getPosition().y < 0 || missile.sprite.getPosition().y > Helper::windowHeight())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Player::shouldRemoveExplosion(Explosion& explosion)
{
	if (explosion.rect.left > 306)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Player::Show(RenderWindow& window)
{
	if (playerClock.getElapsedTime().asSeconds() > 0.2)
	{
		if (playerRect.left == 264)
		{
			playerRect.left = 0;
		}
		else
		{
			playerRect.left += 88;
		}
		playerSprite.setTexture(playerTexture);
		playerSprite.setTextureRect(playerRect);
		playerClock.restart();
	}

	for (auto& bullet : bulletsLeft)
	{
		bullet.sprite.move(0, -bullet.speed * Helper::SecondsPerFrame());
	}
	bulletsLeft.erase(remove_if(bulletsLeft.begin(), bulletsLeft.end(), Player::shouldRemoveBullet), bulletsLeft.end());

	for (auto& bullet : bulletsRight)
	{
		bullet.sprite.move(0, -bullet.speed * Helper::SecondsPerFrame());
	}
	bulletsRight.erase(remove_if(bulletsRight.begin(), bulletsRight.end(), Player::shouldRemoveBullet), bulletsRight.end());

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
		missile.sprite.move(0, -missile.speed * Helper::SecondsPerFrame());
	}
	missiles.erase(remove_if(missiles.begin(), missiles.end(), Player::shouldRemoveMissile), missiles.end());

	for (auto& missile : missiles)
	{
		window.draw(missile.sprite);
	}

	if (playerHealth.healthValue < 0)
	{
		playerHealth.healthValue = 0;
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

	for (auto& explosion : explosions)
	{
		if (explosion.clock.getElapsedTime().asSeconds() > 0.2)
		{
			explosion.rect.left += 51;
			explosion.sprite.setTextureRect(explosion.rect);
			explosion.clock.restart();
		}
	}

	explosions.erase(remove_if(explosions.begin(), explosions.end(), Player::shouldRemoveExplosion), explosions.end());

	for (auto& explosion : explosions)
	{
		window.draw(explosion.sprite);
	}

	window.draw(playerHealth.healthtext);
	window.draw(missile.missileText);
	window.draw(missile.missileCountString);
	window.draw(playerHealth.outsideRect);
	window.draw(playerHealth.insideRect);
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
			bulletsLeft.push_back(bulletLeft);
			bulletRight.sprite.setPosition(playerSprite.getPosition().x + 66, playerSprite.getPosition().y + 68);
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
				missile.sprite.setPosition(playerSprite.getPosition().x + playerRect.width / 2 - 5, playerSprite.getPosition().y + 20);
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