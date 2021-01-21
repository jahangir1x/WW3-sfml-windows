#include "Background.hpp"

Background::Background()
{
	scenery = Scenes(rand() % 2); // set random scenery
	if (scenery == Sea)
	{
//		cout << "scene: sea" << endl;
		backScene.backTexture.loadFromFile("res/sea.png");
		backScene.element1Texture.loadFromFile("res/ship1.png");
		backScene.element2Texture.loadFromFile("res/ship2.png");
		backScene.blending_pos = -3736;
	}
	else if (scenery == Land)
	{
//		cout << "scene: land" << endl;
		backScene.backTexture.loadFromFile("res/sea.png");
		backScene.element1Texture.loadFromFile("res/ship1.png");
		backScene.element2Texture.loadFromFile("res/ship2.png");
		backScene.blending_pos = -3736;
	}

	backScene.backSprite.setTexture(backScene.backTexture);
	backScene.element1Sprite.setTexture(backScene.element1Texture);
	backScene.element2Sprite.setTexture(backScene.element2Texture);
	backScene.backSprite.setPosition(0, -backScene.backSprite.getGlobalBounds().height + Helper::windowHeight());
	shouldRenewElements = false;
}

void Background::Show(RenderWindow& window)
{
	if (shouldRenewElements)
	{
//		cout << "in should renew" << endl;
		if (rand() % 2) // choose randomly whether we should show elements1
		{
			j = rand() % 4; // choose random number of elements
			for (i = 0; i < j; i++)
			{
				elements.push_back(backScene.element1Sprite);
			}
		}
		if (rand() % 2)
		{
			j = rand() % 4;
			for (i = 0; i < j; i++)
			{
				elements.push_back(backScene.element2Sprite);
			}
		}

//		cout << "total elems: " << elements.size() << endl;

		for (auto& element : elements)
		{
			element.setRotation(rand() % 360); // set random rotation
			k = Helper::randRange(60, 210);
			element.setScale(k / 100, k / 100);																													 // set random scale
			element.setPosition(Helper::randRange(0, Helper::windowWidth()), Helper::randRange(-Helper::windowHeight(), -element.getGlobalBounds().height * 2)); // set random position
		}

		// for (i = 0; i < elements.size(); i++)
		// {
		// 	for (j = 0; j < elements.size(); j++)
		// 	{
		// 		if (i == j)
		// 		{
		// 			continue;
		// 		}
		// 		else
		// 		{
		// 			if (elements[j].getGlobalBounds().intersects(elements[i].getGlobalBounds())) // check if it intersects then change position
		// 			{
		// 				elements[i].setPosition(Helper::randRange(0, Helper::windowWidth()), Helper::randRange(-Helper::windowHeight(), -elements[i].getGlobalBounds().height * 2)); // change position
		// 			}
		// 		}
		// 	}
		// }
		shouldRenewElements = false;
	}

	if (backScene.backSprite.getPosition().y >= 0){
		backScene.backSprite.setPosition(0,backScene.blending_pos);
	}

	backScene.backSprite.move(0, 500 * Helper::SecondsPerFrame());
	for (auto& element : elements)
	{
		element.move(0, 500 * Helper::SecondsPerFrame());
	}
	elements.erase(remove_if(elements.begin(), elements.end(), Background::shouldRemoveElement), elements.end());
	if (elements.size() == 0)
	{
		shouldRenewElements = true;
	}

	window.draw(backScene.backSprite);
	for (auto& element : elements)
	{
		window.draw(element);
	}
}

bool Background::shouldRemoveElement(Sprite& sprite)
{
	if (sprite.getPosition().y > (Helper::windowHeight() + sprite.getGlobalBounds().height))
	{
		return true;
	}
	else
	{
		return false;
	}
}
