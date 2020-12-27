#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <bits/stdc++.h>
using namespace std;
using namespace sf;
float slope_angle(float x1, float y1, float x2, float y2);

float slope_angle(float x1, float y1, float x2, float y2)
{
	return atan2((y2 - y1), (x2 - x1)) * 180.0 / 3.14159;
}

int main(void)
{
	RenderWindow window(VideoMode(1000, 1000), "SFFFF", Style::Titlebar | Style::Close);
	Event event;
	Clock gameClock;
	Vector2i globalposition;
	Texture playerTex;
	playerTex.loadFromFile("res/player_sprite.png");
	Sprite playerSprite;
	playerSprite.setTexture(playerTex);
	IntRect playerRect(0, 0, 120, 310);
	playerSprite.setTextureRect(playerRect);

	float dt;
	Texture bananaTex;
	bananaTex.loadFromFile("res/banana.png");
	Sprite bananaSprite(bananaTex);
	bananaSprite.setOrigin(0, 24);
	bananaSprite.setPosition(50, 108);
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				globalposition = Mouse::getPosition(window);
				if (event.key.code == Keyboard::Escape)
				{
					cout << "the escape key was pressed" << endl;
					cout << "x: " << globalposition.x << " y: " << globalposition.y << endl;
				}
			}
			else if (event.type == Event::Closed)
			{
				window.close();
			}
			else if (event.type == Event::MouseMoved)
			{
				globalposition = Mouse::getPosition(window);
				bananaSprite.setRotation(slope_angle(bananaSprite.getPosition().x, bananaSprite.getPosition().y, globalposition.x, globalposition.y));
			}
			// else if (event.type == Event::MouseMoved)
			// {
			// 	globalposition = Mouse::getPosition(window);
			// 	baseballSprite.setRotation(slope_angle(baseballPosx, baseballPosy, globalposition.x, globalposition.y));
			// }
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			dt = gameClock.getElapsedTime().asSeconds();
			playerSprite.move(0.7 * dt, 0);
			bananaSprite.move(0.7 * dt, 0);
			if (gameClock.getElapsedTime().asSeconds() > 0.3)
			{
				if (playerRect.left == 720)
				{
					playerRect.left = 0;
				}
				else
				{
					playerRect.left += 120;
				}
				// cout << "left: " << playerRect.left << endl;
				playerSprite.setTextureRect(playerRect);
				gameClock.restart();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			dt = gameClock.getElapsedTime().asSeconds();
			playerSprite.move(-0.7 * dt, 0);
			bananaSprite.move(-0.7 * dt, 0);
			if (gameClock.getElapsedTime().asSeconds() > 0.3)
			{
				if (playerRect.left == 0)
				{
					playerRect.left = 720;
				}
				else
				{
					playerRect.left -= 120;
				}
				// cout << "left: " << playerRect.left << endl;
				playerSprite.setTextureRect(playerRect);
				gameClock.restart();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			dt = gameClock.getElapsedTime().asSeconds();
			playerSprite.move(0, 0.7 * dt);
			bananaSprite.move(0, 0.7 * dt);
			if (gameClock.getElapsedTime().asSeconds() > 0.3)
			{
				if (playerRect.left == 720)
				{
					playerRect.left = 0;
				}
				else
				{
					playerRect.left += 120;
				}
				// cout << "left: " << playerRect.left << endl;
				playerSprite.setTextureRect(playerRect);
				gameClock.restart();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			dt = gameClock.getElapsedTime().asSeconds();
			playerSprite.move(0, -0.7 * dt);
			bananaSprite.move(0, -0.7 * dt);
			if (gameClock.getElapsedTime().asSeconds() > 0.3)
			{
				if (playerRect.left == 0)
				{
					playerRect.left = 720;
				}
				else
				{
					playerRect.left -= 120;
				}
				// cout << "left: " << playerRect.left << endl;
				playerSprite.setTextureRect(playerRect);
				gameClock.restart();
			}
		}
		window.clear();
		window.draw(playerSprite);
		window.draw(bananaSprite);
		window.display();
	}
	return 0;
}
