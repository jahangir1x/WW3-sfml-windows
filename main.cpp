#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <bits/stdc++.h>
using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(800, 600), "SFML works!");
    CircleShape shape(100.f);
    shape.setFillColor(Color::Green);
    while (window.isOpen()){
        Event event;
        while (window.pollEvent(event)){
            if (event.type == Event::KeyPressed){
				Vector2i globalposition = Mouse::getPosition(window);
				if (event.key.code == Keyboard::Z){
					cout << "the \"z\" key was pressed... mouse location:" << endl;
					cout << "x: " << globalposition.x << " y: " << globalposition.y << endl;
				}
			}
            else if (event.type == Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
