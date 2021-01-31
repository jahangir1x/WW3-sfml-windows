#include "Success.hpp"
#include "BaseEnemy.hpp"
#include "GetRes.hpp"
#include "Helper.hpp"
#include "Player.hpp"

using namespace std;
using namespace sf;
Success::Success()
{
	completeString = "Objective Complete";
	buttonRect.left = 0;
	buttonRect.top = 0;
	buttonRect.width = 281;
	buttonRect.height = 84;

	screenRect.setSize(Vector2f(Helper::windowWidth(), Helper::windowHeight()));
	screenRect.setFillColor(Color(0, 0, 0, 0));

	titleSprite.setTexture(GetRes::titleBar);

	bodySprite.setTexture(GetRes::CompleteBody);
	starSprite.setTexture(GetRes::CompleteStar);
	textSprite.setTexture(GetRes::CompleteText);
	buttonSprite.setTexture(GetRes::CompleteButton);

	titleSprite.setOrigin(titleSprite.getGlobalBounds().width / 2, titleSprite.getGlobalBounds().height / 2);

	bodySprite.setOrigin(bodySprite.getGlobalBounds().width / 2, bodySprite.getGlobalBounds().height / 2);
	bodySprite.setPosition(Helper::windowWidth() / 2, Helper::windowHeight() / 2);
	titleSprite.setPosition(Helper::windowWidth() / 2, bodySprite.getPosition().y - bodySprite.getGlobalBounds().height / 2);

	starSprite.setOrigin(starSprite.getGlobalBounds().width / 2, starSprite.getGlobalBounds().height / 2);
	starSprite.setPosition(bodySprite.getGlobalBounds().left + 5 + starSprite.getGlobalBounds().width / 2, bodySprite.getGlobalBounds().top + 56 + starSprite.getGlobalBounds().height / 2);

	buttonSprite.setTextureRect(buttonRect);
	buttonSprite.setOrigin(buttonSprite.getGlobalBounds().width / 2, buttonSprite.getGlobalBounds().height / 2);
	buttonSprite.setPosition(Helper::windowWidth() + 400, Helper::windowHeight() + 400);

	bodyScale = 0;
	starScale = 0;
	buttonScale = 0;
	textScale = 1;

	time = 0.005;
	sign = 1;
	shouldClose = false;

	alpha = 0;

	bodySprite.setScale(bodyScale, bodyScale);
	starSprite.setScale(starScale, starScale);
	successSound.setBuffer(GetRes::successMessageSound);
	clickSound.setBuffer(GetRes::menuClickSound);
	soundPlayed = false;
	clickSoundPlayed = false;
	Helper::resetClock();
}

bool Success::isFinishedShowing(RenderWindow& window)
{
	BaseEnemy::isMute = true;
	Player::isMute = true;
	buttonSprite.setPosition(bodySprite.getPosition().x + bodySprite.getGlobalBounds().width / 2 - 10 - buttonSprite.getGlobalBounds().width / 2, bodySprite.getPosition().y + bodySprite.getGlobalBounds().height / 2 - 10 - buttonSprite.getGlobalBounds().height / 2);
	buttonSprite.setScale(buttonScale, buttonScale);

	if (rectClock.getElapsedTime().asSeconds() > 0.0005 && alpha < 255.0)
	{
		alpha += 90 * Helper::SecondsPerFrame();
		if (alpha > 255)
		{
			alpha = 255;
		}
		rectClock.restart();
	}
	screenRect.setFillColor(Color(0, 0, 0, alpha));
	window.draw(screenRect);

	if (bodyClock.getElapsedTime().asSeconds() > 0.005 && bodyScale < 1.0 && shouldClose == false)
	{
		if (soundPlayed == false)
		{
			successSound.play();
			soundPlayed = true;
		}
		bodyScale += 0.01 * 90 * Helper::SecondsPerFrame();

		bodyClock.restart();
	}

	else if (bodyClock.getElapsedTime().asSeconds() > 0.005 && starScale < 1.0 && bodyScale >= 1.0 && shouldClose == false)
	{
		starScale += 0.02 * 90 * Helper::SecondsPerFrame();
		bodyClock.restart();
	}

	titleSprite.setScale(bodyScale, bodyScale);
	bodySprite.setScale(bodyScale, bodyScale);
	starSprite.setScale(starScale, starScale);
	window.draw(bodySprite);
	window.draw(titleSprite);
	window.draw(starSprite);

	if (starScale >= 0.5)
	{
		if (custext.fullShowed == false)
		{

			custext.Show(window, completeString, 75, bodySprite.getGlobalBounds().left + 85, bodySprite.getGlobalBounds().top + 102, 0, false, 0.1, Color(52, 209, 245));
		}
		else
		{
			textSprite.setPosition(custext.text.getPosition().x - 6, custext.text.getPosition().y + 8);
			window.draw(textSprite);
		}
	}
	textSprite.setScale(textScale, textScale);

	if (buttonClock.getElapsedTime().asSeconds() > time && custext.fullShowed == true && buttonScale < 1.0 && shouldClose == false)
	{
		buttonScale += 0.01 * 90 * Helper::SecondsPerFrame();
		if (buttonScale >= 1.0)
		{
			time = 0.11;
		}
		window.draw(buttonSprite);
		buttonClock.restart();
	}
	else if (buttonClock.getElapsedTime().asSeconds() > time && buttonScale >= 1.0 && shouldClose == false)
	{
		if (buttonRect.left == 1124)
		{
			sign = -1;
		}
		else if (buttonRect.left == 0)
		{
			sign = 1;
		}
		buttonRect.left += buttonRect.width * sign;
		buttonSprite.setTextureRect(buttonRect);
		buttonClock.restart();
	}

	buttonSprite.setScale(buttonScale, buttonScale);
	window.draw(buttonSprite);

	if (shouldClose == true && bodyClock.getElapsedTime().asSeconds() > 0.005)
	{
		if (buttonScale > 0)
		{
			buttonScale -= 0.03 * 90 * Helper::SecondsPerFrame();
			if (buttonScale < 0)
			{
				buttonScale = 0;
			}
		}
		else if (textScale > 0)
		{
			textScale -= 0.03 * 90 * Helper::SecondsPerFrame();
			if (textScale < 0)
			{
				textScale = 0;
			}
		}
		else if (starScale > 0)
		{
			starScale -= 0.3 * 90 * Helper::SecondsPerFrame();
			if (starScale < 0)
			{
				starScale = 0;
			}
		}

		else if (bodyScale > 0)
		{
			bodyScale -= 0.03 * 90 * Helper::SecondsPerFrame();
			if (bodyScale < 0)
			{
				bodyScale = 0;
			}
		}
		if (bodyScale <= 0)
		{
			return true;
		}
		bodyClock.restart();
	}
	return false;
}

void Success::handleClose(Vector2i mousePos)
{
	if (buttonSprite.getGlobalBounds().contains(Vector2f(mousePos)))
	{
		if (clickSoundPlayed == false)
		{
			clickSound.play();
			clickSoundPlayed = false;
		}
		shouldClose = true;
	}
}
