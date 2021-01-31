#include "BaseEnemy.hpp"
#include "GetRes.hpp"
#include "Helper.hpp"

using namespace std;
using namespace sf;

bool BaseEnemy::isMute;

BaseEnemy::BaseEnemy()
{
	i = rand() % 7;
	switch (i)
	{
		case 0:
			chosenTexture = &GetRes::enemyBodyTex1;
			break;
		case 1:
			chosenTexture = &GetRes::enemyBodyTex2;
			break;
		case 2:
			chosenTexture = &GetRes::enemyBodyTex3;
			break;
		case 3:
			chosenTexture = &GetRes::enemyBodyTex4;
			break;
		case 4:
			chosenTexture = &GetRes::enemyBodyTex5;
			break;
		case 5:
			chosenTexture = &GetRes::enemyBodyTex6;
			break;
		case 6:
			chosenTexture = &GetRes::enemyBodyTex7;
			break;
		default:
			chosenTexture = &GetRes::enemyBodyTex1;
			break;
	}
	enemySprite.setTexture(*chosenTexture);
	enemyRect.left = 0;
	enemyRect.top = 0;
	enemyRect.height = 224;
	enemyRect.width = 170;
	enemySprite.setTextureRect(enemyRect);
	enemySprite.setScale(0.5, 0.5);
	enemySprite.setPosition(Helper::randRange(0, Helper::windowWidth() - enemySprite.getGlobalBounds().width - 10), Helper::randRange(-800, -300));

	explosion.sprite.setTexture(GetRes::explosionTex);
	explosion.rect.left = -51; // since explosion clock starts at instantiation the elapsed time would be greater than 0.2 seconds most of the time. so we need to start with -width in left
	explosion.rect.top = 0;
	explosion.rect.height = 65;
	explosion.rect.width = 51;
	explosion.sprite.setTextureRect(explosion.rect);

	bigExplosion.sprite.setTexture(GetRes::explosionTex);
	bigExplosion.rect.left = -51; // since explosion clock starts at instantiation the elapsed time would be greater than 0.2 seconds most of the time. so we need to start with -width in left
	bigExplosion.rect.top = 0;
	bigExplosion.rect.height = 65;
	bigExplosion.rect.width = 51;
	bigExplosion.sprite.setTextureRect(explosion.rect);

	healthValue = 100;

	isDead = false;
	isDying = false;
	moveInit = false;
	moveFin = false;
	moveLeftFin = rand() % 2;
	moveRightFin = !moveLeftFin;
	shouldDisappear = false;
	shouldExplode = false;
	firstTime = true;
	isBulletIntervalSet = false;
	isMissileIntervalSet = false;
	isMute = false;
	bulletDamage = 5;
	missileDamage = 8;
	hitBodyDamage = 9;
	pi = 2 * asin(1.0);

	bulletLeft.speed = 500;
	bulletLeft.sprite.setTexture(GetRes::enemyBulletTex);

	bulletRight.speed = 500;
	bulletRight.sprite.setTexture(GetRes::enemyBulletTex);

	missile.speed = 400;
	missile.sprite.setTexture(GetRes::enemyMissileTex);
	missileCount = 9;

	bulletSound.setBuffer(GetRes::enemyBulletSound);
	missileSound.setBuffer(GetRes::enemyMissileSound);
	bulletHitSound.setBuffer(GetRes::enemyBulletExplosionSound);
	missileHitSound.setBuffer(GetRes::enemyMissileExplosionSound);
	explodedSound.setBuffer(GetRes::enemyExplodedSound);

	Helper::resetClock();
}

bool BaseEnemy::shouldRemoveBullet(Bullet& bullet)
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

bool BaseEnemy::shouldRemoveMissile(Missile& missile)
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

bool BaseEnemy::shouldRemoveExplosion(Explosion& explosion)
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

void BaseEnemy::Show(RenderWindow& window)
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
		bullet.sprite.move(0, -bullet.speed * Helper::SecondsPerFrame());
	}
	bulletsLeft.erase(remove_if(bulletsLeft.begin(), bulletsLeft.end(), BaseEnemy::shouldRemoveBullet), bulletsLeft.end());

	for (auto& bullet : bulletsRight)
	{
		bullet.sprite.move(0, -bullet.speed * Helper::SecondsPerFrame());
	}
	bulletsRight.erase(remove_if(bulletsRight.begin(), bulletsRight.end(), BaseEnemy::shouldRemoveBullet), bulletsRight.end());

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
	missiles.erase(remove_if(missiles.begin(), missiles.end(), BaseEnemy::shouldRemoveMissile), missiles.end());

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

	explosions.erase(remove_if(explosions.begin(), explosions.end(), BaseEnemy::shouldRemoveExplosion), explosions.end());

	for (auto& explosion : explosions)
	{
		window.draw(explosion.sprite);
	}
}

void BaseEnemy::setStyle(Style style)
{
	switch (style)
	{
		case RedRider:
			chosenTexture = &GetRes::enemyBodyTex1;
			break;
		case YellowZen:
			chosenTexture = &GetRes::enemyBodyTex2;
			break;
		case BlueBolt:
			chosenTexture = &GetRes::enemyBodyTex3;
			break;
		case BlueHazard:
			chosenTexture = &GetRes::enemyBodyTex4;
			break;
		case GreenGwen:
			chosenTexture = &GetRes::enemyBodyTex5;
			break;
		case RedRanger:
			chosenTexture = &GetRes::enemyBodyTex6;
			break;
		case PurplePunk:
			chosenTexture = &GetRes::enemyBodyTex7;
			break;
		case ShakaLala:
			chosenTexture = &GetRes::bossBodyTex;
			break;
		default:
			chosenTexture = &GetRes::enemyBodyTex1;
			break;
	}
}

void BaseEnemy::Die()
{
	bigExplosion.sprite.setOrigin(25.5, 32.5);
	bigExplosion.sprite.setPosition(enemySprite.getGlobalBounds().left + enemySprite.getGlobalBounds().width / 2, enemySprite.getGlobalBounds().top + enemySprite.getGlobalBounds().height / 2);
	bigExplosion.sprite.setScale(3, 3);
	if (!shouldExplode)
	{
		explodedSound.play();
		shouldExplode = true;
	}
}

void BaseEnemy::moveDown(float speed)
{
	if (!isDying)
	{
		tempVect = Helper::getNormalizedVector(Vector2f(enemySprite.getPosition().x, Helper::windowHeight() + 100), Vector2f(enemySprite.getPosition().x, enemySprite.getPosition().y));
		tempVect.x *= Helper::SecondsPerFrame() * speed;
		tempVect.y *= Helper::SecondsPerFrame() * speed;

		enemySprite.move(tempVect);
		for (auto& explosion : explosions)
		{
			explosion.sprite.move(tempVect);
		}
	}
}

void BaseEnemy::moveUp(float speed)
{
	if (!isDying)
	{
		tempVect = Helper::getNormalizedVector(Vector2f(enemySprite.getPosition().x, -Helper::windowHeight()), Vector2f(enemySprite.getPosition().x, enemySprite.getPosition().y));
		tempVect.x *= Helper::SecondsPerFrame() * speed;
		tempVect.y *= Helper::SecondsPerFrame() * speed;

		enemySprite.move(tempVect);
		for (auto& explosion : explosions)
		{
			explosion.sprite.move(tempVect);
		}
	}
}

void BaseEnemy::moveLeft(float speed)
{
	if (!isDying)
	{
		tempVect = Helper::getNormalizedVector(Vector2f(-Helper::windowWidth(), enemySprite.getPosition().y), Vector2f(enemySprite.getPosition().x, enemySprite.getPosition().y));
		tempVect.x *= Helper::SecondsPerFrame() * speed;
		tempVect.y *= Helper::SecondsPerFrame() * speed;

		enemySprite.move(tempVect);
		for (auto& explosion : explosions)
		{
			explosion.sprite.move(tempVect);
		}
	}
}

void BaseEnemy::moveRight(float speed)
{
	if (!isDying)
	{
		tempVect = Helper::getNormalizedVector(Vector2f(Helper::windowWidth() + 100, enemySprite.getPosition().y), Vector2f(enemySprite.getPosition().x, enemySprite.getPosition().y));
		tempVect.x *= Helper::SecondsPerFrame() * speed;
		tempVect.y *= Helper::SecondsPerFrame() * speed;

		enemySprite.move(tempVect);
		for (auto& explosion : explosions)
		{
			explosion.sprite.move(tempVect);
		}
	}
}

void BaseEnemy::show_explosion_bullet(Vector2f pos)
{
	explosion.sprite.setOrigin(25.5, 32.5);
	explosion.sprite.setScale(1, 1);
	explosion.sprite.setPosition(pos);
	explosions.push_back(explosion);
	bulletHitSound.play();
}
void BaseEnemy::show_explosion_missile(Vector2f pos)
{
	explosion.sprite.setOrigin(25.5, 32.5);
	explosion.sprite.setScale(2, 2);
	explosion.sprite.setPosition(pos);
	explosions.push_back(explosion);
	missileHitSound.play();
}
