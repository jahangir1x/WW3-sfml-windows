#include "Loading.hpp"
#include "Helper.hpp"

using namespace std;
using namespace sf;

void Loading::Show(RenderWindow& window, Event& event)
{
	Text loadtext;
	Font font;
	font.loadFromFile("res/AgencyFB-Regular.ttf");
	loadtext.setString("Loading...");
	loadtext.setFont(font);
	loadtext.setCharacterSize(90);
	loadtext.setFillColor(Color(236, 93, 93));
	loadtext.setPosition(Helper::windowWidth() / 2 - loadtext.getGlobalBounds().width / 2, Helper::windowHeight() / 2 - loadtext.getGlobalBounds().height / 2);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				exit(0);
			}
		}
		window.clear(Color(56, 56, 56));
		window.draw(loadtext);
		window.display();
		return;
	}
}