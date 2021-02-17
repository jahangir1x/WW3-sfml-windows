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
	if (min > max)
	{
		swap(min, max);
	}
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

float dir_x;
float dir_y;
float temp;

float getRotation(float to_x, float to_y, float from_x, float from_y)
{
	dir_x = to_x - from_x;
	dir_y = to_y - from_y;

	temp = 180 * acos(dir_x * from_x / (sqrt(dir_x * dir_x + dir_y * dir_y) * sqrt(from_x * from_x))) / 3.14159;
	if (to_y < from_y)
	{
		temp = temp * (-1);
	}
	return temp;
}

float _playerHeight;
void storePlayerHeight(float height)
{
	_playerHeight = height;
}
float getPlayerHeight()
{
	return _playerHeight;
}
}
