#ifndef Level1_air321
#define Level1_air321
#include "Enemy1.hpp"
#include "Enemy2.hpp"
#include "Helper.hpp"
#include "LevelFailed.hpp" // level failed header file
#include "LevelHelper.hpp"
#include "Player.hpp"
using namespace sf; // don't forget this or you would have to initialize everything with sf::
class Level1
{
public:
	void Show(RenderWindow& window, Event& event);
};
#endif
