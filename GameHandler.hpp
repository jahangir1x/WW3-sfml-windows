#ifndef Game_handler_air321
#define Game_handler_air321

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <bits/stdc++.h>

extern float timePerFrame;
extern sf::Clock gameClock;

class GameHandler
{
public:
	void Start();
	void ShowMenu();
	void Help();
	void Play();
	void ExitConfirm();
	void setClock();
	float getElapsedTime();
	// add more level here
	sf::RenderWindow window;
	sf::Event event;

private:
	// static sf::Clock gameClock;
};
#endif
