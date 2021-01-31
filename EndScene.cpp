#include "EndScene.hpp"
#include "CustomText.hpp"
#include "GameUI.hpp"
#include "LevelHelper.hpp"

using namespace std;
using namespace sf;

void EndScene::Show(RenderWindow& window, Event& event)
{

	CustomText text;
	text.shouldMute = true;
	CustomText text2;
	CustomText text3;
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
				}
			}
		}
		window.clear(Color::Black);
		text.Show(window, "War may sometimes be a necessary evil. But no matter how necessary,\nit is always an evil, never a good.\nWe will not learn how to live together in peace by killing each other's children.\n\t\t\t\t\t\t\t-Jimmy Carter", 30, 50, 200, -1, false, 0.01);

		if (text.fullShowed == true)
		{
			text2.Show(window, "To be continued...", 30, 50, 400, -1, false, 0.1, Color(52, 209, 245));
		}

		if (text2.fullShowed == true)
		{
			text3.Show(window, "Press Enter to play again.", 40, 50, 600, -1, true, 0.01);
		}
		if (Keyboard::isKeyPressed(Keyboard::Enter))
		{
			LevelHelper::retriesLeft = 0;
			return;
		}
		GameUI::showMenuUI(window);
		window.display();
	}
}
