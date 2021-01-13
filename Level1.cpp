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
void Level1::Show(RenderWindow& window, Event& event){
	Texture backgroundTex;
	backgroundTex.loadFromFile("res/background.png");
	Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTex);
	LevelFailed levelFailedObj; // create levelFailed object to show level failed message
	LevelHelper levelhelper;
	Player yuri;				// our hero
	Enemy2 don;					// our villain
	don.setPosition(-200, -300, 100);
	while (window.isOpen()){
		Helper::resetClock();
		while (window.pollEvent(event)){
			if (event.type == Event::Closed)    window.close();
		}
		window.clear(Color::Black);
		window.draw(backgroundSprite);

		if (Mouse::isButtonPressed(Mouse::Left))    yuri.fireBullet();
		if (Mouse::isButtonPressed(Mouse::Right))   yuri.fireMissile();
		if (Keyboard::isKeyPressed(Keyboard::A))    yuri.moveLeft();
		if (Keyboard::isKeyPressed(Keyboard::D))    yuri.moveRight();
		if (Keyboard::isKeyPressed(Keyboard::W))    yuri.moveUp();
		if (Keyboard::isKeyPressed(Keyboard::S))    yuri.moveDown();
		don.move(300);
		don.fireBullet(2000, 500, 600);
		don.fireMissile(2000, 1000, 400);
		levelhelper.isHitBody(yuri, don);
		levelhelper.isHitBullet(yuri, don);
		levelhelper.isHitMissile(yuri, don);
		don.Show(window);
		yuri.Show(window);
		if (yuri.isDead)    levelFailedObj.Show(window, event);
		if (don.isDead) return;
		window.display();
	}
}
