#include "LevelHelper.hpp"
#include "Collision.h"

using namespace std;
using namespace sf;

void LevelHelper::isHitBody(Player& player, Enemy1& enemy)
{
	if (enemy.healthValue > 0)
	{
		if (Collision::BoundingBoxTest(enemy.enemy1Sprite, player.playerSprite))
		{
			if (player.hitClock.getElapsedTime().asMilliseconds() > 1700)
			{
				if (Collision::PixelPerfectTest(enemy.enemy1Sprite, player.playerSprite))
				{
					// cout << "hit body" << endl;
					enemy.show_explosion_missile(Vector2f(enemy.enemy1Sprite.getGlobalBounds().left + enemy.enemy1Sprite.getGlobalBounds().width / 2, enemy.enemy1Sprite.getGlobalBounds().top + enemy.enemy1Sprite.getGlobalBounds().height / 2));
					enemy.healthValue -= player.hitBodyDamage;
					// cout << "enemy1 health: " << healthValue << endl;
					player.hitClock.restart();
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
		if (Collision::BoundingBoxTest(player.playerSprite, enemy.enemy1Sprite))
		{
			if (player.hitClock.getElapsedTime().asMilliseconds() > 1700)
			{
				if (Collision::PixelPerfectTest(player.playerSprite, enemy.enemy1Sprite))
				{
					// cout << "hit body" << endl;
					player.show_explosion_missile(Vector2f(player.playerSprite.getGlobalBounds().left + player.playerSprite.getGlobalBounds().width / 2, player.playerSprite.getGlobalBounds().top + player.playerSprite.getGlobalBounds().height / 2));
					player.playerHealth.healthValue -= enemy.hitBodyDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					player.hitClock.restart();
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
		if (Collision::BoundingBoxTest(enemy.enemy1Sprite, player.playerSprite))
		{
			if (player.hitClock.getElapsedTime().asMilliseconds() > 1700)
			{
				if (Collision::PixelPerfectTest(enemy.enemy1Sprite, player.playerSprite))
				{
					// cout << "hit body" << endl;
					enemy.show_explosion_missile(Vector2f(enemy.enemy1Sprite.getGlobalBounds().left + enemy.enemy1Sprite.getGlobalBounds().width / 2, enemy.enemy1Sprite.getGlobalBounds().top + enemy.enemy1Sprite.getGlobalBounds().height / 2));
					enemy.healthValue -= player.hitBodyDamage;
					// cout << "enemy1 health: " << healthValue << endl;
					player.hitClock.restart();
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
		if (Collision::BoundingBoxTest(player.playerSprite, enemy.enemy1Sprite))
		{
			if (player.hitClock.getElapsedTime().asMilliseconds() > 1700)
			{
				if (Collision::PixelPerfectTest(player.playerSprite, enemy.enemy1Sprite))
				{
					// cout << "hit body" << endl;
					player.show_explosion_missile(Vector2f(player.playerSprite.getGlobalBounds().left + player.playerSprite.getGlobalBounds().width / 2, player.playerSprite.getGlobalBounds().top + player.playerSprite.getGlobalBounds().height / 2));
					player.playerHealth.healthValue -= enemy.hitBodyDamage;
					// cout << "player health: " << playerHealth.healthValue << endl;
					player.hitClock.restart();
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

void LevelHelper::isHitBullet(Player& player, Enemy1& enemy)
{
	if (enemy.healthValue > 0)
	{
		for (i = 0; i < player.bulletsLeft.size(); i++)
		{
			if (Collision::BoundingBoxTest(enemy.enemy1Sprite, player.bulletsLeft[i].sprite))
			{
				if (find(enemy.prevCollidedObj.begin(), enemy.prevCollidedObj.end(), player.bulletsLeft[i].id) == enemy.prevCollidedObj.end())
				{
					if (Collision::PixelPerfectTest(enemy.enemy1Sprite, player.bulletsLeft[i].sprite))
					{
						enemy.prevCollidedObj.push_back(player.bulletsLeft[i].id);
						// cout << "hit bullet: " << id << endl;
						enemy.show_explosion_bullet(player.bulletsLeft[i].sprite.getPosition());
						enemy.healthValue -= player.bulletDamage;
						// cout << "enemy1 health: " << healthValue << endl;
						player.bulletsLeft[i].sprite.setColor(Color(0, 0, 0, 0));
					}
				}
			}
		}
		for (i = 0; i < player.bulletsRight.size(); i++)
		{
			if (Collision::BoundingBoxTest(enemy.enemy1Sprite, player.bulletsRight[i].sprite))
			{
				if (find(enemy.prevCollidedObj.begin(), enemy.prevCollidedObj.end(), player.bulletsRight[i].id) == enemy.prevCollidedObj.end())
				{
					if (Collision::PixelPerfectTest(enemy.enemy1Sprite, player.bulletsRight[i].sprite))
					{
						enemy.prevCollidedObj.push_back(player.bulletsRight[i].id);
						// cout << "hit bullet: " << id << endl;
						enemy.show_explosion_bullet(player.bulletsRight[i].sprite.getPosition());
						enemy.healthValue -= player.bulletDamage;
						// cout << "enemy1 health: " << healthValue << endl;
						player.bulletsRight[i].sprite.setColor(Color(0, 0, 0, 0));
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
	if (player.playerHealth.healthValue > 0)
	{
		for (i = 0; i < enemy.bulletsLeft.size(); i++)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, enemy.bulletsLeft[i].sprite)) // fix create loop to check bullets
			{
				if (find(player.prevCollidedObj.begin(), player.prevCollidedObj.end(), enemy.bulletsLeft[i].id) == player.prevCollidedObj.end())
				{
					if (Collision::PixelPerfectTest(player.playerSprite, enemy.bulletsLeft[i].sprite))
					{
						player.prevCollidedObj.push_back(enemy.bulletsLeft[i].id);
						// cout << "hit bullet: " << id << endl;
						player.show_explosion_bullet(Vector2f(enemy.bulletsLeft[i].sprite.getGlobalBounds().left + enemy.bulletsLeft[i].sprite.getGlobalBounds().width, enemy.bulletsLeft[i].sprite.getGlobalBounds().top + enemy.bulletsLeft[i].sprite.getGlobalBounds().height));
						player.playerHealth.healthValue -= enemy.bulletDamage;
						// cout << "player health: " << playerHealth.healthValue << endl;
						enemy.bulletsLeft[i].sprite.setColor(Color(0, 0, 0, 0));
					}
				}
			}
		}
		for (i = 0; i < enemy.bulletsRight.size(); i++)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, enemy.bulletsRight[i].sprite)) // fix create loop to check bullets
			{
				if (find(player.prevCollidedObj.begin(), player.prevCollidedObj.end(), enemy.bulletsRight[i].id) == player.prevCollidedObj.end())
				{
					if (Collision::PixelPerfectTest(player.playerSprite, enemy.bulletsRight[i].sprite))
					{
						player.prevCollidedObj.push_back(enemy.bulletsRight[i].id);
						// cout << "hit bullet: " << id << endl;
						player.show_explosion_bullet(Vector2f(enemy.bulletsRight[i].sprite.getGlobalBounds().left + enemy.bulletsRight[i].sprite.getGlobalBounds().width, enemy.bulletsRight[i].sprite.getGlobalBounds().top + enemy.bulletsRight[i].sprite.getGlobalBounds().height));
						player.playerHealth.healthValue -= enemy.bulletDamage;
						// cout << "player health: " << playerHealth.healthValue << endl;
						enemy.bulletsRight[i].sprite.setColor(Color(0, 0, 0, 0));
					}
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
void LevelHelper::isHitBullet(Player& player, Enemy2& enemy)
{
	if (enemy.healthValue > 0)
	{
		for (i = 0; i < player.bulletsLeft.size(); i++)
		{
			if (Collision::BoundingBoxTest(enemy.enemy1Sprite, player.bulletsLeft[i].sprite))
			{
				if (find(enemy.prevCollidedObj.begin(), enemy.prevCollidedObj.end(), player.bulletsLeft[i].id) == enemy.prevCollidedObj.end())
				{
					if (Collision::PixelPerfectTest(enemy.enemy1Sprite, player.bulletsLeft[i].sprite))
					{
						enemy.prevCollidedObj.push_back(player.bulletsLeft[i].id);
						// cout << "hit bullet: " << id << endl;
						enemy.show_explosion_bullet(player.bulletsLeft[i].sprite.getPosition());
						enemy.healthValue -= player.bulletDamage;
						// cout << "enemy1 health: " << healthValue << endl;
						player.bulletsLeft[i].sprite.setColor(Color(0, 0, 0, 0));
					}
				}
			}
		}
		for (i = 0; i < player.bulletsRight.size(); i++)
		{
			if (Collision::BoundingBoxTest(enemy.enemy1Sprite, player.bulletsRight[i].sprite))
			{
				if (find(enemy.prevCollidedObj.begin(), enemy.prevCollidedObj.end(), player.bulletsRight[i].id) == enemy.prevCollidedObj.end())
				{
					if (Collision::PixelPerfectTest(enemy.enemy1Sprite, player.bulletsRight[i].sprite))
					{
						enemy.prevCollidedObj.push_back(player.bulletsRight[i].id);
						// cout << "hit bullet: " << id << endl;
						enemy.show_explosion_bullet(player.bulletsRight[i].sprite.getPosition());
						enemy.healthValue -= player.bulletDamage;
						// cout << "enemy1 health: " << healthValue << endl;
						player.bulletsRight[i].sprite.setColor(Color(0, 0, 0, 0));
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
	if (player.playerHealth.healthValue > 0)
	{
		for (i = 0; i < enemy.bulletsLeft.size(); i++)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, enemy.bulletsLeft[i].sprite)) // fix create loop to check bullets
			{
				if (find(player.prevCollidedObj.begin(), player.prevCollidedObj.end(), enemy.bulletsLeft[i].id) == player.prevCollidedObj.end())
				{
					if (Collision::PixelPerfectTest(player.playerSprite, enemy.bulletsLeft[i].sprite))
					{
						player.prevCollidedObj.push_back(enemy.bulletsLeft[i].id);
						// cout << "hit bullet: " << id << endl;
						player.show_explosion_bullet(Vector2f(enemy.bulletsLeft[i].sprite.getGlobalBounds().left + enemy.bulletsLeft[i].sprite.getGlobalBounds().width, enemy.bulletsLeft[i].sprite.getGlobalBounds().top + enemy.bulletsLeft[i].sprite.getGlobalBounds().height));
						player.playerHealth.healthValue -= enemy.bulletDamage;
						// cout << "player health: " << playerHealth.healthValue << endl;
						enemy.bulletsLeft[i].sprite.setColor(Color(0, 0, 0, 0));
					}
				}
			}
		}
		for (i = 0; i < enemy.bulletsRight.size(); i++)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, enemy.bulletsRight[i].sprite)) // fix create loop to check bullets
			{
				if (find(player.prevCollidedObj.begin(), player.prevCollidedObj.end(), enemy.bulletsRight[i].id) == player.prevCollidedObj.end())
				{
					if (Collision::PixelPerfectTest(player.playerSprite, enemy.bulletsRight[i].sprite))
					{
						player.prevCollidedObj.push_back(enemy.bulletsRight[i].id);
						// cout << "hit bullet: " << id << endl;
						player.show_explosion_bullet(Vector2f(enemy.bulletsRight[i].sprite.getGlobalBounds().left + enemy.bulletsRight[i].sprite.getGlobalBounds().width, enemy.bulletsRight[i].sprite.getGlobalBounds().top + enemy.bulletsRight[i].sprite.getGlobalBounds().height));
						player.playerHealth.healthValue -= enemy.bulletDamage;
						// cout << "player health: " << playerHealth.healthValue << endl;
						enemy.bulletsRight[i].sprite.setColor(Color(0, 0, 0, 0));
					}
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
			if (Collision::BoundingBoxTest(enemy.enemy1Sprite, player.missiles[i].sprite))
			{
				if (find(enemy.prevCollidedObj.begin(), enemy.prevCollidedObj.end(), player.missiles[i].id) == enemy.prevCollidedObj.end())
				{
					if (Collision::PixelPerfectTest(enemy.enemy1Sprite, player.missiles[i].sprite))
					{
						enemy.prevCollidedObj.push_back(player.missiles[i].id);
						// cout << "hit bullet: " << id << endl;
						enemy.show_explosion_missile(player.missiles[i].sprite.getPosition());
						enemy.healthValue -= player.missileDamage;
						// cout << "enemy1 health: " << healthValue << endl;
						player.missiles[i].sprite.setColor(Color(0, 0, 0, 0));
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
	if (player.playerHealth.healthValue > 0)
	{
		for (i = 0; i < enemy.missiles.size(); i++)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, enemy.missiles[i].sprite))
			{
				if (find(player.prevCollidedObj.begin(), player.prevCollidedObj.end(), enemy.missiles[i].id) == player.prevCollidedObj.end())
				{
					if (Collision::PixelPerfectTest(player.playerSprite, enemy.missiles[i].sprite))
					{
						player.prevCollidedObj.push_back(enemy.missiles[i].id);
						// cout << "hit missile: " << id << endl;
						player.show_explosion_missile(Vector2f(enemy.missiles[i].sprite.getGlobalBounds().left + enemy.missiles[i].sprite.getGlobalBounds().width, enemy.missiles[i].sprite.getGlobalBounds().top + enemy.missiles[i].sprite.getGlobalBounds().height));
						player.playerHealth.healthValue -= enemy.missileDamage;
						// cout << "player health: " << playerHealth.healthValue << endl;
						enemy.missiles[i].sprite.setColor(Color(0, 0, 0, 0));
					}
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
			if (Collision::BoundingBoxTest(enemy.enemy1Sprite, player.missiles[i].sprite))
			{
				if (find(enemy.prevCollidedObj.begin(), enemy.prevCollidedObj.end(), player.missiles[i].id) == enemy.prevCollidedObj.end())
				{
					if (Collision::PixelPerfectTest(enemy.enemy1Sprite, player.missiles[i].sprite))
					{
						enemy.prevCollidedObj.push_back(player.missiles[i].id);
						// cout << "hit bullet: " << id << endl;
						enemy.show_explosion_missile(player.missiles[i].sprite.getPosition());
						enemy.healthValue -= player.missileDamage;
						// cout << "enemy1 health: " << healthValue << endl;
						player.missiles[i].sprite.setColor(Color(0, 0, 0, 0));
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
	if (player.playerHealth.healthValue > 0)
	{
		for (i = 0; i < enemy.missiles.size(); i++)
		{
			if (Collision::BoundingBoxTest(player.playerSprite, enemy.missiles[i].sprite))
			{
				if (find(player.prevCollidedObj.begin(), player.prevCollidedObj.end(), enemy.missiles[i].id) == player.prevCollidedObj.end())
				{
					if (Collision::PixelPerfectTest(player.playerSprite, enemy.missiles[i].sprite))
					{
						player.prevCollidedObj.push_back(enemy.missiles[i].id);
						// cout << "hit missile: " << id << endl;
						player.show_explosion_missile(Vector2f(enemy.missiles[i].sprite.getGlobalBounds().left + enemy.missiles[i].sprite.getGlobalBounds().width, enemy.missiles[i].sprite.getGlobalBounds().top + enemy.missiles[i].sprite.getGlobalBounds().height));
						player.playerHealth.healthValue -= enemy.missileDamage;
						// cout << "player health: " << playerHealth.healthValue << endl;
						enemy.missiles[i].sprite.setColor(Color(0, 0, 0, 0));
					}
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