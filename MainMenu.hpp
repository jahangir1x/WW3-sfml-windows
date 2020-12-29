#ifndef MainMenu_air321
#define MainMenu_air321

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <bits/stdc++.h>

class MainMenu
{
public:
	enum MenuResult
	{
		Play,
		Help,
		Exit
	};
	struct MenuItem
	{
	public:
		sf::Rect<int> rect;
		MenuResult action;
	};
	MenuResult Show(sf::RenderWindow& window, sf::Event& menuEvent);

private:
	sf::Vector2i mousePosition;
	sf::Sprite menuSprite;
	MenuResult GetMenuResponse(sf::RenderWindow& window, sf::Event& menuEvent);
	std::vector<MenuItem> _menuItems;
};
#endif
