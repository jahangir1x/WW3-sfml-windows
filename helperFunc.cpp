#include "helperFunc.hpp"
using namespace sf;
using namespace std;

namespace helperFunc
{
sf::Vector2f getNormalizedVector(sf::Vector2f to, sf::Vector2f from)
{
	Vector2f direction = to - from;
	return (direction / sqrt(direction.x * direction.x + direction.y * direction.y));
}
int randRange(int a, int b)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distr(a, b);
	return distr(gen);
}
}