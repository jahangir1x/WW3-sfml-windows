#ifndef Helper_air321
#define Helper_air321

namespace Helper
{
sf::Vector2f getNormalizedVector(sf::Vector2f to, sf::Vector2f from);
float pointsDistance(float x1, float y1, float x2, float y2);
void seedRand(); // to seed random function
int randRange(int min, int max);
void resetClock();
float SecondsPerFrame();					 // to get global seconds elapsed since last frame
void storeWindowSize(int width, int height); // to store windowsize so that we don't need to pass RenderWindow whenever we want to instantiate enemy or player class
int windowWidth();
int windowHeight();
int enemiesDied();
void newEnemyDied(); // increase enemy died counter for level completion
void resetEnemyDiedCounter();
float getRotation(float to_x, float to_y, float from_x, float from_y);
}
#endif
