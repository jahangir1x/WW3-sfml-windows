#include "Story.hpp"
#include "CustomText.hpp"
#include "GameUI.hpp"
#include "Helper.hpp"
#include "LevelHelper.hpp"

using namespace std;
using namespace sf;

void Story::Show(RenderWindow& window, Event& event)
{

	CustomText text;
	CustomText text2;
	CustomText text3;
	CustomText text4;
	text.text.setOutlineColor(Color::Black);
	text.text.setOutlineThickness(2);
	text.shouldMute = true;
	Texture backTex;
	Sprite backSprite;
	backTex.loadFromFile("res/story.png");
	backTex.setSmooth(true);
	backSprite.setTexture(backTex);
	text.text.setScale(1, 1);
	text2.text.setScale(1, 1);
	text3.text.setScale(1, 1);
	text4.text.setScale(1, 1);
	backSprite.setScale(1, 1);
	backSprite.setPosition(Helper::windowWidth() / 2 - backSprite.getGlobalBounds().width / 2, Helper::windowHeight() / 2 - backSprite.getGlobalBounds().height / 2);

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
					GameUI::handleClose(window, window.mapPixelToCoords(Mouse::getPosition(window)));
				}
			}
		}
		window.clear(Color::Black);
		window.draw(backSprite);
		text.Show(window, "The year is 2050. The USA is trying to take control of the whole world with\ntheir advanced weapons and their cunning mindset. Meanwhile, Russia is trying\nto expose their guileful tricks. The relationship between both countries\nstarts to worsen day by day. One day the USA declares war against Russia.\nThousands of armies, fighter jets start to invade Russia. Yuri is a Russian\nair force captain. Now Yuri needs to fight with his MIG29 jet to save his\ncountry.\n", 35, backSprite.getPosition().x + 12, backSprite.getPosition().y + 12, -1, false, 0.01);
		text2.Show(window, "Press ", 45, text.text.getGlobalBounds().left, text.text.getGlobalBounds().top + text.text.getGlobalBounds().height + 20, -1, false, 0.01);
		if (text2.fullShowed)
		{
			text3.Show(window, "Enter", 45, text2.text.getPosition().x + text2.text.getGlobalBounds().width + 10, text2.text.getPosition().y, -1, true, 0.01);
		}
		if (text3.fullShowed)
		{
			text4.Show(window, " to play.", 45, text3.text.getPosition().x + text3.text.getGlobalBounds().width + 10, text3.text.getPosition().y, -1, false, 0.01);
		}
		if (Keyboard::isKeyPressed(Keyboard::Enter))
		{
			return;
		}
		GameUI::showMenuUI(window);
		window.display();
	}
}