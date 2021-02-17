#include "CreditsMenu.hpp"
#include "CustomText.hpp"
#include "GameUI.hpp"
#include "Helper.hpp"
#include "LevelHelper.hpp"

using namespace std;
using namespace sf;

void CreditsMenu::Show(RenderWindow& window, Event& event)
{
	Texture teamLogoTex;
	Texture buttonTex;
	vector<string> strings {
		"---------------Team Members---------------",
		"Md. Jahangir Alam Rocky",
		"Md. Sourav",
		"Fouzia Zilani",
		""
		"-----------------Special Thanks to -----------------",
		"Prof. Dr. Iqbal Aziz Khan",
		"Nick Koirala",
		"ahnonay",
		"Suraj Sharma",
		"Daniel Noronha",
		"Tri Tachyon",
		"eXpl0it3r",
		"Laurent",
		"--------------------Special Special Thanks to--------------------",
		"YOU <3"
	};
	vector<Text> texts;
	texts.resize(strings.size());
	int offset = 0;
	for (unsigned int i = 0; i < strings.size(); i++)
	{
		texts[i].setString(strings[i]);
		texts[i].setFont(GetRes::techFont);
		texts[i].setCharacterSize(40);
		texts[i].setFillColor(Color(64, 191, 76));
		texts[i].setPosition(Helper::windowWidth() / 2 - texts[i].getGlobalBounds().width / 2, Helper::windowHeight() + offset);
		cout << "pos: " << texts[i].getPosition().x << " " << texts[i].getPosition().y << endl;

		offset += 70;
	}
	teamLogoTex.loadFromFile("res/team_logo.png");
	buttonTex.loadFromFile("res/back_button.png");
	Sprite ControlSprite(teamLogoTex);
	Sprite buttonSprite(buttonTex);
	IntRect buttonRect(0, 0, 141.6, 84);
	buttonSprite.setTextureRect(buttonRect);
	buttonSprite.setPosition(10, 10);
	// ControlSprite.setPosition(Helper::windowWidth() / 2 - ControlSprite.getGlobalBounds().width / 2, Helper::windowHeight() / 2 - ControlSprite.getGlobalBounds().height / 2);
	ControlSprite.setScale(0.6, 0.6);
	ControlSprite.setPosition(buttonSprite.getPosition().x, buttonSprite.getGlobalBounds().top + buttonSprite.getGlobalBounds().height + 20);
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
					mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
					GameUI::handleClose(window, mousePos);
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

		for (auto& text : texts)
		{
			text.move(0, -70 * Helper::SecondsPerFrame());
		}

		window.draw(ControlSprite);
		for (auto& text : texts)
		{
			window.draw(text);
		}
		window.draw(buttonSprite);
		GameUI::showMenuUI(window);
		window.display();
	}
}