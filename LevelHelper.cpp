#include "LevelHelper.hpp"

using namespace std;
using namespace sf;

void LevelHelper::isHitBody(Player& player, Enemy1& enemy)
{
	if (enemy.healthValue > 0)
	{
		if (Collision::BoundingBoxTest(enemy.enemySprite, player.playerSprite))
		{
			if (player.hitClock.getElapsedTime().asMilliseconds() > 1700)
			{
				if (Collision::PixelPerfectTest(enemy.enemySprite, player.playerSprite))
				{
					// cout << "hit body" << endl;
					enemy.show_explosion_missile(Vector2f(enemy.enemySprite.getGlobalBounds().left + enemy.enemySprite.getGlobalBounds().width / 2, enemy.enemySprite.getGlobalBounds().top + enemy.enemySprite.getGlobalBounds().height / 2));
					enemy.healthValue -= player.hitBodyDamage;
					// cout << "enemy1 health: " << enemy.healthValue << endl;
					player.hitClock.restart();

					if (player.playerHealth.healthValue > 0)
					{

						// cout << "hit body" << endl;
						player.show_explosion_missile(Vector2f(player.playerSprite.getGlobalBounds().left + player.playerSprite.getGlobalBounds().width / 2, player.playerSprite.getGlobalBounds().top + player.playerSprite.getGlobalBounds().height / 2));
						player.playerHealth.healthValue -= enemy.hitBodyDamage;
						// cout << "player health: " << player.playerHealth.healthValue << endl;
					}
					else
					{
						player.isDying = true;
						player.Die();
					}
				}
			}
		}
	}
	else
	{
		enemy.isDying = true;
		enemy.Die();
	}
}

void LevelHelper::isHitBullet(Player& player, Enemy1& enemy)
{
	if (enemy.healthValue > 0)
	{
		for (auto& bullet : player.bulletsLeft)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, bullet.sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, bullet.sprite))
				{

					enemy.show_explosion_bullet(bullet.sprite.getPosition());
					enemy.healthValue -= player.bulletDamage;
					// cout << "enemy1 health: " << enemy.healthValue << endl;
					// bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
					bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
		for (auto& bullet : player.bulletsRight)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, bullet.sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, bullet.sprite))
				{

					// cout << "hit bullet: " << id << endl;
					enemy.show_explosion_bullet(bullet.sprite.getPosition());
					enemy.healthValue -= player.bulletDamage;
					// cout << "enemy1 health: " << enemy.healthValue << endl;
					// bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
					bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
	}
	else
	{
		enemy.isDying = true;
		enemy.Die();
	}
	if (player.playerHealth.healthValue > 0)
	{
		for (auto& bullet : enemy.bulletsLeft)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, bullet.sprite)) // fix create loop to check bullets
			{

				if (Collision::PixelPerfectTest(player.playerSprite, bullet.sprite))
				{

					// cout << "hit bullet: " << id << endl;
					player.show_explosion_bullet(Vector2f(bullet.sprite.getGlobalBounds().left + bullet.sprite.getGlobalBounds().width, bullet.sprite.getGlobalBounds().top + bullet.sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.bulletDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
		for (auto& bullet : enemy.bulletsRight)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, bullet.sprite)) // fix create loop to check bullets
			{

				if (Collision::PixelPerfectTest(player.playerSprite, bullet.sprite))
				{

					// cout << "hit bullet: " << id << endl;
					player.show_explosion_bullet(Vector2f(bullet.sprite.getGlobalBounds().left + bullet.sprite.getGlobalBounds().width, bullet.sprite.getGlobalBounds().top + bullet.sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.bulletDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
	}
	else
	{
		player.isDying = true;
		player.Die();
	}
}

void LevelHelper::isHitMissile(Player& player, Enemy1& enemy)
{
	if (enemy.healthValue > 0)
	{
		for (auto& missile : player.missiles)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, missile.sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, missile.sprite))
				{

					// cout << "hit bullet: " << id << endl;
					enemy.show_explosion_missile(missile.sprite.getPosition());
					enemy.healthValue -= player.missileDamage;
					// cout << "enemy1 health: " << healthValue << endl;
					missile.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
	}
	else
	{
		enemy.isDying = true;
		enemy.Die();
	}
	if (player.playerHealth.healthValue > 0)
	{
		for (auto& missile : enemy.missiles)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, missile.sprite))
			{

				if (Collision::PixelPerfectTest(player.playerSprite, missile.sprite))
				{

					// cout << "hit missile: " << id << endl;
					player.show_explosion_missile(Vector2f(missile.sprite.getGlobalBounds().left + missile.sprite.getGlobalBounds().width, missile.sprite.getGlobalBounds().top + missile.sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.missileDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					missile.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
	}
	else
	{
		player.isDying = true;
		player.Die();
	}
}

void LevelHelper::isHitBody(Player& player, Enemy2& enemy)
{
	if (enemy.healthValue > 0)
	{
		if (Collision::BoundingBoxTest(enemy.enemySprite, player.playerSprite))
		{
			if (player.hitClock.getElapsedTime().asMilliseconds() > 1700)
			{
				if (Collision::PixelPerfectTest(enemy.enemySprite, player.playerSprite))
				{
					// cout << "hit body" << endl;
					enemy.show_explosion_missile(Vector2f(enemy.enemySprite.getGlobalBounds().left + enemy.enemySprite.getGlobalBounds().width / 2, enemy.enemySprite.getGlobalBounds().top + enemy.enemySprite.getGlobalBounds().height / 2));
					enemy.healthValue -= player.hitBodyDamage;
					// cout << "Enemy2 health: " << enemy.healthValue << endl;
					player.hitClock.restart();

					if (player.playerHealth.healthValue > 0)
					{

						// cout << "hit body" << endl;
						player.show_explosion_missile(Vector2f(player.playerSprite.getGlobalBounds().left + player.playerSprite.getGlobalBounds().width / 2, player.playerSprite.getGlobalBounds().top + player.playerSprite.getGlobalBounds().height / 2));
						player.playerHealth.healthValue -= enemy.hitBodyDamage;
						// cout << "player health: " << player.playerHealth.healthValue << endl;
					}
					else
					{
						player.isDying = true;
						player.Die();
					}
				}
			}
		}
	}
	else
	{
		enemy.isDying = true;
		enemy.Die();
	}
}

void LevelHelper::isHitBullet(Player& player, Enemy2& enemy)
{
	if (enemy.healthValue > 0)
	{
		for (auto& bullet : player.bulletsLeft)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, bullet.sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, bullet.sprite))
				{

					enemy.show_explosion_bullet(bullet.sprite.getPosition());
					enemy.healthValue -= player.bulletDamage;
					// cout << "Enemy2 health: " << enemy.healthValue << endl;
					// bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
					bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
		for (auto& bullet : player.bulletsRight)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, bullet.sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, bullet.sprite))
				{

					// cout << "hit bullet: " << id << endl;
					enemy.show_explosion_bullet(bullet.sprite.getPosition());
					enemy.healthValue -= player.bulletDamage;
					// cout << "Enemy2 health: " << enemy.healthValue << endl;
					// bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
					bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
	}
	else
	{
		enemy.isDying = true;
		enemy.Die();
	}
	if (player.playerHealth.healthValue > 0)
	{
		for (auto& bullet : enemy.bulletsLeft)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, bullet.sprite)) // fix create loop to check bullets
			{

				if (Collision::PixelPerfectTest(player.playerSprite, bullet.sprite))
				{

					// cout << "hit bullet: " << id << endl;
					player.show_explosion_bullet(Vector2f(bullet.sprite.getGlobalBounds().left + bullet.sprite.getGlobalBounds().width, bullet.sprite.getGlobalBounds().top + bullet.sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.bulletDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
		for (auto& bullet : enemy.bulletsRight)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, bullet.sprite)) // fix create loop to check bullets
			{

				if (Collision::PixelPerfectTest(player.playerSprite, bullet.sprite))
				{

					// cout << "hit bullet: " << id << endl;
					player.show_explosion_bullet(Vector2f(bullet.sprite.getGlobalBounds().left + bullet.sprite.getGlobalBounds().width, bullet.sprite.getGlobalBounds().top + bullet.sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.bulletDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
	}
	else
	{
		player.isDying = true;
		player.Die();
	}
}

void LevelHelper::isHitMissile(Player& player, Enemy2& enemy)
{
	if (enemy.healthValue > 0)
	{
		for (auto& missile : player.missiles)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, missile.sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, missile.sprite))
				{

					// cout << "hit bullet: " << id << endl;
					enemy.show_explosion_missile(missile.sprite.getPosition());
					enemy.healthValue -= player.missileDamage;
					// cout << "Enemy2 health: " << healthValue << endl;
					missile.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
	}
	else
	{
		enemy.isDying = true;
		enemy.Die();
	}
	if (player.playerHealth.healthValue > 0)
	{
		for (auto& missile : enemy.missiles)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, missile.sprite))
			{

				if (Collision::PixelPerfectTest(player.playerSprite, missile.sprite))
				{

					// cout << "hit missile: " << id << endl;
					player.show_explosion_missile(Vector2f(missile.sprite.getGlobalBounds().left + missile.sprite.getGlobalBounds().width, missile.sprite.getGlobalBounds().top + missile.sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.missileDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					missile.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
	}
	else
	{
		player.isDying = true;
		player.Die();
	}
}

void LevelHelper::isHitBody(Player& player, Enemy3& enemy)
{
	if (enemy.healthValue > 0)
	{
		if (Collision::BoundingBoxTest(enemy.enemySprite, player.playerSprite))
		{
			if (player.hitClock.getElapsedTime().asMilliseconds() > 1700)
			{
				if (Collision::PixelPerfectTest(enemy.enemySprite, player.playerSprite))
				{
					// cout << "hit body" << endl;
					enemy.show_explosion_missile(Vector2f(enemy.enemySprite.getGlobalBounds().left + enemy.enemySprite.getGlobalBounds().width / 2, enemy.enemySprite.getGlobalBounds().top + enemy.enemySprite.getGlobalBounds().height / 2));
					enemy.healthValue -= player.hitBodyDamage;
					// cout << "Enemy3 health: " << enemy.healthValue << endl;
					player.hitClock.restart();

					if (player.playerHealth.healthValue > 0)
					{

						// cout << "hit body" << endl;
						player.show_explosion_missile(Vector2f(player.playerSprite.getGlobalBounds().left + player.playerSprite.getGlobalBounds().width / 2, player.playerSprite.getGlobalBounds().top + player.playerSprite.getGlobalBounds().height / 2));
						player.playerHealth.healthValue -= enemy.hitBodyDamage;
						// cout << "player health: " << player.playerHealth.healthValue << endl;
					}
					else
					{
						player.isDying = true;
						player.Die();
					}
				}
			}
		}
	}
	else
	{
		enemy.isDying = true;
		enemy.Die();
	}
}

void LevelHelper::isHitBullet(Player& player, Enemy3& enemy)
{
	if (enemy.healthValue > 0)
	{
		for (auto& bullet : player.bulletsLeft)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, bullet.sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, bullet.sprite))
				{

					enemy.show_explosion_bullet(bullet.sprite.getPosition());
					enemy.healthValue -= player.bulletDamage;
					// cout << "Enemy3 health: " << enemy.healthValue << endl;
					// bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
					bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
		for (auto& bullet : player.bulletsRight)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, bullet.sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, bullet.sprite))
				{

					// cout << "hit bullet: " << id << endl;
					enemy.show_explosion_bullet(bullet.sprite.getPosition());
					enemy.healthValue -= player.bulletDamage;
					// cout << "Enemy3 health: " << enemy.healthValue << endl;
					// bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
					bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
	}
	else
	{
		enemy.isDying = true;
		enemy.Die();
	}
	if (player.playerHealth.healthValue > 0)
	{
		for (auto& bullet : enemy.bulletsLeft)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, bullet.sprite)) // fix create loop to check bullets
			{

				if (Collision::PixelPerfectTest(player.playerSprite, bullet.sprite))
				{

					// cout << "hit bullet: " << id << endl;
					player.show_explosion_bullet(Vector2f(bullet.sprite.getGlobalBounds().left + bullet.sprite.getGlobalBounds().width, bullet.sprite.getGlobalBounds().top + bullet.sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.bulletDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
		for (auto& bullet : enemy.bulletsRight)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, bullet.sprite)) // fix create loop to check bullets
			{

				if (Collision::PixelPerfectTest(player.playerSprite, bullet.sprite))
				{

					// cout << "hit bullet: " << id << endl;
					player.show_explosion_bullet(Vector2f(bullet.sprite.getGlobalBounds().left + bullet.sprite.getGlobalBounds().width, bullet.sprite.getGlobalBounds().top + bullet.sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.bulletDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
	}
	else
	{
		player.isDying = true;
		player.Die();
	}
}

void LevelHelper::isHitMissile(Player& player, Enemy3& enemy)
{
	if (enemy.healthValue > 0)
	{
		for (auto& missile : player.missiles)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, missile.sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, missile.sprite))
				{

					// cout << "hit bullet: " << id << endl;
					enemy.show_explosion_missile(missile.sprite.getPosition());
					enemy.healthValue -= player.missileDamage;
					// cout << "Enemy3 health: " << healthValue << endl;
					missile.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
	}
	else
	{
		enemy.isDying = true;
		enemy.Die();
	}
	if (player.playerHealth.healthValue > 0)
	{
		for (auto& missile : enemy.missiles)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, missile.sprite))
			{

				if (Collision::PixelPerfectTest(player.playerSprite, missile.sprite))
				{

					// cout << "hit missile: " << id << endl;
					player.show_explosion_missile(Vector2f(missile.sprite.getGlobalBounds().left + missile.sprite.getGlobalBounds().width, missile.sprite.getGlobalBounds().top + missile.sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.missileDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					missile.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
	}
	else
	{
		player.isDying = true;
		player.Die();
	}
}

void LevelHelper::isHitBody(Player& player, Enemy4& enemy)
{
	if (enemy.healthValue > 0)
	{
		if (Collision::BoundingBoxTest(enemy.enemySprite, player.playerSprite))
		{
			if (player.hitClock.getElapsedTime().asMilliseconds() > 1700)
			{
				if (Collision::PixelPerfectTest(enemy.enemySprite, player.playerSprite))
				{
					// cout << "hit body" << endl;
					enemy.show_explosion_missile(Vector2f(enemy.enemySprite.getGlobalBounds().left + enemy.enemySprite.getGlobalBounds().width / 2, enemy.enemySprite.getGlobalBounds().top + enemy.enemySprite.getGlobalBounds().height / 2));
					enemy.healthValue -= player.hitBodyDamage;
					// cout << "Enemy4 health: " << enemy.healthValue << endl;
					player.hitClock.restart();

					if (player.playerHealth.healthValue > 0)
					{

						// cout << "hit body" << endl;
						player.show_explosion_missile(Vector2f(player.playerSprite.getGlobalBounds().left + player.playerSprite.getGlobalBounds().width / 2, player.playerSprite.getGlobalBounds().top + player.playerSprite.getGlobalBounds().height / 2));
						player.playerHealth.healthValue -= enemy.hitBodyDamage;
						// cout << "player health: " << player.playerHealth.healthValue << endl;
					}
					else
					{
						player.isDying = true;
						player.Die();
					}
				}
			}
		}
	}
	else
	{
		enemy.isDying = true;
		enemy.Die();
	}
}

void LevelHelper::isHitBullet(Player& player, Enemy4& enemy)
{
	if (enemy.healthValue > 0)
	{
		for (auto& bullet : player.bulletsLeft)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, bullet.sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, bullet.sprite))
				{

					enemy.show_explosion_bullet(bullet.sprite.getPosition());
					enemy.healthValue -= player.bulletDamage;
					// cout << "Enemy4 health: " << enemy.healthValue << endl;
					// bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
					bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
		for (auto& bullet : player.bulletsRight)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, bullet.sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, bullet.sprite))
				{

					// cout << "hit bullet: " << id << endl;
					enemy.show_explosion_bullet(bullet.sprite.getPosition());
					enemy.healthValue -= player.bulletDamage;
					// cout << "Enemy4 health: " << enemy.healthValue << endl;
					// bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
					bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
	}
	else
	{
		enemy.isDying = true;
		enemy.Die();
	}
	if (player.playerHealth.healthValue > 0)
	{
		for (auto& bullet : enemy.bulletsLeft)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, bullet.sprite)) // fix create loop to check bullets
			{

				if (Collision::PixelPerfectTest(player.playerSprite, bullet.sprite))
				{

					// cout << "hit bullet: " << id << endl;
					player.show_explosion_bullet(Vector2f(bullet.sprite.getGlobalBounds().left + bullet.sprite.getGlobalBounds().width, bullet.sprite.getGlobalBounds().top + bullet.sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.bulletDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
		for (auto& bullet : enemy.bulletsRight)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, bullet.sprite)) // fix create loop to check bullets
			{

				if (Collision::PixelPerfectTest(player.playerSprite, bullet.sprite))
				{

					// cout << "hit bullet: " << id << endl;
					player.show_explosion_bullet(Vector2f(bullet.sprite.getGlobalBounds().left + bullet.sprite.getGlobalBounds().width, bullet.sprite.getGlobalBounds().top + bullet.sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.bulletDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
	}
	else
	{
		player.isDying = true;
		player.Die();
	}
}

void LevelHelper::isHitMissile(Player& player, Enemy4& enemy)
{
	if (enemy.healthValue > 0)
	{
		for (auto& missile : player.missiles)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, missile.sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, missile.sprite))
				{

					// cout << "hit bullet: " << id << endl;
					enemy.show_explosion_missile(missile.sprite.getPosition());
					enemy.healthValue -= player.missileDamage;
					// cout << "Enemy4 health: " << healthValue << endl;
					missile.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
	}
	else
	{
		enemy.isDying = true;
		enemy.Die();
	}
	if (player.playerHealth.healthValue > 0)
	{
		for (auto& missile : enemy.missiles)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, missile.sprite))
			{

				if (Collision::PixelPerfectTest(player.playerSprite, missile.sprite))
				{

					// cout << "hit missile: " << id << endl;
					player.show_explosion_missile(Vector2f(missile.sprite.getGlobalBounds().left + missile.sprite.getGlobalBounds().width, missile.sprite.getGlobalBounds().top + missile.sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.missileDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					missile.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
	}
	else
	{
		player.isDying = true;
		player.Die();
	}
}

void LevelHelper::isHitBody(Player& player, Enemy5& enemy)
{
	if (enemy.healthValue > 0)
	{
		if (Collision::BoundingBoxTest(enemy.enemySprite, player.playerSprite))
		{
			if (player.hitClock.getElapsedTime().asMilliseconds() > 1700)
			{
				if (Collision::PixelPerfectTest(enemy.enemySprite, player.playerSprite))
				{
					// cout << "hit body" << endl;
					enemy.show_explosion_missile(Vector2f(enemy.enemySprite.getGlobalBounds().left + enemy.enemySprite.getGlobalBounds().width / 2, enemy.enemySprite.getGlobalBounds().top + enemy.enemySprite.getGlobalBounds().height / 2));
					enemy.healthValue -= player.hitBodyDamage;
					// cout << "Enemy5 health: " << enemy.healthValue << endl;
					player.hitClock.restart();

					if (player.playerHealth.healthValue > 0)
					{

						// cout << "hit body" << endl;
						player.show_explosion_missile(Vector2f(player.playerSprite.getGlobalBounds().left + player.playerSprite.getGlobalBounds().width / 2, player.playerSprite.getGlobalBounds().top + player.playerSprite.getGlobalBounds().height / 2));
						player.playerHealth.healthValue -= enemy.hitBodyDamage;
						// cout << "player health: " << player.playerHealth.healthValue << endl;
					}
					else
					{
						player.isDying = true;
						player.Die();
					}
				}
			}
		}
	}
	else
	{
		enemy.isDying = true;
		enemy.Die();
	}
}

void LevelHelper::isHitBullet(Player& player, Enemy5& enemy)
{
	if (enemy.healthValue > 0)
	{
		for (auto& bullet : player.bulletsLeft)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, bullet.sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, bullet.sprite))
				{

					enemy.show_explosion_bullet(bullet.sprite.getPosition());
					enemy.healthValue -= player.bulletDamage;
					// cout << "Enemy5 health: " << enemy.healthValue << endl;
					// bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
					bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
		for (auto& bullet : player.bulletsRight)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, bullet.sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, bullet.sprite))
				{

					// cout << "hit bullet: " << id << endl;
					enemy.show_explosion_bullet(bullet.sprite.getPosition());
					enemy.healthValue -= player.bulletDamage;
					// cout << "Enemy5 health: " << enemy.healthValue << endl;
					// bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
					bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
	}
	else
	{
		enemy.isDying = true;
		enemy.Die();
	}
	if (player.playerHealth.healthValue > 0)
	{
		for (auto& bullet : enemy.bulletsLeft)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, bullet.sprite)) // fix create loop to check bullets
			{

				if (Collision::PixelPerfectTest(player.playerSprite, bullet.sprite))
				{

					// cout << "hit bullet: " << id << endl;
					player.show_explosion_bullet(Vector2f(bullet.sprite.getGlobalBounds().left + bullet.sprite.getGlobalBounds().width, bullet.sprite.getGlobalBounds().top + bullet.sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.bulletDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
		for (auto& bullet : enemy.bulletsRight)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, bullet.sprite)) // fix create loop to check bullets
			{

				if (Collision::PixelPerfectTest(player.playerSprite, bullet.sprite))
				{

					// cout << "hit bullet: " << id << endl;
					player.show_explosion_bullet(Vector2f(bullet.sprite.getGlobalBounds().left + bullet.sprite.getGlobalBounds().width, bullet.sprite.getGlobalBounds().top + bullet.sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.bulletDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
	}
	else
	{
		player.isDying = true;
		player.Die();
	}
}

void LevelHelper::isHitMissile(Player& player, Enemy5& enemy)
{
	if (enemy.healthValue > 0)
	{
		for (auto& missile : player.missiles)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, missile.sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, missile.sprite))
				{

					// cout << "hit bullet: " << id << endl;
					enemy.show_explosion_missile(missile.sprite.getPosition());
					enemy.healthValue -= player.missileDamage;
					// cout << "Enemy5 health: " << healthValue << endl;
					missile.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
	}
	else
	{
		enemy.isDying = true;
		enemy.Die();
	}
	if (player.playerHealth.healthValue > 0)
	{
		for (auto& missile : enemy.missiles)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, missile.sprite))
			{

				if (Collision::PixelPerfectTest(player.playerSprite, missile.sprite))
				{

					// cout << "hit missile: " << id << endl;
					player.show_explosion_missile(Vector2f(missile.sprite.getGlobalBounds().left + missile.sprite.getGlobalBounds().width, missile.sprite.getGlobalBounds().top + missile.sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.missileDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					missile.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
	}
	else
	{
		player.isDying = true;
		player.Die();
	}
}

void LevelHelper::isHitBody(Player& player, Enemy6& enemy)
{
	if (enemy.healthValue > 0)
	{
		if (Collision::BoundingBoxTest(enemy.enemySprite, player.playerSprite))
		{
			if (player.hitClock.getElapsedTime().asMilliseconds() > 1700)
			{
				if (Collision::PixelPerfectTest(enemy.enemySprite, player.playerSprite))
				{
					// cout << "hit body" << endl;
					enemy.show_explosion_missile(Vector2f(enemy.enemySprite.getGlobalBounds().left + enemy.enemySprite.getGlobalBounds().width / 2, enemy.enemySprite.getGlobalBounds().top + enemy.enemySprite.getGlobalBounds().height / 2));
					enemy.healthValue -= player.hitBodyDamage;
					// cout << "Enemy6 health: " << enemy.healthValue << endl;
					player.hitClock.restart();

					if (player.playerHealth.healthValue > 0)
					{

						// cout << "hit body" << endl;
						player.show_explosion_missile(Vector2f(player.playerSprite.getGlobalBounds().left + player.playerSprite.getGlobalBounds().width / 2, player.playerSprite.getGlobalBounds().top + player.playerSprite.getGlobalBounds().height / 2));
						player.playerHealth.healthValue -= enemy.hitBodyDamage;
						// cout << "player health: " << player.playerHealth.healthValue << endl;
					}
					else
					{
						player.isDying = true;
						player.Die();
					}
				}
			}
		}
	}
	else
	{
		enemy.isDying = true;
		enemy.Die();
	}
}

void LevelHelper::isHitBullet(Player& player, Enemy6& enemy)
{
	if (enemy.healthValue > 0)
	{
		for (auto& bullet : player.bulletsLeft)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, bullet.sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, bullet.sprite))
				{

					enemy.show_explosion_bullet(bullet.sprite.getPosition());
					enemy.healthValue -= player.bulletDamage;
					// cout << "Enemy6 health: " << enemy.healthValue << endl;
					// bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
					bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
		for (auto& bullet : player.bulletsRight)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, bullet.sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, bullet.sprite))
				{

					// cout << "hit bullet: " << id << endl;
					enemy.show_explosion_bullet(bullet.sprite.getPosition());
					enemy.healthValue -= player.bulletDamage;
					// cout << "Enemy6 health: " << enemy.healthValue << endl;
					// bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
					bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
	}
	else
	{
		enemy.isDying = true;
		enemy.Die();
	}
	if (player.playerHealth.healthValue > 0)
	{
		for (auto& bullet : enemy.bulletsLeft)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, bullet.sprite)) // fix create loop to check bullets
			{

				if (Collision::PixelPerfectTest(player.playerSprite, bullet.sprite))
				{

					// cout << "hit bullet: " << id << endl;
					player.show_explosion_bullet(Vector2f(bullet.sprite.getGlobalBounds().left + bullet.sprite.getGlobalBounds().width, bullet.sprite.getGlobalBounds().top + bullet.sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.bulletDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
		for (auto& bullet : enemy.bulletsRight)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, bullet.sprite)) // fix create loop to check bullets
			{

				if (Collision::PixelPerfectTest(player.playerSprite, bullet.sprite))
				{

					// cout << "hit bullet: " << id << endl;
					player.show_explosion_bullet(Vector2f(bullet.sprite.getGlobalBounds().left + bullet.sprite.getGlobalBounds().width, bullet.sprite.getGlobalBounds().top + bullet.sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.bulletDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					bullet.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
	}
	else
	{
		player.isDying = true;
		player.Die();
	}
}

void LevelHelper::isHitMissile(Player& player, Enemy6& enemy)
{
	if (enemy.healthValue > 0)
	{
		for (auto& missile : player.missiles)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, missile.sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, missile.sprite))
				{

					// cout << "hit bullet: " << id << endl;
					enemy.show_explosion_missile(missile.sprite.getPosition());
					enemy.healthValue -= player.missileDamage;
					// cout << "Enemy6 health: " << healthValue << endl;
					missile.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
	}
	else
	{
		enemy.isDying = true;
		enemy.Die();
	}
	if (player.playerHealth.healthValue > 0)
	{
		for (auto& missile : enemy.missiles)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, missile.sprite))
			{

				if (Collision::PixelPerfectTest(player.playerSprite, missile.sprite))
				{

					// cout << "hit missile: " << id << endl;
					player.show_explosion_missile(Vector2f(missile.sprite.getGlobalBounds().left + missile.sprite.getGlobalBounds().width, missile.sprite.getGlobalBounds().top + missile.sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.missileDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					missile.sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
	}
	else
	{
		player.isDying = true;
		player.Die();
	}
}
