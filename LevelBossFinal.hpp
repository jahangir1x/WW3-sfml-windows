#ifndef LevelBossFinal_air321
#define LevelBossFinal_air321
#include "Background.hpp"
#include "Enemy1.hpp"
#include "Enemy2.hpp"
#include "Enemy3.hpp"
#include "Enemy4.hpp"
#include "Enemy5.hpp"
#include "Enemy6.hpp"
#include "Helper.hpp"
#include "LevelFailed.hpp" // level failed header file
#include "LevelHelper.hpp"

using namespace sf; // don't forget this or you would have to initialize everything with sf::
class LevelBossFinal
{
public:
	void Show(RenderWindow& window, Event& event);
};
#endif
