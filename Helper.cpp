#include "Helper.hpp"
using namespace sf;
using namespace std;

namespace Helper
{
sf::Vector2f getNormalizedVector(sf::Vector2f to, sf::Vector2f from)
{
	Vector2f direction = to - from;
	return (direction / sqrt(direction.x * direction.x + direction.y * direction.y));
}

unsigned seed = chrono::system_clock::now().time_since_epoch().count();

float pointsDistance(float x1, float y1, float x2, float y2)
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

default_random_engine generator;

void seedRand()
{
	generator.seed(seed);
}

int randRange(int min, int max)
{
	uniform_int_distribution<int> distr(min, max);
	return distr(generator);
}

float timePerFrame;
Clock gameClock;

void resetClock()
{
	timePerFrame = gameClock.restart().asSeconds();
}

float SecondsPerFrame()
{
	return timePerFrame;
}
int _windowWidth;
int _windowHeight;
void storeWindowSize(int width, int height)
{
	_windowWidth = width;
	_windowHeight = height;
}
int windowWidth()
{
	return _windowWidth;
}
int windowHeight()
{
	return _windowHeight;
}
int _enemiesDied = 0;
int enemiesDied()
{
	return _enemiesDied;
}
void newEnemyDied()
{
	_enemiesDied++;
}

void resetEnemyDiedCounter()
{
	_enemiesDied = 0;
}
}