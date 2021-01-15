#include "Level1.hpp" // level header file
#include "Collision.h"
#include "Enemy1.hpp"
#include "Enemy2.hpp"
#include "Helper.hpp"
#include "LevelFailed.hpp" // level failed header file
#include "LevelHelper.hpp"
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
	LevelHelper levelhelper;    // levelhelper to check collisions
	Player yuri; // our hero
	vector<Enemy2> enemies(3);  // 3 enemies
	while (window.isOpen())
	{
		Helper::resetClock();
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}
		window.clear(Color::Black);
		window.draw(backgroundSprite);
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
		for (i = 0; i < enemies.size() ; i++){
			enemies[i].move(300);
			enemies[i].fireBullet(6000, 1000, 400);
			enemies[i].fireMissile(7000, 1000, 300);
			levelhelper.isHitBody(yuri, enemies[i]);
			levelhelper.isHitBullet(yuri, enemies[i]);
			levelhelper.isHitMissile(yuri, enemies[i]);
			enemies[i].Show(window);
		}
		if(Helper::enemiesDied() == 3){
			return;
		}
		yuri.Show(window);
		if (yuri.isDead)
			levelFailedObj.Show(window, event);
		window.display();
	}
}
