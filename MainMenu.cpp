#include "MainMenu.hpp"
#include "GetRes.hpp"

using namespace std;
using namespace sf;

MainMenu::MenuResult MainMenu::Show(RenderWindow& window, Event& menuEvent)
{
	gameLogoSprite.setTexture(GetRes::gameLogoTex);
	gameLogoSprite.setPosition(286, 46);

	playSprite.setTexture(GetRes::playButtonTex);
	playRect.left = 0;
	playRect.top = 0;
	playRect.width = 371;
	playRect.height = 148;
	playSprite.setTextureRect(playRect);
	playSprite.setPosition(366, 245);

	helpSprite.setTexture(GetRes::helpButtonTex);
	helpRect.left = 0;
	helpRect.top = 0;
	helpRect.width = 371;
	helpRect.height = 148;
	helpSprite.setTextureRect(helpRect);
	helpSprite.setPosition(366, 393);

	creditsSprite.setTexture(GetRes::creditsButtonTex);
	creditsRect.left = 0;
	creditsRect.top = 0;
	creditsRect.width = 371;
	creditsRect.height = 148;
	creditsSprite.setTextureRect(creditsRect);
	creditsSprite.setPosition(366, 541);

	exitSprite.setTexture(GetRes::exitButtonTex);
	exitRect.left = 0;
	exitRect.top = 0;
	exitRect.width = 371;
	exitRect.height = 148;
	exitSprite.setTextureRect(exitRect);
	exitSprite.setPosition(366, 689);

	clicked = false;

	while (window.isOpen())
	{
		while (window.pollEvent(menuEvent))
		{
			if (menuEvent.type == Event::MouseMoved)
			{
				mousePosition = Mouse::getPosition(window);
			}
			else if (menuEvent.type == Event::Closed)
			{
				// cout << "exiting from menu\n";
				return Exit;
			}
		}

		if (playClock.getElapsedTime().asSeconds() > 0.08)
		{
			if (!clicked)
			{
				if (playSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
				{
					// cout << "mouse" << endl;
					if (playRect.left < 2597)
					{
						playRect.left += playRect.width;
						playSprite.setTextureRect(playRect);
					}
				}
				else if (playRect.left > 0)
				{
					playRect.left -= playRect.width;
					playSprite.setTextureRect(playRect);
				}
				playClock.restart();
			}
			else
			{
				// cout << "clicked";
				// clicked = false;
				return result;
			}
		}
		if (Mouse::isButtonPressed(Mouse::Left) && playSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			playRect.left = 2968;
			playSprite.setTextureRect(playRect);
			clicked = true;
			result = Play;
			cout << "result : play" << endl;
			playClock.restart();
		}

		if (helpClock.getElapsedTime().asSeconds() > 0.08)
		{
			if (!clicked)
			{
				if (helpSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
				{
					// cout << "mouse" << endl;
					if (helpRect.left < 2597)
					{
						helpRect.left += helpRect.width;
						helpSprite.setTextureRect(helpRect);
					}
				}
				else if (helpRect.left > 0)
				{
					helpRect.left -= helpRect.width;
					helpSprite.setTextureRect(helpRect);
				}
				helpClock.restart();
			}
			else
			{
				// cout << "clicked";
				// clicked = false;
				return result;
			}
		}
		if (Mouse::isButtonPressed(Mouse::Left) && helpSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			helpRect.left = 2968;
			helpSprite.setTextureRect(helpRect);
			clicked = true;
			result = Help;
			cout << "result : help" << endl;
			helpClock.restart();
		}

		if (creditsClock.getElapsedTime().asSeconds() > 0.08)
		{
			if (!clicked)
			{
				if (creditsSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
				{
					// cout << "mouse" << endl;
					if (creditsRect.left < 2597)
					{
						creditsRect.left += creditsRect.width;
						creditsSprite.setTextureRect(creditsRect);
					}
				}
				else if (creditsRect.left > 0)
				{
					creditsRect.left -= creditsRect.width;
					creditsSprite.setTextureRect(creditsRect);
				}
				creditsClock.restart();
			}
			else
			{
				// cout << "clicked";
				// clicked = false;
				return result;
			}
		}
		if (Mouse::isButtonPressed(Mouse::Left) && creditsSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			creditsRect.left = 2968;
			creditsSprite.setTextureRect(creditsRect);
			clicked = true;
			result = Credits;
			cout << "result : credits" << endl;
			creditsClock.restart();
		}

		if (exitClock.getElapsedTime().asSeconds() > 0.08)
		{
			if (!clicked)
			{
				if (exitSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
				{
					// cout << "mouse" << endl;
					if (exitRect.left < 2597)
					{
						exitRect.left += exitRect.width;
						exitSprite.setTextureRect(exitRect);
					}
				}
				else if (exitRect.left > 0)
				{
					exitRect.left -= exitRect.width;
					exitSprite.setTextureRect(exitRect);
				}
				exitClock.restart();
			}
			else
			{
				// cout << "clicked";
				// clicked = false;
				return result;
			}
		}
		if (Mouse::isButtonPressed(Mouse::Left) && exitSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			exitRect.left = 2968;
			exitSprite.setTextureRect(exitRect);
			clicked = true;
			result = Exit;
			cout << "result : exit" << endl;
			exitClock.restart();
		}

		window.clear(Color::Black);
		window.draw(gameLogoSprite);
		window.draw(playSprite);
		window.draw(helpSprite);
		window.draw(creditsSprite);
		window.draw(exitSprite);
		window.display();
	}
	return Nothing;
}