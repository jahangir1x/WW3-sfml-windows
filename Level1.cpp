#include "Level1.hpp" // level header file
#include "Collision.h"
#include "Enemy1.hpp"
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
	LevelFailed levelFailedObj;				// create levelFailed object to show level failed message
	Player yuri(window);					// our hero
	Enemy1 doe(window);						// our villain
	doe.enemy1Sprite.setPosition(-500, -500); // set villain position randomly
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
					cout << "player:" << yuri.playerSprite.getPosition().x << " " << yuri.playerSprite.getPosition().y << endl;
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
		doe.move_to(Vector2f(300, 300), 200, 200);
		doe.fireBullet(2000, 1000, 100);
		doe.fireMissile(4000, 1000, 50);

		yuri.isHit(doe.enemy1Sprite, 1, 8, false);
		for (i = 0; i < doe.bulletsLeft.size(); i++)
		{
			yuri.isHit(doe.bulletsLeft[i].sprite, doe.bulletsLeft[i].id, 5);
			yuri.isHit(doe.bulletsRight[i].sprite, doe.bulletsRight[i].id, 5);
		}
		for (i = 0; i < doe.missiles.size(); i++)
		{
			yuri.isHit(doe.missiles[i].sprite, doe.missiles[i].id, 9);
		}
		doe.isHit(yuri.playerSprite, 1, 8, false);
		for ( i = 0; i < yuri.bulletsLeft.size(); i++)
		{
			doe.isHit(yuri.bulletsLeft[i].sprite, yuri.bulletsLeft[i].id, 5);
			doe.isHit(yuri.bulletsRight[i].sprite, yuri.bulletsRight[i].id, 5);
		}
		for (i = 0; i< yuri.missiles.size(); i++){
			doe.isHit(yuri.missiles[i].sprite, yuri.missiles[i].id, 9);
		}

		window.draw(backgroundSprite);
		doe.Show(window);
		yuri.Show(window);
		if (yuri.isDead && yuri.explosionFin)
			levelFailedObj.Show(window, event);
		window.display();
	}
}
