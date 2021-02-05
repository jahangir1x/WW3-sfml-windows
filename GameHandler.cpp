#include "GameHandler.hpp"
#include "CreditsMenu.hpp"
#include "EndScene.hpp"
#include "GetRes.hpp"
#include "HelpMenu.hpp"
#include "Helper.hpp"
#include "Level1.hpp" //include level headers
#include "Level10.hpp"
#include "Level11.hpp"
#include "Level12.hpp"
#include "Level13.hpp"
#include "Level14.hpp"
#include "Level2.hpp" //include level headers
#include "Level3.hpp" //include level headers
#include "Level4.hpp"
#include "Level5.hpp"
#include "Level6.hpp"
#include "Level7.hpp"
#include "Level8.hpp"
#include "Level9.hpp"
#include "LevelBoss1.hpp"
#include "LevelBoss3p.hpp"
#include "LevelBoss4.hpp"
#include "LevelBoss4p.hpp"
#include "LevelBoss5p.hpp"
#include "LevelBoss6.hpp"
#include "LevelBoss6p.hpp"
#include "LevelBossFinal.hpp"
#include "LevelBossI2.hpp"
#include "LevelBossI4.hpp"
#include "LevelBossI6.hpp"
#include "LevelHelper.hpp"
#include "LevelInversed1.hpp"
#include "LevelInversed2.hpp"
#include "LevelInversed3.hpp"
#include "LevelInversed4.hpp"
#include "LevelPuzzle1.hpp"
#include "LevelPuzzle2.hpp"
#include "LevelTutorial.hpp"
#include "Loading.hpp"
#include "MainMenu.hpp"
#include "Player.hpp"
#include "Story.hpp"

using namespace std;
using namespace sf;

void GameHandler::Start()
{
	window.create(VideoMode(1100, 768), "World War 3", Style::Fullscreen); // invalid resolution is intentional
	window.setFramerateLimit(90);
	window.setMouseCursorVisible(false);
	View view(FloatRect(0, 0, window.getSize().x * 1080.0 / window.getSize().y, 1080.0));
	window.setView(view);
	// Helper::storeWindowSize(window.getSize().x, window.getSize().y);
	Helper::storeWindowSize(view.getSize().x, view.getSize().y);
	Helper::seedRand();

	backMusic.openFromFile("res/music/MenuBackSound.wav");
	backMusic.setLoop(true);
	backMusic.setVolume(80);
	backMusic.play();

	Loading loading;
	loading.Show(window, event);

	resources.init();
	srand(time(0));

	gameLoop();
}

void GameHandler::Help(RenderWindow& window, Event& event)
{
	cout << "help" << endl;
	HelpMenu help;
	help.Show(window, event);
	return;
}

void GameHandler::Credits(RenderWindow& window, Event& event)
{
	cout << "credits" << endl;
	CreditsMenu credits;
	credits.Show(window, event);
	return;
}

void GameHandler::ExitConfirm(RenderWindow& window, Event& event)
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

			// test region -----------------

			// EndScene eendscene;
			// eendscene.Show(window, event);
			// if (LevelHelper::retriesLeft == 0)
			// {
			// 	LevelHelper::retriesLeft = 6;
			// 	continue;
			// }

			// test region ---------------------

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

			cout << "level1" << endl;
			Level1 level1;
			level1.Show(window, event);
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
			cout << "levelpuzzle1" << endl;
			LevelPuzzle1 levelpuzzle1;
			levelpuzzle1.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}
			cout << "levelinversed1" << endl;
			LevelInversed1 levelinversed1;
			levelinversed1.Show(window, event);
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
			cout << "levelboss1" << endl;
			LevelBoss1 levelboss1;
			levelboss1.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}
			cout << "levelpuzzle2" << endl;
			LevelPuzzle2 levelpuzzle2;
			levelpuzzle2.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}
			cout << "level4" << endl;
			Level4 level4;
			level4.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}
			cout << "levelboss3p" << endl;
			LevelBoss3p levelboss3p;
			levelboss3p.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}
			Level5 level5;
			level5.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}

			LevelBoss4p levelboss4p;
			levelboss4p.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}
			Level6 level6;
			level6.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}
			LevelBossI2 levelbossi2;
			levelbossi2.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}
			Level7 level7;
			level7.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}
			LevelBoss4 levelboss4;
			levelboss4.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}
			Level8 level8;
			level8.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}
			LevelBossI4 levelbossi4;
			levelbossi4.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}
			Level9 level9;
			level9.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}
			LevelInversed2 levelinversed2;
			levelinversed2.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}
			Level10 level10;
			level10.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}
			LevelBoss6 levelboss6;
			levelboss6.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}
			LevelInversed3 levelinversed3;
			levelinversed3.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}
			LevelBoss5p levelboss5p;
			levelboss5p.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}

			// beta test done----

			Level11 level11;
			level11.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}
			LevelInversed4 level1inversed4;
			level1inversed4.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}
			Level12 level12;
			level12.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}
			LevelBoss6p levelboss6p;
			levelboss6p.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}
			LevelBossI6 levelbossi6;
			levelbossi6.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}
			Level13 level13;
			level13.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}
			Level14 level14;
			level14.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}
			LevelBossFinal levelbossfinal;
			levelbossfinal.Show(window, event);
			if (LevelHelper::retriesLeft == 0)
			{
				LevelHelper::retriesLeft = 6;
				continue;
			}
			EndScene endscene;
			endscene.Show(window, event);
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
