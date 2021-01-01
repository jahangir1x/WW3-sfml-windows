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
	LevelFailed levelFailedObj; // create levelFailed object to show level failed message
	Player yuri(window); // our hero
	Enemy1 doe(window); // our villain
	doe.enemy1Sprite.setPosition(100,300); // set villain position randomly
	GameHandler gamehandler;
	Texture mouseTexture;
	mouseTexture.loadFromFile("res/player_bullet.png");
	Sprite mouseSprite;
	mouseSprite.setTexture(mouseTexture);

	while (window.isOpen())
	{
		gamehandler.setClock();
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (event.type == Event::MouseMoved)
			{
				// cout << "mouse: " << mouseRect.left << " " << mouseRect.top << " " << mouseRect.left + mouseRect.width << " " << mouseRect.top + mouseRect.height << endl;
				// mouseSprite.setPosition(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
				// yuri.isHit(mouseSprite, 5);
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
		doe.move_to(Vector2f(window.getSize().x/2 - 100,window.getSize().y/2),3000,1000,400,200);
		// doe.fireBullet_to(Vector2f(yuri.playerSprite.getPosition().x, yuri.playerSprite.getPosition().y),0,2,5000,250);
		// doe.fireMissile_to(Vector2f(yuri.playerSprite.getPosition().x, yuri.playerSprite.getPosition().y),0,2, 4000, 250);
		window.clear(Color::Black);

		doe.Show(window);
		yuri.Show(window);
		if (yuri.isDead)
			levelFailedObj.Show(window, event);
		window.draw(mouseSprite);
		// window.draw(someThing);
		window.display();
	}
}
