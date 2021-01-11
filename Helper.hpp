#ifndef Helper_air321
#define Helper_air321

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <bits/stdc++.h>
namespace Helper
{
sf::Vector2f getNormalizedVector(sf::Vector2f to, sf::Vector2f from);
int randRange(int min, int max);
void resetClock();
float SecondsPerFrame();
void storeWindowSize(int width, int height);
int windowWidth();
int windowHeight();
int enemiesDied();
void newEnemyDied();
}
#endif
