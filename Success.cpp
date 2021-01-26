#include "Success.hpp"
#include "GetRes.hpp"
#include "Helper.hpp"

using namespace std;
using namespace sf;
Success::Success()
{
	buttonRect.left = 0;
	buttonRect.top = 0;
	buttonRect.width = 281;
	buttonRect.height = 84;

	screenRect.setSize(Vector2f(Helper::windowWidth(), Helper::windowHeight()));
	screenRect.setFillColor(Color(0, 0, 0, 0));

	bodySprite.setTexture(GetRes::CompleteBody);
	starSprite.setTexture(GetRes::CompleteStar);
	textSprite.setTexture(GetRes::CompleteText);
	buttonSprite.setTexture(GetRes::CompleteButton);
	completeText.setFont(GetRes::techFont);
	completeText.setFillColor(Color(52, 209, 245));

	bodySprite.setOrigin(bodySprite.getGlobalBounds().width / 2, bodySprite.getGlobalBounds().height / 2);
	bodySprite.setPosition(Helper::windowWidth() / 2, Helper::windowHeight() / 2);

	starSprite.setOrigin(starSprite.getGlobalBounds().width / 2, starSprite.getGlobalBounds().height / 2);
	starSprite.setPosition(bodySprite.getGlobalBounds().left + 5 + starSprite.getGlobalBounds().width / 2, bodySprite.getGlobalBounds().top + 56 + starSprite.getGlobalBounds().height / 2);

	buttonSprite.setTextureRect(buttonRect);
	buttonSprite.setOrigin(buttonSprite.getGlobalBounds().width / 2, buttonSprite.getGlobalBounds().height / 2);
	buttonSprite.setPosition(bodySprite.getGlobalBounds().left + 561 + buttonSprite.getGlobalBounds().width / 2, bodySprite.getGlobalBounds().top + 216 + buttonSprite.getGlobalBounds().height / 2);

	bodyScale = 0;
	starScale = 0;
	buttonScale = 0;
	textScale = 1;
	length = 1;
	time = 0.005;
	sign = 1;
	shouldClose = false;
	currentState = Nothing;
	alpha = 0;

	bodySprite.setScale(bodyScale, bodyScale);
	starSprite.setScale(starScale, starScale);
	buttonSprite.setScale(buttonScale, buttonScale);
}

void Success::Show(RenderWindow& window)
{

	if (rectClock.getElapsedTime().asSeconds() > 0.0005 && alpha < 255.0)
	{
		alpha += 1;
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
		bodyScale += 0.01;

		bodyClock.restart();
	}

	else if (bodyClock.getElapsedTime().asSeconds() > 0.005 && starScale < 1.0 && bodyScale >= 1.0 && shouldClose == false)
	{
		starScale += 0.02;
		bodyClock.restart();
	}

	bodySprite.setScale(bodyScale, bodyScale);
	starSprite.setScale(starScale, starScale);
	window.draw(bodySprite);
	window.draw(starSprite);

	if (length <= completeString.getSize())
	{

		textShow(window, completeString, 75, bodySprite.getGlobalBounds().left + 364, bodySprite.getGlobalBounds().top + 90);
	}
	else
	{
		textSprite.setPosition(completeText.getPosition().x - 6, completeText.getPosition().y + 8);
		window.draw(textSprite);
	}

	textSprite.setScale(textScale, textScale);

	if (buttonClock.getElapsedTime().asSeconds() > time && length > completeString.getSize() && buttonScale < 1.0 && shouldClose == false)
	{
		buttonScale += 0.01;
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
	if (Mouse::isButtonPressed(Mouse::Left) && buttonSprite.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))))
	{
		shouldClose = true;
	}

	buttonSprite.setScale(buttonScale, buttonScale);
	window.draw(buttonSprite);

	if (shouldClose == true && bodyClock.getElapsedTime().asSeconds() > 0.005)
	{
		if (buttonScale > 0)
		{
			buttonScale -= 0.03;
			if (buttonScale < 0)
			{
				buttonScale = 0;
			}
		}
		else if (textScale > 0)
		{
			textScale -= 0.03;
			if (textScale < 0)
			{
				textScale = 0;
			}
		}
		else if (starScale > 0)
		{
			starScale -= 0.3;
			if (starScale < 0)
			{
				starScale = 0;
			}
		}

		else if (bodyScale > 0)
		{
			bodyScale -= 0.03;
			if (bodyScale < 0)
			{
				bodyScale = 0;
			}
		}
		if (bodyScale <= 0)
		{
			currentState = Proceed;
		}
		bodyClock.restart();
	}
}

void Success::textShow(RenderWindow& window, String str, unsigned int char_size, float pos_x, float pos_y)
{
	completeText.setCharacterSize(char_size);
	completeText.setPosition(pos_x, pos_y);

	if (textClock.getElapsedTime().asSeconds() > 0.1 && starScale >= 0.5 && str.getSize() >= length)
	{
		completeText.setString(str.substring(0, length));
		length++;
		textClock.restart();
	}
	window.draw(completeText);
}

Success::State Success::getState()
{
	return currentState;
}
