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

int randRange(int min, int max)
{
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator;
	generator.seed(seed);
	uniform_int_distribution<int> distr(min, max);
	return distr(generator);
}
}