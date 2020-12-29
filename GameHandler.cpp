#include "GameHandler.hpp"
#include "Level1.hpp" //include level headers
#include "Level2.hpp" //include level headers
#include "Level3.hpp" //include level headers
#include "MainMenu.hpp"

using namespace std;
using namespace sf;

void GameHandler::Start()
{
	window.create(VideoMode(1000, 800), "CoolGame");

	ShowMenu();
}

void GameHandler::ShowMenu()
{
	MainMenu mainmenu;
	MainMenu::MenuResult result = mainmenu.Show(window, event);
	if (result == MainMenu::Play)
	{
		Play();
	}
	else if (result == MainMenu::Help)
	{
		Help();
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

void GameHandler::ExitConfirm()
{
	cout << "exitconfirm" << endl;
}

void GameHandler::Play()
{
	cout << "level1" << endl;
	Level1 level1;                  //create level object
	level1.Show(window, event);     //show level

	cout << "level2" << endl;
	Level2 level2;                  //create level object
	level2.Show(window, event);     //show level

	cout << "level3" << endl;
	Level3 level3;                  //create level object
	level3.Show(window, event);     //show level
}
