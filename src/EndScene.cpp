#include "EndScene.hpp"
#include "CustomText.hpp"
#include "GameUI.hpp"
#include "GetRes.hpp"
#include "LevelHelper.hpp"

using namespace std;
using namespace sf;

void EndScene::Show(RenderWindow& window, Event& event)
{
	unsigned int i;
	CustomText text;

	text.shouldMute = true;

	CustomText text2;
	CustomText text3;
	CustomText text4;
	text.text.setScale(1, 1);
	text2.text.setScale(1, 1);
	text3.text.setScale(1, 1);
	text4.text.setScale(1, 1);
	Texture roadTex;
	Texture houseTex;
	Texture buildingTex;
	Texture cloudTex;
	Texture planeTex;
	Texture reactionTex;
	Texture treeTex;
	Texture explosionTex;

	explosionTex.loadFromFile("res/explosion.png");

	roadTex.loadFromFile("res/end_scene_road.png");
	houseTex.loadFromFile("res/end_scene_house.png");
	buildingTex.loadFromFile("res/end_scene_building.png");
	cloudTex.loadFromFile("res/end_scene_clouds.png");
	planeTex.loadFromFile("res/end_scene_plane.png");
	reactionTex.loadFromFile("res/reaction.png");
	treeTex.loadFromFile("res/tree.png");

	Sprite roadSprite;
	Sprite houseSprite;
	Sprite buildingSprite;
	RectangleShape grassRect;
	class Cloud
	{
	public:
		Sprite sprite;
		IntRect rect;
	};
	class Tree
	{
	public:
		Sprite sprite;
	};
	class Explosion
	{
	public:
		Clock clock;
		Sprite sprite;
		IntRect rect;
		float intervalTime;
	};
	Sprite planeSprite;
	Sprite reactionSprite;

	vector<Cloud> clouds(5);
	vector<Tree> trees(4);
	vector<Explosion> explosions(5);

	IntRect reactionRect(0, 0, 111, 207);

	roadSprite.setTexture(roadTex);
	houseSprite.setTexture(houseTex);
	buildingSprite.setTexture(buildingTex);
	planeSprite.setTexture(planeTex);
	reactionSprite.setTexture(reactionTex);
	reactionSprite.setTextureRect(reactionRect);

	planeSprite.setOrigin(planeSprite.getGlobalBounds().width, planeSprite.getGlobalBounds().height);
	houseSprite.setOrigin(0, houseSprite.getGlobalBounds().height);
	buildingSprite.setOrigin(0, buildingSprite.getGlobalBounds().height);
	reactionSprite.setOrigin(reactionSprite.getGlobalBounds().width / 2.0, reactionSprite.getGlobalBounds().height + 20);



	planeSprite.setPosition(-planeSprite.getGlobalBounds().width * 2, -planeSprite.getGlobalBounds().height * 2);
	roadSprite.setPosition(0, Helper::windowHeight() * 2.0 / 3.0);
	houseSprite.setPosition(roadSprite.getGlobalBounds().left + 20, roadSprite.getGlobalBounds().top);
	buildingSprite.setPosition(roadSprite.getGlobalBounds().left + roadSprite.getGlobalBounds().width - buildingSprite.getGlobalBounds().width - 30, roadSprite.getGlobalBounds().top);
	reactionSprite.setPosition(-400, -400);

	grassRect.setPosition(roadSprite.getGlobalBounds().left, roadSprite.getGlobalBounds().top);
	grassRect.setSize(Vector2f(Helper::windowWidth(), Helper::windowHeight() - roadSprite.getGlobalBounds().top));
	grassRect.setFillColor(Color(45, 136, 26));

	for (i = 0; i < clouds.size(); i++)
	{
		clouds[i].sprite.setTexture(cloudTex);
		clouds[i].rect.left = 200 * i;
		clouds[i].rect.top = 0;
		clouds[i].rect.width = 200;
		clouds[i].rect.height = 112;
		clouds[i].sprite.setTextureRect(clouds[i].rect);
		clouds[i].sprite.setPosition(Helper::randRange(0, Helper::windowWidth() - clouds[i].sprite.getGlobalBounds().width), Helper::randRange(0, roadSprite.getGlobalBounds().top * 2.0 / 3.0));
	}

	for (auto& tree : trees)
	{
		tree.sprite.setTexture(treeTex);
		tree.sprite.setOrigin(0, tree.sprite.getGlobalBounds().height);
		tree.sprite.setPosition(Helper::randRange(houseSprite.getGlobalBounds().left + houseSprite.getGlobalBounds().width - 40, buildingSprite.getGlobalBounds().left + 40), roadSprite.getGlobalBounds().top);
	}

	for (auto& explosion : explosions)
	{
		explosion.sprite.setTexture(explosionTex);
		explosion.rect.left = (rand() % 5) * 51;
		explosion.rect.top = 0;
		explosion.rect.width = 51;
		explosion.rect.height = 65;
		explosion.sprite.setTextureRect(explosion.rect);
		explosion.sprite.setOrigin(explosion.sprite.getGlobalBounds().width / 2.0, explosion.sprite.getGlobalBounds().height / 2.0);
		explosion.sprite.setScale(3.0, 3.0);
		explosion.intervalTime = Helper::randRange(100, 500) / 1000.0;
	}

	explosions[0].sprite.setPosition(houseSprite.getGlobalBounds().left + 63, houseSprite.getGlobalBounds().top + 42);
	cout << "ex0: " << explosions[0].sprite.getPosition().x << " " << explosions[0].sprite.getPosition().y << endl;
	explosions[1].sprite.setPosition(houseSprite.getGlobalBounds().left + 348, houseSprite.getGlobalBounds().top + 82);
	explosions[2].sprite.setPosition(buildingSprite.getGlobalBounds().left + 42, buildingSprite.getGlobalBounds().top + 113);
	explosions[3].sprite.setPosition(buildingSprite.getGlobalBounds().left + 245, buildingSprite.getGlobalBounds().top + 232);
	explosions[4].sprite.setPosition(buildingSprite.getGlobalBounds().left + 533, buildingSprite.getGlobalBounds().top + 338);

	Vector2f landingPos = Vector2f(Helper::windowWidth() / 4.0, roadSprite.getGlobalBounds().top + roadSprite.getGlobalBounds().height / 2);

	Vector2f stoppingPos = Vector2f(Helper::windowWidth() * 3.0 / 4.0, roadSprite.getGlobalBounds().top + roadSprite.getGlobalBounds().height / 2);
	Vector2f landingNorm;
	Vector2f stoppingNorm;
	Clock decClock;
	Clock explosionClock;

	bool landed = false;
	bool stopped = false;
	float speed = 200.0;

	GameUI::init();

	while (window.isOpen())
	{
		Helper::resetClock();
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				exit(0);
			}
			else if (event.type == Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					GameUI::handleClose(window, window.mapPixelToCoords(Mouse::getPosition(window)));
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			cout << "mou: " << Mouse::getPosition(window).x << " " << Mouse::getPosition(window).y << endl;
			cout << "ex0: " << explosions[0].rect.left << " " << explosions[1].rect.left << " " << explosions[2].rect.left << " " << explosions[3].rect.left << " " << explosions[4].rect.left << endl;
			cout << "exti: " << explosions[0].intervalTime << " " << explosions[1].intervalTime << " " << explosions[2].intervalTime << " " << explosions[3].intervalTime << " " << explosions[4].intervalTime << endl;
		}
		window.clear(Color(142, 194, 253));

		if (landed == false)
		{
			landingNorm = Helper::getNormalizedVector(landingPos, planeSprite.getPosition());
			planeSprite.move(landingNorm * float(250.0) * Helper::SecondsPerFrame());
			if (Helper::pointsDistance(landingPos.x, landingPos.y, planeSprite.getPosition().x, planeSprite.getPosition().y) < 20.0)
			{
				landed = true;
			}
		}
		if (landed == true && stopped == false)
		{
			stoppingNorm = Helper::getNormalizedVector(stoppingPos, planeSprite.getPosition());
			planeSprite.move(stoppingNorm * float(speed) * Helper::SecondsPerFrame());
			if (decClock.getElapsedTime().asSeconds() > 0.8 && speed > 28)
			{
				speed -= 14.0;
				cout << "speed: " << speed << endl;
				decClock.restart();
			}
			if (Helper::pointsDistance(stoppingPos.x, stoppingPos.y, planeSprite.getPosition().x, planeSprite.getPosition().y) < 20.0)
			{
				stopped = true;
			}
		}
		if (stopped == true && decClock.getElapsedTime().asSeconds() > 0.5)
		{
			reactionRect.left = (rand() % 4) * reactionRect.width;
			reactionSprite.setTextureRect(reactionRect);

			reactionSprite.setPosition(planeSprite.getGlobalBounds().left + planeSprite.getGlobalBounds().width * 2.0 / 3.0, planeSprite.getGlobalBounds().top - 10);

			reactionSprite.setRotation(Helper::randRange(-30, 30));
			decClock.restart();
		}

		for (auto& explosion : explosions)
		{
			if (explosion.clock.getElapsedTime().asSeconds() > explosion.intervalTime)
			{
				if (explosion.rect.left >= 204)
				{
					explosion.rect.left = 0;
				}
				else
				{
					explosion.rect.left += explosion.rect.width;
				}

				explosion.sprite.setTextureRect(explosion.rect);
				explosion.clock.restart();
			}
		}

		for (auto& cloud : clouds)
		{
			window.draw(cloud.sprite);
		}
		window.draw(grassRect);
		window.draw(roadSprite);
		window.draw(houseSprite);
		window.draw(buildingSprite);

		for (auto& explosion : explosions)
		{
			window.draw(explosion.sprite);
		}

		for (auto& tree : trees)
		{
			window.draw(tree.sprite);
		}
		window.draw(planeSprite);
		window.draw(reactionSprite);

		text.Show(window, "To be continued...", 50, 20, 20, -1, true, 0.1);
		if (text.fullShowed)
		{
			text2.Show(window, "Press ", 45, text.text.getGlobalBounds().left, text.text.getGlobalBounds().top + text.text.getGlobalBounds().height + 20, -1, false, 0.2, Color(249, 13, 36));
		}
		if (text2.fullShowed)
		{
			text3.Show(window, "Enter", 45, text2.text.getPosition().x + text2.text.getGlobalBounds().width + 10, text2.text.getPosition().y, -1, true, 0.2);
		}
		if (text3.fullShowed)
		{
			text4.Show(window, " to play again.", 45, text3.text.getPosition().x + text3.text.getGlobalBounds().width + 10, text3.text.getPosition().y, -1, false, 0.2, Color(249, 13, 36));
		}
		if (Keyboard::isKeyPressed(Keyboard::Enter))
		{
			LevelHelper::retriesLeft = 0;
			return;
		}

		GameUI::showMenuUI(window);
		window.display();
	}
}
