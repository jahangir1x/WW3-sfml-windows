#include "GameHandler.hpp"
#include "CreditsMenu.hpp"
#include "EndScene.hpp"
#include "GetRes.hpp"
#include "HelpMenu.hpp"
#include "Helper.hpp"
#include "Level1.hpp" //include level headers
#include "Level100.hpp"
#include "Level101.hpp"
#include "Level102.hpp"
#include "Level103.hpp"
#include "Level104.hpp"
#include "Level105.hpp"
#include "Level106.hpp"
#include "Level107.hpp"
#include "Level108.hpp"
#include "Level109.hpp"
#include "Level110.hpp"
#include "Level111.hpp"
#include "Level112.hpp"
#include "Level2.hpp" //include level headers
#include "Level201.hpp"
#include "Level202.hpp"
#include "Level203.hpp"
#include "Level204.hpp"
#include "Level205.hpp"
#include "Level206.hpp"
#include "Level3.hpp" //include level headers
#include "LevelHelper.hpp"
#include "LevelTutorial.hpp"
#include "Loading.hpp"
#include "MainMenu.hpp"
#include "Player.hpp"
#include "Story.hpp"

using namespace std;
using namespace sf;

void GameHandler::Start()
{
	window.create(VideoMode(1100, 768), "World War 3", Style::Fullscreen);
	window.setFramerateLimit(90);
	window.setMouseCursorVisible(false);
	Helper::storeWindowSize(window.getSize().x, window.getSize().y);
	Helper::seedRand();
	Helper::setWidthScaling();
	Helper::setHeightScaling();

	backMusic.openFromFile("res/music/MenuBackSound.wav");
	backMusic.setLoop(true);
	backMusic.setVolume(30);
	backMusic.play();

	Loading loading;
	loading.Show(window, event);

	resources.init();
	srand(time(0));

	gameLoop();
}

void GameHandler::Help(RenderWindow &window, Event &event)
{
	cout << "help" << endl;
	HelpMenu help;
	help.Show(window, event);
	return;
}

void GameHandler::Credits(RenderWindow &window, Event &event)
{
	cout << "credits" << endl;
	CreditsMenu credits;
	credits.Show(window, event);
	return;
}

void GameHandler::ExitConfirm(RenderWindow &window, Event &event)
{
	cout << "exitconfirm" << endl;
	cout << window.getSize().x << event.type << endl;
}

void GameHandler::gameLoop()
{
	while (true)
	{
		Helper::resetClock();
		result = mainmenu.Show(window, event);
		if (result == MainMenu::Play)
		{
			backMusic.stop();
			// cout << "level1" << endl;
			// Level1 leevel1;
			// leevel1.Show(window, event);
			// if (LevelHelper::retriesLeft == 0)
			// {
			// 	LevelHelper::retriesLeft = 6;
			// 	continue;
			// }

			cout << "story" << endl;
			Story story;
			story.Show(window, event);

			cout << "tutorial" << endl;
			LevelTutorial tutorial;
			tutorial.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}

			cout << "level2" << endl;
			Level2 level2;
			level2.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}

			cout << "level3" << endl;
			Level3 level3;
			level3.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}

			cout << "level100" << endl;
			Level100 level100;
			level100.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}

			cout << "level102" << endl;
			Level102 level102;
			level102.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}

			cout << "level103" << endl;
			Level103 level103;
			level103.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}

			cout << "level205" << endl;
			Level205 level205;
			level205.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}

			cout << "level206" << endl;
			Level206 level206;
			level206.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}

			cout << "level104" << endl;
			Level104 level104;
			level104.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}
			cout << "level105" << endl;
			Level105 level105;
			level105.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}

			cout << "level106" << endl;
			Level106 level106;
			level106.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}

			cout << "level107" << endl;
			Level107 level107;
			level107.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}

			cout << "level201" << endl;
			Level201 level201;
			level201.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}

			cout << "level108" << endl;
			Level108 level108;
			level108.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}

			cout << "level109" << endl;
			Level109 level109;
			level109.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}
			cout << "level110" << endl;
			Level110 level110;
			level110.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}

			cout << "level203" << endl;
			Level203 level203;
			level203.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}

			cout << "level111" << endl;
			Level111 level111;
			level111.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}

			cout << "level202" << endl;
			Level202 level202;
			level202.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}

			cout << "level112" << endl;
			Level112 level112;
			level112.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}
			cout << "level101" << endl;
			Level101 level101;
			level101.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}

			Level204 level204;
			level204.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}

			cout << "level1" << endl;
			Level1 level1;
			level1.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}

			cout << "end" << endl;
			EndScene endScene;
			endScene.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}
		}
		else if (result == MainMenu::Help)
		{
			Help(window, event);
			continue;
		}
		else if (result == MainMenu::Credits)
		{
			Credits(window, event);
			continue;
		}
		else if (result == MainMenu::Exit)
		{
			ExitConfirm(window, event);
			exit(0);
		}
	}
}
