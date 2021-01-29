#include "CustomText.hpp"
#include "GetRes.hpp"

CustomText::CustomText()
{
	currentLength = 1;
	sign = 1;
	green_blue = 174;
	index = 0;

	fullShowed = false;
	hidingFinished = false;
	waiting_finished = false;
	text.setFont(GetRes::techFont);
	text.setFillColor(Color(255, green_blue, green_blue));
}

void CustomText::Show(RenderWindow& window, sf::String str, unsigned int char_size, float pos_x, float pos_y, float hide_after_seconds, bool shouldHighlight, float text_popping_delay, sf::Color color)
{
	text.setCharacterSize(char_size);
	text.setPosition(pos_x, pos_y);

	if (shouldHighlight == true)
	{
		if (highlightClock.getElapsedTime().asSeconds() > 0.001)
		{
			if (green_blue >= 174)
			{
				green_blue = 174;
				sign = -1;
			}
			else if (green_blue <= 0)
			{
				green_blue = 0;
				sign = 1;
			}

			green_blue += 2 * sign;
			text.setFillColor(Color(255, green_blue, green_blue));
			highlightClock.restart();
		}
	}
	else
	{
		text.setFillColor(color);
	}

	if (str.getSize() >= currentLength)
	{
		if (clock.getElapsedTime().asSeconds() > text_popping_delay)
		{
			text.setString(str.substring(0, currentLength));
			currentLength++;
			clock.restart();
		}
		window.draw(text);
	}
	else
	{
		if (hide_after_seconds != -1.0)
		{
			if (index <= str.getSize())
			{
				if (waiting_finished == true)
				{
					time_to_wait = text_popping_delay;
				}
				else
				{
					time_to_wait = hide_after_seconds;
				}

				if (clock.getElapsedTime().asSeconds() > time_to_wait)
				{
					waiting_finished = true;
					text.setString(str.substring(index, str.getSize() - index));
					test = text.getString();
					index++;
					clock.restart();
				}
				window.draw(text);
				fullShowed = true;
			}
			else
			{
				hidingFinished = true;
			}
		}
		else
		{
			window.draw(text);
			fullShowed = true;
		}
	}
}
