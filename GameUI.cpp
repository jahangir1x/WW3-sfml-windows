#include "GameUI.hpp"
#include "GetRes.hpp"
#include "LevelHelper.hpp"
#include "Player.hpp"

RectangleShape GameUI::healthInsideRect;
RectangleShape GameUI::healthOutsideRect;
Sprite GameUI::retrySprite;
vector<Sprite> GameUI::retrySprites;
Sprite GameUI::missileSprite;
vector<Sprite> GameUI::missileSprites;
Sprite GameUI::cursorSprite;
IntRect GameUI::cursorRect;
Sprite GameUI::closeButton;
GameUI::CursorStates GameUI::cursorState;
unsigned int GameUI::i;
unsigned int GameUI::j;
Sound GameUI::clickSound;

void GameUI::init()
{
	healthInsideRect.setPosition(11, 12);
	healthInsideRect.setSize(Vector2f(197, 14));
	healthInsideRect.setFillColor(Color(49, 206, 241));

	healthOutsideRect.setPosition(9, 9);
	healthOutsideRect.setSize(Vector2f(201, 20));
	healthOutsideRect.setFillColor(Color(77, 77, 77));

	cursorState = Inactive;

	cursorRect.left = 0;
	cursorRect.top = 0;
	cursorRect.width = 38;
	cursorRect.height = 46;

	cursorSprite.setTexture(GetRes::cursor);
	cursorSprite.setTextureRect(cursorRect);
	cursorSprite.setPosition(Vector2f(Mouse::getPosition()));

	closeButton.setTexture(GetRes::closeButton);
	closeButton.setPosition(Helper::windowWidth() - closeButton.getGlobalBounds().width, 0);

	missileSprite.setTexture(GetRes::missileCountTex);
	retrySprite.setTexture(GetRes::retryCount);

	// for (i = 0, j = 0; i < Player::missileCount; i++)
	// {
	// 	missileSprite.setPosition(9 + j, 76);
	// 	missileSprites.push_back(missileSprite);
	// 	j += 16;
	// }

	// for (i = 0, j = 0; i < LevelHelper::retriesLeft - 1; i++)
	// {
	// 	retrySprite.setPosition(9 + j, 41);
	// 	retrySprites.push_back(retrySprite);
	// 	j += 31;
	// }
	clickSound.setBuffer(GetRes::menuClickSound);
	Helper::resetClock();
}

void GameUI::showPlayerUI(RenderWindow& window)
{
	healthInsideRect.setSize(Vector2f(197 * Player::healthValue / 100, 12));
	missileSprites.clear();
	retrySprites.clear();
	for (i = 0, j = 0; i < Player::missileCount; i++)
	{
		missileSprite.setPosition(9 + j, 76);
		missileSprites.push_back(missileSprite);
		j += 16;
	}

	for (i = 0, j = 0; i < LevelHelper::retriesLeft - 1; i++)
	{
		retrySprite.setPosition(9 + j, 41);
		retrySprites.push_back(retrySprite);
		j += 31;
	}

	cursorSprite.setPosition(Vector2f(Mouse::getPosition(window)));
	if (Player::startedFiring)
	{
		cursorState = Left;
		if (Mouse::isButtonPressed(Mouse::Right))
		{
			cursorState = Both;
		}
	}
	else if (Mouse::isButtonPressed(Mouse::Right))
	{
		cursorState = Right;
	}
	else
	{
		cursorState = Inactive;
	}

	if (cursorState == Left)
	{
		cursorRect.left = cursorRect.width;
	}
	else if (cursorState == Right)
	{
		cursorRect.left = cursorRect.width * 2;
	}
	else if (cursorState == Both)
	{
		cursorRect.left = cursorRect.width * 3;
	}
	else
	{
		cursorRect.left = 0;
	}

	cursorSprite.setTextureRect(cursorRect);

	for (auto& missile : missileSprites)
	{
		window.draw(missile);
	}
	for (auto& retry : retrySprites)
	{
		window.draw(retry);
	}

	window.draw(healthOutsideRect);
	window.draw(healthInsideRect);
	window.draw(closeButton);
	window.draw(cursorSprite);
}

void GameUI::showMenuUI(RenderWindow& window)
{
	cursorSprite.setPosition(Vector2f(Mouse::getPosition(window)));
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		cursorState = Left;
		if (Mouse::isButtonPressed(Mouse::Right))
		{
			cursorState = Both;
		}
	}
	else if (Mouse::isButtonPressed(Mouse::Right))
	{
		cursorState = Right;
	}
	else
	{
		cursorState = Inactive;
	}

	if (cursorState == Left)
	{
		cursorRect.left = cursorRect.width;
	}
	else if (cursorState == Right)
	{
		cursorRect.left = cursorRect.width * 2;
	}
	else if (cursorState == Both)
	{
		cursorRect.left = cursorRect.width * 3;
	}
	else
	{
		cursorRect.left = 0;
	}

	window.draw(closeButton);

	cursorSprite.setTextureRect(cursorRect);
	window.draw(cursorSprite);
}

void GameUI::handleClose(RenderWindow& window, Vector2i MousePos)
{
	if (closeButton.getGlobalBounds().contains(Vector2f(MousePos)))
	{
		clickSound.play();

		window.close();
		exit(0);
	}
}
