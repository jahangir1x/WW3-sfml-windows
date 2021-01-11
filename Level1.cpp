#include "Level1.hpp" // level header file
#include "Collision.h"
#include "Enemy1.hpp"
#include "Enemy2.hpp"
#include "GameHandler.hpp"
#include "LevelFailed.hpp" // level failed header file
#include "Player.hpp"

using namespace std;
using namespace sf;

void Level1::Show(RenderWindow& window, Event& event)
{
	unsigned int i;
	Texture backgroundTex;
	backgroundTex.loadFromFile("res/background.png");
	Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTex);
	LevelFailed levelFailedObj; // create levelFailed object to show level failed message
	Player yuri(window);		// our hero
	// Enemy2 doe(window);			// our villain
	Enemy1 don(window);
	// doe.enemy1Sprite.setPosition(300, 300); // set villain position randomly
	don.setPosition(-200,-300,100);
	GameHandler gamehandler;

	while (window.isOpen())
	{
		gamehandler.setClock();
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
				{
					cout << "mouse :" << Mouse::getPosition(window).x << " " << Mouse::getPosition(window).y << endl;
					cout << "enemy:" << don.enemy1Sprite.getPosition().x << " " << don.enemy1Sprite.getPosition().y << endl;
				}
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
			{
				return; // show next level
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::L)
			{
				levelFailedObj.Show(window, event); // show level failed message
			}
		}
		window.clear(Color::Black);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			yuri.fireBullet();
		}
		if (Mouse::isButtonPressed(Mouse::Right))
		{
			yuri.fireMissile();
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			yuri.moveLeft();
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			yuri.moveRight();
		}
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			yuri.moveUp();
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			yuri.moveDown();
		}
		// doe.move_to(300, 300, 100, 200);
		// doe.fireBullet(1000, 500, 400);
		// doe.fireMissile(2000, 1000, 400);
		don.move_to(400, 3000, 100);
		don.fireBullet(2000, 500, 600);
		don.fireMissile(2000, 1000, 400);

		// yuri.isHitBody(doe.enemy1Sprite, 8);
		// for (i = 0; i < doe.bulletsLeft.size(); i++)
		// {
		// 	yuri.isHitBullet(doe.bulletsLeft[i].sprite, doe.bulletsLeft[i].id, 5);
		// 	yuri.isHitBullet(doe.bulletsRight[i].sprite, doe.bulletsRight[i].id, 5);
		// }
		// for (i = 0; i < doe.missiles.size(); i++)
		// {
		// 	yuri.isHitMissile(doe.missiles[i].sprite, doe.missiles[i].id, 9);
		// }
		// doe.isHitBody(yuri.playerSprite, 8);
		// for (i = 0; i < yuri.bulletsLeft.size(); i++)
		// {
		// 	doe.isHitBullet(yuri.bulletsLeft[i].sprite, yuri.bulletsLeft[i].id, 5);
		// 	doe.isHitBullet(yuri.bulletsRight[i].sprite, yuri.bulletsRight[i].id, 5);
		// }
		// for (i = 0; i < yuri.missiles.size(); i++)
		// {
		// 	doe.isHitMissile(yuri.missiles[i].sprite, yuri.missiles[i].id, 9);
		// }

		yuri.isHitBody(don.enemy1Sprite, 8);
		for (i = 0; i < don.bulletsLeft.size(); i++)
		{
			yuri.isHitBullet(don.bulletsLeft[i].sprite, don.bulletsLeft[i].id, 5);
			yuri.isHitBullet(don.bulletsRight[i].sprite, don.bulletsRight[i].id, 5);
		}
		for (i = 0; i < don.missiles.size(); i++)
		{
			yuri.isHitMissile(don.missiles[i].sprite, don.missiles[i].id, 9);
		}
		don.isHitBody(yuri.playerSprite, 8);
		for (i = 0; i < yuri.bulletsLeft.size(); i++)
		{
			don.isHitBullet(yuri.bulletsLeft[i].sprite, yuri.bulletsLeft[i].id, 5);
			don.isHitBullet(yuri.bulletsRight[i].sprite, yuri.bulletsRight[i].id, 5);
		}
		for (i = 0; i < yuri.missiles.size(); i++)
		{
			don.isHitMissile(yuri.missiles[i].sprite, yuri.missiles[i].id, 9);
		}

		window.draw(backgroundSprite);
		// doe.Show(window);
		don.Show(window);
		yuri.Show(window);
		if (yuri.isDead && yuri.explosionFin)
			levelFailedObj.Show(window, event);
		window.display();
	}
}
