#include "Background.hpp"
#include "GetRes.hpp"

Background::Background()
{
	scenery = Scenes(rand() % 2); // set random scenery
	if (scenery == Sea)
	{
		backScene.blending_pos = -3095;
		backScene.backSprite.setTexture(GetRes::seaTex);
		backScene.element1Sprite.setTexture(GetRes::seaElem1);
		backScene.element2Sprite.setTexture(GetRes::seaElem2);
		backScene.element3Sprite.setTexture(GetRes::seaElem3);
		backScene.element4Sprite.setTexture(GetRes::seaElem4);
		backScene.element5Sprite.setTexture(GetRes::seaElem5);
	}
	else if (scenery == Land)
	{
		backScene.blending_pos = -3912;
		backScene.backSprite.setTexture(GetRes::landTex);
		backScene.element1Sprite.setTexture(GetRes::landElem1);
		backScene.element2Sprite.setTexture(GetRes::landElem2);
		backScene.element3Sprite.setTexture(GetRes::landElem3);
		backScene.element4Sprite.setTexture(GetRes::landElem4);
		backScene.element5Sprite.setTexture(GetRes::landElem5);
	}
	backScene.backSprite.setPosition(0, -backScene.backSprite.getGlobalBounds().height + Helper::windowHeight());
	shouldRenewElements = false;
	Helper::resetClock();
}

void Background::Show(RenderWindow& window)
{
	if (shouldRenewElements)
	{
		if (rand() % 2) // choose randomly whether we should show elements1
		{
			j = rand() % 2; // choose random number of elements
			for (i = 0; i < j; i++)
			{
				elements.push_back(backScene.element1Sprite);
			}
		}
		if (rand() % 2)
		{
			j = rand() % 2;
			for (i = 0; i < j; i++)
			{
				elements.push_back(backScene.element2Sprite);
			}
		}
		if (rand() % 2)
		{
			j = rand() % 2;
			for (i = 0; i < j; i++)
			{
				elements.push_back(backScene.element3Sprite);
			}
		}
		if (rand() % 2)
		{
			j = rand() % 2;
			for (i = 0; i < j; i++)
			{
				elements.push_back(backScene.element4Sprite);
			}
		}
		if (rand() % 2)
		{
			j = rand() % 2;
			for (i = 0; i < j; i++)
			{
				elements.push_back(backScene.element5Sprite);
			}
		}

		for (auto& element : elements)
		{
			element.setRotation(rand() % 360); // set random rotation
			k = Helper::randRange(50, 100);
			element.setScale(k / 100.0 * Helper::getWidthScalingFactor(), k / 100.0 * Helper::getWidthScalingFactor());													 // set random scale
			element.setPosition(Helper::randRange(0, Helper::windowWidth()), Helper::randRange(-Helper::windowHeight(), -element.getGlobalBounds().height * 2)); // set random position
		}

		for (i = 0; i < elements.size(); i++)
		{
			for (j = i + 1; j < elements.size(); j++)
			{
				if (i == j)
				{
					continue;
				}
				else
				{
					if (elements[j].getGlobalBounds().intersects(elements[i].getGlobalBounds())) // check if it intersects then set it outside
					{
						elements[i].setPosition(Helper::windowWidth() + 100, Helper::windowHeight() + 100);
					}
				}
			}
		}
		shouldRenewElements = false;
	}

	backScene.backSprite.move(0, 500 * Helper::SecondsPerFrame());
	if (backScene.backSprite.getPosition().y >= 0)
	{
		backScene.backSprite.setPosition(0, backScene.blending_pos);
	}
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
