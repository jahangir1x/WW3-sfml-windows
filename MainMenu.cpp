#include "MainMenu.hpp"
#include "GameUI.hpp"
#include "GetRes.hpp"
#include "Helper.hpp"

using namespace std;
using namespace sf;

MainMenu::MenuResult MainMenu::Show(RenderWindow& window, Event& menuEvent)
{
	GameUI::init();
	gameLogoSprite.setTexture(GetRes::gameLogoTex);
	gameLogoSprite.setPosition(Helper::windowWidth() / 2 - gameLogoSprite.getGlobalBounds().width / 2, 30);
	menuBackSprite.setTexture(GetRes::menuBackTex);
	widthScale = Helper::windowWidth() / menuBackSprite.getGlobalBounds().width;
	heightScale = Helper::windowHeight() / menuBackSprite.getGlobalBounds().height;
	menuBackSprite.setScale(max(widthScale, heightScale), max(widthScale, heightScale));
	menuBackSprite.setPosition(0, 0);

	playSprite.setTexture(GetRes::playButtonTex);
	playRect.left = 0;
	playRect.top = 0;
	playRect.width = 371;
	playRect.height = 148;
	playSprite.setTextureRect(playRect);
	playSprite.setPosition(Helper::windowWidth() / 2 - playSprite.getGlobalBounds().width / 2, gameLogoSprite.getGlobalBounds().top + gameLogoSprite.getGlobalBounds().height + 40);

	helpSprite.setTexture(GetRes::helpButtonTex);
	helpRect.left = 0;
	helpRect.top = 0;
	helpRect.width = 371;
	helpRect.height = 148;
	helpSprite.setTextureRect(helpRect);
	helpSprite.setPosition(Helper::windowWidth() / 2 - helpSprite.getGlobalBounds().width / 2, ((Helper::windowHeight() - gameLogoSprite.getGlobalBounds().top - gameLogoSprite.getGlobalBounds().height - 40) / 4.0) + gameLogoSprite.getGlobalBounds().top + gameLogoSprite.getGlobalBounds().height + 40);

	creditsSprite.setTexture(GetRes::creditsButtonTex);
	creditsRect.left = 0;
	creditsRect.top = 0;
	creditsRect.width = 371;
	creditsRect.height = 148;
	creditsSprite.setTextureRect(creditsRect);
	creditsSprite.setPosition(Helper::windowWidth() / 2 - creditsSprite.getGlobalBounds().width / 2, ((Helper::windowHeight() - gameLogoSprite.getGlobalBounds().top - gameLogoSprite.getGlobalBounds().height - 40) / 4.0 * 2.0) + gameLogoSprite.getGlobalBounds().top + gameLogoSprite.getGlobalBounds().height + 40);

	exitSprite.setTexture(GetRes::exitButtonTex);
	exitRect.left = 0;
	exitRect.top = 0;
	exitRect.width = 371;
	exitRect.height = 148;
	exitSprite.setTextureRect(exitRect);
	exitSprite.setPosition(Helper::windowWidth() / 2 - exitSprite.getGlobalBounds().width / 2, ((Helper::windowHeight() - gameLogoSprite.getGlobalBounds().top - gameLogoSprite.getGlobalBounds().height - 40) / 4.0 * 3.0) + gameLogoSprite.getGlobalBounds().top + gameLogoSprite.getGlobalBounds().height + 40);

	clicked = false;
	result = Nothing;
	menuHover.setBuffer(GetRes::menuHoverSound);
	menuClick.setBuffer(GetRes::menuClickSound);
	hoverSoundPlayed = false;
	clickSoundPlayed = false;

	Helper::resetClock();

	while (window.isOpen())
	{
		while (window.pollEvent(menuEvent))
		{
			if (menuEvent.type == Event::MouseMoved)
			{
				mousePosition = Mouse::getPosition(window);
			}
			else if (menuEvent.type == Event::MouseButtonReleased && menuEvent.mouseButton.button == Mouse::Left)
			{
				mousePositionClicked = Mouse::getPosition(window);
				GameUI::handleClose(window, mousePositionClicked);
				clicked = true;
				menuClock.restart();
			}
			else if (menuEvent.type == Event::Closed)
			{
				// cout << "exiting from menu\n";
				return Exit;
			}
		}

		// music.play();

		if (playClock.getElapsedTime().asSeconds() > 0.08)
		{
			// if (!clicked)
			// {
			if (playSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
			{
				// cout << "mouse" << endl;
				if (playRect.left < 2597)
				{
					if (hoverSoundPlayed == false)
					{
						menuHover.play();
						hoverSoundPlayed = true;
					}
					playRect.left += playRect.width;
					playSprite.setTextureRect(playRect);
				}
			}
			else if (playRect.left > 0)
			{
				hoverSoundPlayed = false;
				playRect.left -= playRect.width;
				playSprite.setTextureRect(playRect);
			}
			playClock.restart();
		}
		if (clicked && playSprite.getGlobalBounds().contains(mousePositionClicked.x, mousePositionClicked.y))
		{
			if (clickSoundPlayed == false)
			{
				menuClick.play();
				clickSoundPlayed = true;
			}
			playRect.left = 2969;
			playSprite.setTextureRect(playRect);
			result = Play;
			cout << "result : play" << endl;
			playClock.restart();
		}

		if (helpClock.getElapsedTime().asSeconds() > 0.08)
		{
			if (helpSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
			{
				// cout << "mouse" << endl;
				if (helpRect.left < 2597)
				{
					if (hoverSoundPlayed == false)
					{
						menuHover.play();
						hoverSoundPlayed = true;
					}
					helpRect.left += helpRect.width;
					helpSprite.setTextureRect(helpRect);
				}
			}
			else if (helpRect.left > 0)
			{
				hoverSoundPlayed = false;
				helpRect.left -= helpRect.width;
				helpSprite.setTextureRect(helpRect);
			}
			helpClock.restart();
		}
		if (clicked && helpSprite.getGlobalBounds().contains(mousePositionClicked.x, mousePositionClicked.y))
		{
			if (clickSoundPlayed == false)
			{
				menuClick.play();
				clickSoundPlayed = true;
			}
			helpRect.left = 2969;
			helpSprite.setTextureRect(helpRect);

			result = Help;
			cout << "result : help" << endl;
			helpClock.restart();
		}

		if (creditsClock.getElapsedTime().asSeconds() > 0.08)
		{
			if (creditsSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
			{
				// cout << "mouse" << endl;
				if (creditsRect.left < 2597)
				{
					if (hoverSoundPlayed == false)
					{
						menuHover.play();
						hoverSoundPlayed = true;
					}
					creditsRect.left += creditsRect.width;
					creditsSprite.setTextureRect(creditsRect);
				}
			}
			else if (creditsRect.left > 0)
			{
				hoverSoundPlayed = false;
				creditsRect.left -= creditsRect.width;
				creditsSprite.setTextureRect(creditsRect);
			}
			creditsClock.restart();
		}
		if (clicked && creditsSprite.getGlobalBounds().contains(mousePositionClicked.x, mousePositionClicked.y))
		{
			if (clickSoundPlayed == false)
			{
				menuClick.play();
				clickSoundPlayed = true;
			}
			creditsRect.left = 2969;
			creditsSprite.setTextureRect(creditsRect);

			result = Credits;
			cout << "result : credits" << endl;
			creditsClock.restart();
		}

		if (exitClock.getElapsedTime().asSeconds() > 0.08)
		{
			if (exitSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
			{
				// cout << "mouse" << endl;
				if (exitRect.left < 2597)
				{
					if (hoverSoundPlayed == false)
					{
						menuHover.play();
						hoverSoundPlayed = true;
					}
					exitRect.left += exitRect.width;
					exitSprite.setTextureRect(exitRect);
				}
			}
			else if (exitRect.left > 0)
			{
				hoverSoundPlayed = false;
				exitRect.left -= exitRect.width;
				exitSprite.setTextureRect(exitRect);
			}
			exitClock.restart();
		}
		if (clicked && exitSprite.getGlobalBounds().contains(mousePositionClicked.x, mousePositionClicked.y))
		{
			if (clickSoundPlayed == false)
			{
				menuClick.play();
				clickSoundPlayed = true;
			}
			exitRect.left = 2969;
			exitSprite.setTextureRect(exitRect);

			result = Exit;
			cout << "result : exit" << endl;
			exitClock.restart();
		}

		if (result != Nothing && menuClock.getElapsedTime().asSeconds() > 0.8)
		{
			return result;
		}

		window.clear(Color::White);
		window.draw(menuBackSprite);
		window.draw(gameLogoSprite);
		window.draw(playSprite);
		window.draw(helpSprite);
		window.draw(creditsSprite);
		window.draw(exitSprite);

		GameUI::showMenuUI(window);

		window.display();
	}
	return Nothing;
}