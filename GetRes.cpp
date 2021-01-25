#include "GetRes.hpp"
#include "Helper.hpp"
using namespace std;
using namespace sf;

GetRes::GetRes()
{
	boldFont.loadFromFile("res/Roboto-Bold.ttf");
	gameFont.loadFromFile("res/Roboto-Regular.ttf");
	explosionTex.loadFromFile("res/explosion.png");
	gameLogoTex.loadFromFile("res/game_logo.png");
	creditsButtonTex.loadFromFile("res/credits_button.png");
	exitButtonTex.loadFromFile("res/exit_button.png");
	helpButtonTex.loadFromFile("res/help_button.png");
	playButtonTex.loadFromFile("res/play_button.png");
	enemyBulletTex.loadFromFile("res/enemy_bullet.png");
	enemyMissileTex.loadFromFile("res/enemy_missile.png");
	enemyBodyTex1.loadFromFile("res/enemy1_spritesheet.png");
	enemyBodyTex2.loadFromFile("res/enemy2_spritesheet.png");
	enemyBodyTex3.loadFromFile("res/enemy3_spritesheet.png");
	enemyBodyTex4.loadFromFile("res/enemy4_spritesheet.png");
	enemyBodyTex5.loadFromFile("res/enemy5_spritesheet.png");
	enemyBodyTex6.loadFromFile("res/enemy6_spritesheet.png");
	enemyBodyTex7.loadFromFile("res/enemy7_spritesheet.png");
	playerBulletTex.loadFromFile("res/player_bullet.png");
	playerMissileTex.loadFromFile("res/player_missile.png");
	playerBodyTex.loadFromFile("res/player_spritesheet.png");
	seaTex.loadFromFile("res/sea.png");
	seaElem1.loadFromFile("res/sea_elem1.png");
	seaElem2.loadFromFile("res/sea_elem2.png");

	explosionTex.setSmooth(true);
	gameLogoTex.setSmooth(true);
	creditsButtonTex.setSmooth(true);
	exitButtonTex.setSmooth(true);
	helpButtonTex.setSmooth(true);
	playButtonTex.setSmooth(true);
	enemyBulletTex.setSmooth(true);
	enemyMissileTex.setSmooth(true);
	enemyBodyTex1.setSmooth(true);
	enemyBodyTex2.setSmooth(true);
	enemyBodyTex3.setSmooth(true);
	enemyBodyTex4.setSmooth(true);
	enemyBodyTex5.setSmooth(true);
	enemyBodyTex6.setSmooth(true);
	enemyBodyTex7.setSmooth(true);
	playerBulletTex.setSmooth(true);
	playerMissileTex.setSmooth(true);
	playerBodyTex.setSmooth(true);
	seaTex.setSmooth(true);
	seaElem1.setSmooth(true);
	seaElem2.setSmooth(true);
}