#include "HelpMenu.hpp"
#include "CustomText.hpp"
#include "GameUI.hpp"
#include "Helper.hpp"
#include "LevelHelper.hpp"

using namespace std;
using namespace sf;

void HelpMenu::Show(RenderWindow& window, Event& event)
{
	Texture controlTex;
	Texture buttonTex;
	controlTex.loadFromFile("res/help_menu.png");
	controlTex.setSmooth(true);
	buttonTex.loadFromFile("res/back_button.png");
	Sprite ControlSprite(controlTex);
	Sprite buttonSprite(buttonTex);
	IntRect buttonRect(0, 0, 141.6, 84);
	buttonSprite.setTextureRect(buttonRect);
	buttonSprite.setPosition(10, 10);
	ControlSprite.setScale(Helper::getHeightScalingFactor(), Helper::getHeightScalingFactor());
	ControlSprite.setPosition(Helper::windowWidth() / 2 - ControlSprite.getGlobalBounds().width / 2, Helper::windowHeight() / 2 - ControlSprite.getGlobalBounds().height / 2);
	Clock buttonClock;
	bool shouldClose = false;
	int sign = 1;
	float buttonScale = 1;
	Vector2f mousePos;
	bool clickSoundPlayed = false;
	Sound clickSound;
	clickSound.setBuffer(GetRes::menuClickSound);

	GameUI::init();

	while (window.isOpen())
	{
		Helper::resetClock();
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				exit(0);
			}
			else if (event.type == Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					GameUI::handleClose(window, Mouse::getPosition(window));
					mousePos = Vector2f(Mouse::getPosition(window));
				}
			}
		}
		window.clear(Color(56, 56, 56));
		if (buttonClock.getElapsedTime().asSeconds() > 0.11 && shouldClose == false)
		{
			if (buttonRect.left >= buttonRect.width * 4)
			{
				sign = -1;
			}
			else if (buttonRect.left <= 0)
			{
				sign = 1;
			}
			buttonRect.left += buttonRect.width * sign;
			buttonSprite.setTextureRect(buttonRect);
			buttonClock.restart();
		}
		buttonSprite.setScale(buttonScale, buttonScale);
		if (buttonSprite.getGlobalBounds().contains(mousePos))
		{
			if (clickSoundPlayed == false)
			{
				clickSound.play();
				clickSoundPlayed = true;
			}
			shouldClose = true;
		}
		if (shouldClose == true && buttonClock.getElapsedTime().asSeconds() > 0.005)
		{
			if (buttonScale > 0)
			{
				buttonScale -= 0.03 * 90 * Helper::SecondsPerFrame();
				if (buttonScale < 0)
				{
					buttonScale = 0;
				}
			}
		}
		if (buttonScale <= 0)
		{
			return;
		}

		window.draw(ControlSprite);
		window.draw(buttonSprite);
		GameUI::showMenuUI(window);
		window.display();
	}
}