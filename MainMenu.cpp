#include "MainMenu.hpp"
using namespace std;
using namespace sf;
MainMenu::MenuResult MainMenu::Show(RenderWindow& window, Event& menuEvent)
{
	Texture menuTex;
	menuTex.loadFromFile("res/MainMenu_all.png");
	menuSprite.setTexture(menuTex);
	MenuItem playButton;
	playButton.rect.top = 218;
	playButton.rect.left = 219;
	playButton.rect.height = 122;
	playButton.rect.width = 559;
	playButton.action = Play;

	MenuItem helpButton;
	helpButton.rect.top = 412;
	helpButton.rect.left = 219;
	helpButton.rect.height = 122;
	helpButton.rect.width = 559;
	helpButton.action = Help;

	MenuItem exitButton;
	exitButton.rect.top = 606;
	exitButton.rect.left = 219;
	exitButton.rect.height = 122;
	exitButton.rect.width = 559;
	exitButton.action = Exit;

	_menuItems.push_back(playButton);
	_menuItems.push_back(helpButton);
	_menuItems.push_back(exitButton);

	window.draw(menuSprite);
	window.display();

	return GetMenuResponse(window, menuEvent);
}

MainMenu::MenuResult MainMenu::GetMenuResponse(RenderWindow& window, Event& menuEvent)
{
	while (true)
	{
		while (window.isOpen())
		{

			while (window.pollEvent(menuEvent))
			{
				if (menuEvent.type == Event::Closed)
				{
					cout << "exiting from MainMenu\n";
					return Exit;
				}
			}
			mousePosition = Mouse::getPosition(window);

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				for (unsigned int i = 0; i < _menuItems.size(); i++)
				{
					if (_menuItems[i].rect.contains(Mouse::getPosition(window)))
					{
						return _menuItems[i].action;
					}
				}
			}
			window.clear();
			window.draw(menuSprite);
			window.display();
		}
	}
}