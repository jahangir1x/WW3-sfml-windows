#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <bits/stdc++.h>
using namespace std;
using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == Event::KeyPressed){
				Vector2i globalposition = Mouse::getPosition(window);
				if (event.key.code == Keyboard::Z){
					cout << "the \"z\" key was pressed... mouse location:" << endl;
					cout << "x: " << globalposition.x << " y: " << globalposition.y << endl;
				}
			}
            else if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
