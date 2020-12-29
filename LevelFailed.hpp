#ifndef LevelFailed_air321
#define LevelFailed_air321

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <bits/stdc++.h>

using namespace sf; // don't forget this or you would have to initialize everything with sf::
class LevelFailed
{
public:
	void Show(RenderWindow& window, Event& event);
};
#endif
