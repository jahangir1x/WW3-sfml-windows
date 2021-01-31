#ifndef Game_handler_air321
#define Game_handler_air321

#include "GetRes.hpp"
#include "MainMenu.hpp"

class GameHandler
{
public:
	void Start();
	void Help(RenderWindow& window, Event& event);
	void Credits(RenderWindow& window, Event& event);
	void ExitConfirm(RenderWindow& window, Event& event);
	void gameLoop();
	// add more level here
	sf::RenderWindow window;
	sf::Event event;
	GetRes resources;
	long long musicOffset;
	Music backMusic;

private:
	MainMenu::MenuResult result;
	MainMenu mainmenu;
	// static sf::Clock gameClock;
};
#endif
