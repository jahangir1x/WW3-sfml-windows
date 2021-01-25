#include "GetRes.hpp"
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
	enemyBodyTex.loadFromFile("res/enemy_spritesheet.png");
	playerBulletTex.loadFromFile("res/player_bullet.png");
	playerMissileTex.loadFromFile("res/player_missile.png");
	playerBodyTex.loadFromFile("res/player_spritesheet.png");
	seaTex.loadFromFile("res/sea.png");
	seaElem1.loadFromFile("res/sea_elem1.png");
	seaElem2.loadFromFile("res/sea_elem2.png");
}