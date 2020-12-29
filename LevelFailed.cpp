#include "LevelFailed.hpp"

using namespace std;
using namespace sf;

void LevelFailed::Show(RenderWindow& window, Event& event)
{
	Font failedFont;								   // set font
	failedFont.loadFromFile("res/Roboto-Regular.ttf"); // load font
	Text failedText;								   // set text
	failedText.setFont(failedFont);					   // set text font
	failedText.setString("You failed Nigga\n");		   // load text
	failedText.setCharacterSize(80);				   // set text size
	failedText.setFillColor(Color::White);             // set text color

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}
		window.clear(Color::Magenta);
		// window.draw(someThing);
		cout << "showing failed" << endl;
		window.draw(failedText); // show text
		window.display();
	}
}
