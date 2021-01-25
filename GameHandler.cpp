#include "GameHandler.hpp"
#include "GetRes.hpp"
#include "Helper.hpp"
#include "Level1.hpp" //include level headers
#include "Level2.hpp" //include level headers
#include "Level3.hpp" //include level headers
#include "MainMenu.hpp"

using namespace std;
using namespace sf;

Font GetRes::boldFont;
Font GetRes::gameFont;
Texture GetRes::explosionTex;
Texture GetRes::gameLogoTex;
Texture GetRes::creditsButtonTex;
Texture GetRes::exitButtonTex;
Texture GetRes::helpButtonTex;
Texture GetRes::playButtonTex;
Texture GetRes::enemyBulletTex;
Texture GetRes::enemyMissileTex;
Texture GetRes::enemyBodyTex1;
Texture GetRes::enemyBodyTex2;
Texture GetRes::enemyBodyTex3;
Texture GetRes::enemyBodyTex4;
Texture GetRes::enemyBodyTex5;
Texture GetRes::enemyBodyTex6;
Texture GetRes::enemyBodyTex7;
Texture GetRes::playerBulletTex;
Texture GetRes::playerMissileTex;
Texture GetRes::playerBodyTex;
Texture GetRes::seaTex;
Texture GetRes::seaElem1;
Texture GetRes::seaElem2;

void GameHandler::Start()
{
	window.create(VideoMode(1100, 900), "World War 3", Style::Default);
	window.setFramerateLimit(90);
	Helper::storeWindowSize(window.getSize().x, window.getSize().y);
	Helper::seedRand();
	GetRes gettexture;
	srand(time(0));

	ShowMenu();
}

void GameHandler::ShowMenu()
{
	result = mainmenu.Show(window, event);
	if (result == MainMenu::Play)
	{
		Play();
	}
	else if (result == MainMenu::Help)
	{
		Help();
	}
	else if (result == MainMenu::Credits)
	{
		Credits();
	}
	else if (result == MainMenu::Exit)
	{
		ExitConfirm();
	}
}

void GameHandler::Help()
{
	cout << "help" << endl;
}

void GameHandler::Credits()
{
	cout << "credits" << endl;
}

void GameHandler::ExitConfirm()
{
	cout << "exitconfirm" << endl;
}

void GameHandler::Play()
{
	cout << "level3" << endl;
	Level3 level3;				//create level object
	level3.Show(window, event); //show level
	cout << "level1" << endl;
	Level1 level1;				//create level object
	level1.Show(window, event); //show level

	cout << "level2" << endl;
	Level2 level2;				//create level object
	level2.Show(window, event); //show level

}
