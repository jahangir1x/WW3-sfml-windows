#ifndef Game_handler_air321
#define Game_handler_air321

#include "MainMenu.hpp"

class GameHandler
{
public:
	void Start();
	void ShowMenu();
	void Help();
	void Credits();
	void Play();
	void ExitConfirm();
	// add more level here
	sf::RenderWindow window;
	sf::Event event;

private:
	MainMenu::MenuResult result;
	MainMenu mainmenu;
	// static sf::Clock gameClock;
};
#endif
