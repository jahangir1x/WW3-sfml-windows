#ifndef Game_handler_air321
#define Game_handler_air321

#include "MainMenu.hpp"

class GameHandler
{
public:
	void Start();
	void Help();
	void Credits();
	void ExitConfirm();
	void gameLoop();
	// add more level here
	sf::RenderWindow window;
	sf::Event event;

private:
	MainMenu::MenuResult result;
	MainMenu mainmenu;
	// static sf::Clock gameClock;
};
#endif
