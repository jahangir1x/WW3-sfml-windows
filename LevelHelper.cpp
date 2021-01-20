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
		for (i = 0; i < player.bulletsLeft.size(); i++)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, player.bulletsLeft[i].sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, player.bulletsLeft[i].sprite))
				{

					enemy.show_explosion_bullet(player.bulletsLeft[i].sprite.getPosition());
					enemy.healthValue -= player.bulletDamage;
					// cout << "enemy1 health: " << enemy.healthValue << endl;
					// player.bulletsLeft[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
					player.bulletsLeft[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
		for (i = 0; i < player.bulletsRight.size(); i++)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, player.bulletsRight[i].sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, player.bulletsRight[i].sprite))
				{

					// cout << "hit bullet: " << id << endl;
					enemy.show_explosion_bullet(player.bulletsRight[i].sprite.getPosition());
					enemy.healthValue -= player.bulletDamage;
					// cout << "enemy1 health: " << enemy.healthValue << endl;
					// player.bulletsRight[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
					player.bulletsRight[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
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
		for (i = 0; i < enemy.bulletsLeft.size(); i++)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, enemy.bulletsLeft[i].sprite)) // fix create loop to check bullets
			{

				if (Collision::PixelPerfectTest(player.playerSprite, enemy.bulletsLeft[i].sprite))
				{

					// cout << "hit bullet: " << id << endl;
					player.show_explosion_bullet(Vector2f(enemy.bulletsLeft[i].sprite.getGlobalBounds().left + enemy.bulletsLeft[i].sprite.getGlobalBounds().width, enemy.bulletsLeft[i].sprite.getGlobalBounds().top + enemy.bulletsLeft[i].sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.bulletDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					enemy.bulletsLeft[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
		for (i = 0; i < enemy.bulletsRight.size(); i++)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, enemy.bulletsRight[i].sprite)) // fix create loop to check bullets
			{

				if (Collision::PixelPerfectTest(player.playerSprite, enemy.bulletsRight[i].sprite))
				{

					// cout << "hit bullet: " << id << endl;
					player.show_explosion_bullet(Vector2f(enemy.bulletsRight[i].sprite.getGlobalBounds().left + enemy.bulletsRight[i].sprite.getGlobalBounds().width, enemy.bulletsRight[i].sprite.getGlobalBounds().top + enemy.bulletsRight[i].sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.bulletDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					enemy.bulletsRight[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
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
		for (i = 0; i < player.missiles.size(); i++)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, player.missiles[i].sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, player.missiles[i].sprite))
				{

					// cout << "hit bullet: " << id << endl;
					enemy.show_explosion_missile(player.missiles[i].sprite.getPosition());
					enemy.healthValue -= player.missileDamage;
					// cout << "enemy1 health: " << healthValue << endl;
					player.missiles[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
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
		for (i = 0; i < enemy.missiles.size(); i++)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, enemy.missiles[i].sprite))
			{

				if (Collision::PixelPerfectTest(player.playerSprite, enemy.missiles[i].sprite))
				{

					// cout << "hit missile: " << id << endl;
					player.show_explosion_missile(Vector2f(enemy.missiles[i].sprite.getGlobalBounds().left + enemy.missiles[i].sprite.getGlobalBounds().width, enemy.missiles[i].sprite.getGlobalBounds().top + enemy.missiles[i].sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.missileDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					enemy.missiles[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
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

void LevelHelper::isHitBullet(Player& player, Enemy2& enemy)
{
	if (enemy.healthValue > 0)
	{
		for (i = 0; i < player.bulletsLeft.size(); i++)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, player.bulletsLeft[i].sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, player.bulletsLeft[i].sprite))
				{

					enemy.show_explosion_bullet(player.bulletsLeft[i].sprite.getPosition());
					enemy.healthValue -= player.bulletDamage;
					// cout << "enemy1 health: " << enemy.healthValue << endl;
					// player.bulletsLeft[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
					player.bulletsLeft[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
		for (i = 0; i < player.bulletsRight.size(); i++)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, player.bulletsRight[i].sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, player.bulletsRight[i].sprite))
				{

					// cout << "hit bullet: " << id << endl;
					enemy.show_explosion_bullet(player.bulletsRight[i].sprite.getPosition());
					enemy.healthValue -= player.bulletDamage;
					// cout << "enemy1 health: " << enemy.healthValue << endl;
					// player.bulletsRight[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
					player.bulletsRight[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
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
		for (i = 0; i < enemy.bulletsLeft.size(); i++)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, enemy.bulletsLeft[i].sprite)) // fix create loop to check bullets
			{

				if (Collision::PixelPerfectTest(player.playerSprite, enemy.bulletsLeft[i].sprite))
				{

					// cout << "hit bullet: " << id << endl;
					player.show_explosion_bullet(Vector2f(enemy.bulletsLeft[i].sprite.getGlobalBounds().left + enemy.bulletsLeft[i].sprite.getGlobalBounds().width, enemy.bulletsLeft[i].sprite.getGlobalBounds().top + enemy.bulletsLeft[i].sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.bulletDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					enemy.bulletsLeft[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
		for (i = 0; i < enemy.bulletsRight.size(); i++)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, enemy.bulletsRight[i].sprite)) // fix create loop to check bullets
			{

				if (Collision::PixelPerfectTest(player.playerSprite, enemy.bulletsRight[i].sprite))
				{

					// cout << "hit bullet: " << id << endl;
					player.show_explosion_bullet(Vector2f(enemy.bulletsRight[i].sprite.getGlobalBounds().left + enemy.bulletsRight[i].sprite.getGlobalBounds().width, enemy.bulletsRight[i].sprite.getGlobalBounds().top + enemy.bulletsRight[i].sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.bulletDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					enemy.bulletsRight[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
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
		for (i = 0; i < player.missiles.size(); i++)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, player.missiles[i].sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, player.missiles[i].sprite))
				{

					// cout << "hit bullet: " << id << endl;
					enemy.show_explosion_missile(player.missiles[i].sprite.getPosition());
					enemy.healthValue -= player.missileDamage;
					// cout << "enemy1 health: " << healthValue << endl;
					player.missiles[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
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
		for (i = 0; i < enemy.missiles.size(); i++)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, enemy.missiles[i].sprite))
			{

				if (Collision::PixelPerfectTest(player.playerSprite, enemy.missiles[i].sprite))
				{

					// cout << "hit missile: " << id << endl;
					player.show_explosion_missile(Vector2f(enemy.missiles[i].sprite.getGlobalBounds().left + enemy.missiles[i].sprite.getGlobalBounds().width, enemy.missiles[i].sprite.getGlobalBounds().top + enemy.missiles[i].sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.missileDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					enemy.missiles[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
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
		for (i = 0; i < player.bulletsLeft.size(); i++)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, player.bulletsLeft[i].sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, player.bulletsLeft[i].sprite))
				{

					enemy.show_explosion_bullet(player.bulletsLeft[i].sprite.getPosition());
					enemy.healthValue -= player.bulletDamage;
					// cout << "Enemy3 health: " << enemy.healthValue << endl;
					// player.bulletsLeft[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
					player.bulletsLeft[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
		for (i = 0; i < player.bulletsRight.size(); i++)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, player.bulletsRight[i].sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, player.bulletsRight[i].sprite))
				{

					// cout << "hit bullet: " << id << endl;
					enemy.show_explosion_bullet(player.bulletsRight[i].sprite.getPosition());
					enemy.healthValue -= player.bulletDamage;
					// cout << "Enemy3 health: " << enemy.healthValue << endl;
					// player.bulletsRight[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
					player.bulletsRight[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
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
		for (i = 0; i < enemy.bulletsLeft.size(); i++)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, enemy.bulletsLeft[i].sprite)) // fix create loop to check bullets
			{

				if (Collision::PixelPerfectTest(player.playerSprite, enemy.bulletsLeft[i].sprite))
				{

					// cout << "hit bullet: " << id << endl;
					player.show_explosion_bullet(Vector2f(enemy.bulletsLeft[i].sprite.getGlobalBounds().left + enemy.bulletsLeft[i].sprite.getGlobalBounds().width, enemy.bulletsLeft[i].sprite.getGlobalBounds().top + enemy.bulletsLeft[i].sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.bulletDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					enemy.bulletsLeft[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
		for (i = 0; i < enemy.bulletsRight.size(); i++)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, enemy.bulletsRight[i].sprite)) // fix create loop to check bullets
			{

				if (Collision::PixelPerfectTest(player.playerSprite, enemy.bulletsRight[i].sprite))
				{

					// cout << "hit bullet: " << id << endl;
					player.show_explosion_bullet(Vector2f(enemy.bulletsRight[i].sprite.getGlobalBounds().left + enemy.bulletsRight[i].sprite.getGlobalBounds().width, enemy.bulletsRight[i].sprite.getGlobalBounds().top + enemy.bulletsRight[i].sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.bulletDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					enemy.bulletsRight[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
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
		for (i = 0; i < player.missiles.size(); i++)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, player.missiles[i].sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, player.missiles[i].sprite))
				{

					// cout << "hit bullet: " << id << endl;
					enemy.show_explosion_missile(player.missiles[i].sprite.getPosition());
					enemy.healthValue -= player.missileDamage;
					// cout << "Enemy3 health: " << healthValue << endl;
					player.missiles[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
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
		for (i = 0; i < enemy.missiles.size(); i++)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, enemy.missiles[i].sprite))
			{

				if (Collision::PixelPerfectTest(player.playerSprite, enemy.missiles[i].sprite))
				{

					// cout << "hit missile: " << id << endl;
					player.show_explosion_missile(Vector2f(enemy.missiles[i].sprite.getGlobalBounds().left + enemy.missiles[i].sprite.getGlobalBounds().width, enemy.missiles[i].sprite.getGlobalBounds().top + enemy.missiles[i].sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.missileDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					enemy.missiles[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
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
		for (i = 0; i < player.bulletsLeft.size(); i++)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, player.bulletsLeft[i].sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, player.bulletsLeft[i].sprite))
				{

					enemy.show_explosion_bullet(player.bulletsLeft[i].sprite.getPosition());
					enemy.healthValue -= player.bulletDamage;
					// cout << "Enemy4 health: " << enemy.healthValue << endl;
					// player.bulletsLeft[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
					player.bulletsLeft[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
		for (i = 0; i < player.bulletsRight.size(); i++)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, player.bulletsRight[i].sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, player.bulletsRight[i].sprite))
				{

					// cout << "hit bullet: " << id << endl;
					enemy.show_explosion_bullet(player.bulletsRight[i].sprite.getPosition());
					enemy.healthValue -= player.bulletDamage;
					// cout << "Enemy4 health: " << enemy.healthValue << endl;
					// player.bulletsRight[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
					player.bulletsRight[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
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
		for (i = 0; i < enemy.bulletsLeft.size(); i++)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, enemy.bulletsLeft[i].sprite)) // fix create loop to check bullets
			{

				if (Collision::PixelPerfectTest(player.playerSprite, enemy.bulletsLeft[i].sprite))
				{

					// cout << "hit bullet: " << id << endl;
					player.show_explosion_bullet(Vector2f(enemy.bulletsLeft[i].sprite.getGlobalBounds().left + enemy.bulletsLeft[i].sprite.getGlobalBounds().width, enemy.bulletsLeft[i].sprite.getGlobalBounds().top + enemy.bulletsLeft[i].sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.bulletDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					enemy.bulletsLeft[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
		for (i = 0; i < enemy.bulletsRight.size(); i++)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, enemy.bulletsRight[i].sprite)) // fix create loop to check bullets
			{

				if (Collision::PixelPerfectTest(player.playerSprite, enemy.bulletsRight[i].sprite))
				{

					// cout << "hit bullet: " << id << endl;
					player.show_explosion_bullet(Vector2f(enemy.bulletsRight[i].sprite.getGlobalBounds().left + enemy.bulletsRight[i].sprite.getGlobalBounds().width, enemy.bulletsRight[i].sprite.getGlobalBounds().top + enemy.bulletsRight[i].sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.bulletDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					enemy.bulletsRight[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
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
		for (i = 0; i < player.missiles.size(); i++)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, player.missiles[i].sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, player.missiles[i].sprite))
				{

					// cout << "hit bullet: " << id << endl;
					enemy.show_explosion_missile(player.missiles[i].sprite.getPosition());
					enemy.healthValue -= player.missileDamage;
					// cout << "Enemy4 health: " << healthValue << endl;
					player.missiles[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
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
		for (i = 0; i < enemy.missiles.size(); i++)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, enemy.missiles[i].sprite))
			{

				if (Collision::PixelPerfectTest(player.playerSprite, enemy.missiles[i].sprite))
				{

					// cout << "hit missile: " << id << endl;
					player.show_explosion_missile(Vector2f(enemy.missiles[i].sprite.getGlobalBounds().left + enemy.missiles[i].sprite.getGlobalBounds().width, enemy.missiles[i].sprite.getGlobalBounds().top + enemy.missiles[i].sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.missileDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					enemy.missiles[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
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
		for (i = 0; i < player.bulletsLeft.size(); i++)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, player.bulletsLeft[i].sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, player.bulletsLeft[i].sprite))
				{

					enemy.show_explosion_bullet(player.bulletsLeft[i].sprite.getPosition());
					enemy.healthValue -= player.bulletDamage;
					// cout << "Enemy5 health: " << enemy.healthValue << endl;
					// player.bulletsLeft[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
					player.bulletsLeft[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
		for (i = 0; i < player.bulletsRight.size(); i++)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, player.bulletsRight[i].sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, player.bulletsRight[i].sprite))
				{

					// cout << "hit bullet: " << id << endl;
					enemy.show_explosion_bullet(player.bulletsRight[i].sprite.getPosition());
					enemy.healthValue -= player.bulletDamage;
					// cout << "Enemy5 health: " << enemy.healthValue << endl;
					// player.bulletsRight[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
					player.bulletsRight[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
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
		for (i = 0; i < enemy.bulletsLeft.size(); i++)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, enemy.bulletsLeft[i].sprite)) // fix create loop to check bullets
			{

				if (Collision::PixelPerfectTest(player.playerSprite, enemy.bulletsLeft[i].sprite))
				{

					// cout << "hit bullet: " << id << endl;
					player.show_explosion_bullet(Vector2f(enemy.bulletsLeft[i].sprite.getGlobalBounds().left + enemy.bulletsLeft[i].sprite.getGlobalBounds().width, enemy.bulletsLeft[i].sprite.getGlobalBounds().top + enemy.bulletsLeft[i].sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.bulletDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					enemy.bulletsLeft[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
		for (i = 0; i < enemy.bulletsRight.size(); i++)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, enemy.bulletsRight[i].sprite)) // fix create loop to check bullets
			{

				if (Collision::PixelPerfectTest(player.playerSprite, enemy.bulletsRight[i].sprite))
				{

					// cout << "hit bullet: " << id << endl;
					player.show_explosion_bullet(Vector2f(enemy.bulletsRight[i].sprite.getGlobalBounds().left + enemy.bulletsRight[i].sprite.getGlobalBounds().width, enemy.bulletsRight[i].sprite.getGlobalBounds().top + enemy.bulletsRight[i].sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.bulletDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					enemy.bulletsRight[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
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
		for (i = 0; i < player.missiles.size(); i++)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, player.missiles[i].sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, player.missiles[i].sprite))
				{

					// cout << "hit bullet: " << id << endl;
					enemy.show_explosion_missile(player.missiles[i].sprite.getPosition());
					enemy.healthValue -= player.missileDamage;
					// cout << "Enemy5 health: " << healthValue << endl;
					player.missiles[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
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
		for (i = 0; i < enemy.missiles.size(); i++)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, enemy.missiles[i].sprite))
			{

				if (Collision::PixelPerfectTest(player.playerSprite, enemy.missiles[i].sprite))
				{

					// cout << "hit missile: " << id << endl;
					player.show_explosion_missile(Vector2f(enemy.missiles[i].sprite.getGlobalBounds().left + enemy.missiles[i].sprite.getGlobalBounds().width, enemy.missiles[i].sprite.getGlobalBounds().top + enemy.missiles[i].sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.missileDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					enemy.missiles[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
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
		for (i = 0; i < player.bulletsLeft.size(); i++)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, player.bulletsLeft[i].sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, player.bulletsLeft[i].sprite))
				{

					enemy.show_explosion_bullet(player.bulletsLeft[i].sprite.getPosition());
					enemy.healthValue -= player.bulletDamage;
					// cout << "Enemy6 health: " << enemy.healthValue << endl;
					// player.bulletsLeft[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
					player.bulletsLeft[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
		for (i = 0; i < player.bulletsRight.size(); i++)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, player.bulletsRight[i].sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, player.bulletsRight[i].sprite))
				{

					// cout << "hit bullet: " << id << endl;
					enemy.show_explosion_bullet(player.bulletsRight[i].sprite.getPosition());
					enemy.healthValue -= player.bulletDamage;
					// cout << "Enemy6 health: " << enemy.healthValue << endl;
					// player.bulletsRight[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
					player.bulletsRight[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
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
		for (i = 0; i < enemy.bulletsLeft.size(); i++)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, enemy.bulletsLeft[i].sprite)) // fix create loop to check bullets
			{

				if (Collision::PixelPerfectTest(player.playerSprite, enemy.bulletsLeft[i].sprite))
				{

					// cout << "hit bullet: " << id << endl;
					player.show_explosion_bullet(Vector2f(enemy.bulletsLeft[i].sprite.getGlobalBounds().left + enemy.bulletsLeft[i].sprite.getGlobalBounds().width, enemy.bulletsLeft[i].sprite.getGlobalBounds().top + enemy.bulletsLeft[i].sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.bulletDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					enemy.bulletsLeft[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
				}
			}
		}
		for (i = 0; i < enemy.bulletsRight.size(); i++)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, enemy.bulletsRight[i].sprite)) // fix create loop to check bullets
			{

				if (Collision::PixelPerfectTest(player.playerSprite, enemy.bulletsRight[i].sprite))
				{

					// cout << "hit bullet: " << id << endl;
					player.show_explosion_bullet(Vector2f(enemy.bulletsRight[i].sprite.getGlobalBounds().left + enemy.bulletsRight[i].sprite.getGlobalBounds().width, enemy.bulletsRight[i].sprite.getGlobalBounds().top + enemy.bulletsRight[i].sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.bulletDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					enemy.bulletsRight[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
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
		for (i = 0; i < player.missiles.size(); i++)
		{
			if (Collision::BoundingBoxTest(enemy.enemySprite, player.missiles[i].sprite))
			{

				if (Collision::PixelPerfectTest(enemy.enemySprite, player.missiles[i].sprite))
				{

					// cout << "hit bullet: " << id << endl;
					enemy.show_explosion_missile(player.missiles[i].sprite.getPosition());
					enemy.healthValue -= player.missileDamage;
					// cout << "Enemy6 health: " << healthValue << endl;
					player.missiles[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
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
		for (i = 0; i < enemy.missiles.size(); i++)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, enemy.missiles[i].sprite))
			{

				if (Collision::PixelPerfectTest(player.playerSprite, enemy.missiles[i].sprite))
				{

					// cout << "hit missile: " << id << endl;
					player.show_explosion_missile(Vector2f(enemy.missiles[i].sprite.getGlobalBounds().left + enemy.missiles[i].sprite.getGlobalBounds().width, enemy.missiles[i].sprite.getGlobalBounds().top + enemy.missiles[i].sprite.getGlobalBounds().height));
					player.playerHealth.healthValue -= enemy.missileDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					enemy.missiles[i].sprite.setPosition(Helper::windowWidth() + 100, 0);
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