#include "GameHandler.hpp"
#include "Helper.hpp"
#include "Level1.hpp" //include level headers
#include "Level2.hpp" //include level headers
#include "Level3.hpp" //include level headers
#include "Level100.hpp"
#include "Level101.hpp"
#include "Level102.hpp"
#include "level103.hpp"
#include "level104.hpp"
#include "level105.hpp"
#include "level106.hpp"
#include "level107.hpp"
#include "level108.hpp"
#include "level109.hpp"
#include "level110.hpp"
#include "level111.hpp"
#include "MainMenu.hpp"

using namespace std;
using namespace sf;

Font GetRes::boldFont;
Font GetRes::gameFont;
Font GetRes::techFont;
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
Texture GetRes::CompleteBody;
Texture GetRes::CompleteStar;
Texture GetRes::CompleteText;
Texture GetRes::CompleteButton;

void GameHandler::Start()
{
	window.create(VideoMode(1100, 900), "World War 3", Style::Default);
	window.setFramerateLimit(90);
	Helper::storeWindowSize(window.getSize().x, window.getSize().y);
	Helper::seedRand();
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
	cout << "level111" << endl;
	Level111 level111;				//create level object
    level111.Show(window, event); //show level

	cout << "level110" << endl;
	Level110 level110;				//create level object
    level110.Show(window, event); //show level

	cout << "level109" << endl;
	Level109 level109;				//create level object
    level109.Show(window, event); //show level

	cout << "level108" << endl;
	Level108 level108;				//create level object
    level108.Show(window, event); //show level

	cout << "level107" << endl;
	Level107 level107;				//create level object
    level107.Show(window, event); //show level

	cout << "level106" << endl;
	Level106 level106;				//create level object
    level106.Show(window, event); //show level

	cout << "level105" << endl;
	Level105 level105;				//create level object
    level105.Show(window, event); //show level

	cout << "level104" << endl;
	Level104 level104;				//create level object
    level104.Show(window, event); //show level

    cout << "level102" << endl;
	Level102 level102;				//create level object
    level102.Show(window, event); //show level

	cout << "level103" << endl;
	Level103 level103;				//create level object
    level103.Show(window, event); //show level

	cout << "level 101" << endl;
	Level101 level101;
	level101.Show(window,event);

	cout << "level100" << endl;
	Level100 level100;				//create level object
	level100.Show(window, event); //show level

	cout << "level1" << endl;
	Level1 level1;				//create level object
	level1.Show(window, event); //show level

	cout << "level2" << endl;
	Level2 level2;				//create level object
	level2.Show(window, event); //show level

	cout << "level3" << endl;
	Level3 level3;				//create level object
	level3.Show(window, event); //show level
}
