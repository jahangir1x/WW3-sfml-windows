#include "Level3.hpp"	   // level header file
#include "LevelFailed.hpp" // level failed header file

using namespace std;
using namespace sf;

void Level3::Show(RenderWindow& window, Event& event)
{
	LevelFailed levelFailedObj; // create levelFailed object to show level failed message
	while (window.isOpen())
	{

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
			{
				return; // show next level
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::L)
			{
				levelFailedObj.Show(window, event); // show level failed message
			}
		}
		window.clear(Color::Blue);
		// window.draw(someThing);
		window.display();
	}
}