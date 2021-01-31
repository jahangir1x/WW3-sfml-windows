#include "Puzzle.hpp"
#include "CustomText.hpp"
#include "GameUI.hpp"
#include "GetRes.hpp"
#include "Helper.hpp"
#include "LevelFailed.hpp"
#include "LevelHelper.hpp"
#include "Success.hpp"

using namespace std;
using namespace sf;
Puzzle::Puzzle()
{
	custext.shouldMute = true;
	state = Nothing;
	solved = false;
	GameUI::init();
	stopWatchStarted = false;
	outMeter.meterSprite.setTexture(GetRes::outMeter);
	outMeter.handSprite.setTexture(GetRes::outMeterHand);
	outMeter.hintSprite.setTexture(GetRes::outMeterHint);

	inMeter1.meterSprite.setTexture(GetRes::inMeter);
	inMeter1.handSprite.setTexture(GetRes::inMeterHand);
	inMeter2.meterSprite.setTexture(GetRes::inMeter);
	inMeter2.handSprite.setTexture(GetRes::inMeterHand);

	stopWatchText.setFont(GetRes::techFont);
	stopWatchText.setString("99");
	stopWatchText.setFillColor(Color(223, 75, 75));
	stopWatchText.setPosition(20, 20);
	watchRectangle.setSize(Vector2f(312, 74));
	watchRectangle.setPosition(10, 15);
	watchRectangle.setFillColor(Color(71, 71, 71));

	buttons.resize(Helper::randRange(3, 8));
	for (auto& sprite : buttons)
	{
		sprite.setTexture(GetRes::dummyButtons);
		buttonRect.left = 0;
		buttonRect.top = 0;
		buttonRect.width = 57;
		buttonRect.height = 150;
		if (bool(rand() % 2))
		{
			buttonRect.left = 0;
		}
		else
		{
			buttonRect.left = buttonRect.width;
		}
		sprite.setTextureRect(buttonRect);
		sprite.setRotation(rand() % 360);
		k = Helper::randRange(50, 160);
		sprite.setScale(k / 100.0 * Helper::getScalingFactor(), k / 100.0 * Helper::getScalingFactor());
		sprite.setPosition(Helper::randRange(0, Helper::windowWidth()), Helper::randRange(0, Helper::windowHeight())); // set random position
	}

	meter1active = false;
	meter2active = false;
	shouldRotate = false;
	rotateClockwise = false;
	shouldSetRotation = false;
	can_click = false;
	shouldStopEverything = false;
	inMeter1.rotation = no_rotation;
	inMeter2.rotation = no_rotation;
	outMeter.rotation = no_rotation;
}

void Puzzle::make(int outTicksInit, int outHintTicks, int inTicksInit1, int inTicks1, int inTicksInit2, int inTicks2, float timeRemain)
{

	// out meter
	outMeter.meterSprite.setOrigin(outMeter.meterSprite.getGlobalBounds().width / 2, outMeter.meterSprite.getGlobalBounds().height / 2);
	outMeter.handSprite.setOrigin(10, outMeter.handSprite.getGlobalBounds().height / 2);
	outMeter.hintSprite.setOrigin(10, outMeter.hintSprite.getGlobalBounds().height / 2);

	outMeter.meterSprite.setPosition(Helper::windowWidth() / 2, (outMeter.meterSprite.getGlobalBounds().height / 2) + 20);
	outMeter.handSprite.setPosition(outMeter.meterSprite.getPosition().x, outMeter.meterSprite.getPosition().y);
	outMeter.hintSprite.setPosition(outMeter.meterSprite.getPosition().x, outMeter.meterSprite.getPosition().y);

	outMeter.handSprite.setRotation(outTicksInit * 360 / 30);
	outMeter.hintSprite.setRotation(outHintTicks * 360 / 30);

	// meter 1
	inMeter1.meterSprite.setOrigin(inMeter1.meterSprite.getGlobalBounds().width / 2, inMeter1.meterSprite.getGlobalBounds().height / 2);
	inMeter1.handSprite.setOrigin(10, inMeter1.handSprite.getGlobalBounds().height / 2);

	inMeter1.meterSprite.setPosition(Helper::windowWidth() / 4, outMeter.meterSprite.getPosition().y + outMeter.meterSprite.getGlobalBounds().height + 20);
	inMeter1.handSprite.setPosition(inMeter1.meterSprite.getPosition().x, inMeter1.meterSprite.getPosition().y);

	inMeter1.handSprite.setRotation(inTicksInit1 * 360 / 30);
	inMeter1.handRotation = inTicks1 * 360 / 30;

	//meter 2
	inMeter2.meterSprite.setOrigin(inMeter2.meterSprite.getGlobalBounds().width / 2, inMeter2.meterSprite.getGlobalBounds().height / 2);
	inMeter2.handSprite.setOrigin(10, inMeter2.handSprite.getGlobalBounds().height / 2);

	inMeter2.meterSprite.setPosition(Helper::windowWidth() * 3 / 4, outMeter.meterSprite.getPosition().y + outMeter.meterSprite.getGlobalBounds().height + 20);
	inMeter2.handSprite.setPosition(inMeter2.meterSprite.getPosition().x, inMeter2.meterSprite.getPosition().y);

	inMeter2.handSprite.setRotation(inTicksInit2 * 360 / 30);
	inMeter2.handRotation = inTicks2 * 360 / 30;

	inMeter1.targetRotation = inMeter1.handSprite.getRotation();
	inMeter2.targetRotation = inMeter2.handSprite.getRotation();
	outMeter.targetRotation = outMeter.handSprite.getRotation();

	inMeter1.currentRotation = inMeter1.handSprite.getRotation();
	inMeter2.currentRotation = inMeter2.handSprite.getRotation();
	outMeter.currentRotation = outMeter.handSprite.getRotation();

	stopWatchText.setString(to_string(timeRemain));
	stopWatchText.setCharacterSize(40);
	stopWatch.restart();
	secondsRemainStore = timeRemain;

	for (i = 0; i < buttons.size(); i++)
	{
		for (j = i + 1; j < buttons.size(); j++)
		{
			if (i == j)
			{
				continue;
			}
			else
			{
				if (buttons[j].getGlobalBounds().intersects(buttons[i].getGlobalBounds()) || outMeter.meterSprite.getGlobalBounds().intersects(buttons[i].getGlobalBounds()) || inMeter1.meterSprite.getGlobalBounds().intersects(buttons[i].getGlobalBounds()) || inMeter2.meterSprite.getGlobalBounds().intersects(buttons[i].getGlobalBounds()) || watchRectangle.getGlobalBounds().intersects(buttons[i].getGlobalBounds())) // check if it intersects then set it outside
				{
					buttons[i].setPosition(Helper::windowWidth() + 100, Helper::windowHeight() + 100);
				}
			}
		}
	}
}

void Puzzle::Show(RenderWindow& window, Event& event)
{

	Music music;
	music.openFromFile("res/music/tension.wav");
	music.setVolume(30);
	music.play();

	while (window.isOpen())
	{
		if (stopWatchStarted == false)
		{
			stopWatch.restart();
			stopWatchStarted = true;
		}
		Helper::resetClock();
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				exit(0);
			}
			else if (event.type == Event::MouseMoved)
			{
				mousePosition = Vector2f(Mouse::getPosition(window));
			}
			else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
			{
				mousePositionClicked = Mouse::getPosition(window);
				GameUI::handleClose(window, mousePositionClicked);
			}
			else if (event.type == Event::KeyReleased)
			{
				shouldSetRotation = false;
				if (event.key.code == Keyboard::A)
				{
					shouldSetRotation = true;
					rotateClockwise = false;
				}
				else if (event.key.code == Keyboard::D)
				{
					shouldSetRotation = true;
					rotateClockwise = true;
				}
			}
		}
		window.clear(Color(45, 45, 45));
		for (auto& sprite : buttons)
		{
			window.draw(sprite);
		}
		window.draw(watchRectangle);

		if (meter1active == false)
		{
			if (inMeter1.meterSprite.getGlobalBounds().contains(mousePosition))
			{
				inMeter1.meterSprite.setTexture(GetRes::inMeterHover);
			}
			else
			{
				inMeter1.meterSprite.setTexture(GetRes::inMeter);
			}
		}

		if (meter2active == false)
		{
			if (inMeter2.meterSprite.getGlobalBounds().contains(mousePosition))
			{
				inMeter2.meterSprite.setTexture(GetRes::inMeterHover);
			}
			else
			{
				inMeter2.meterSprite.setTexture(GetRes::inMeter);
			}
		}

		//click
		if (shouldStopEverything == false && can_click == true && inMeter1.meterSprite.getGlobalBounds().contains(Vector2f(mousePositionClicked)))
		{
			inMeter1.meterSprite.setTexture(GetRes::inMeterClick);
			meter2active = false;
			meter1active = true;
		}
		if (shouldStopEverything == false && can_click == true && inMeter2.meterSprite.getGlobalBounds().contains(Vector2f(mousePositionClicked)))
		{
			inMeter2.meterSprite.setTexture(GetRes::inMeterClick);
			meter1active = false;
			meter2active = true;
		}

		// set target rotation

		if (shouldSetRotation)
		{
			if (meter1active)
			{
				if (rotateClockwise)
				{
					inMeter1.targetRotation = inMeter1.currentRotation + inMeter1.handRotation;
					outMeter.targetRotation = outMeter.currentRotation + inMeter1.handRotation;
					inMeter1.rotation = clockwise;
					outMeter.rotation = clockwise;
				}
				else
				{
					inMeter1.targetRotation = inMeter1.currentRotation - inMeter1.handRotation;
					outMeter.targetRotation = outMeter.currentRotation - inMeter1.handRotation;
					inMeter1.rotation = anticlockwise;
					outMeter.rotation = anticlockwise;
				}
			}

			else if (meter2active)
			{
				if (rotateClockwise)
				{
					inMeter2.targetRotation = inMeter2.currentRotation + inMeter2.handRotation;
					outMeter.targetRotation = outMeter.currentRotation + inMeter2.handRotation;
					inMeter2.rotation = clockwise;
					outMeter.rotation = clockwise;
				}
				else
				{
					inMeter2.targetRotation = inMeter2.currentRotation - inMeter2.handRotation;
					outMeter.targetRotation = outMeter.currentRotation - inMeter2.handRotation;
					inMeter2.rotation = anticlockwise;
					outMeter.rotation = anticlockwise;
				}
			}
			shouldSetRotation = false;
			cout << "in1: " << inMeter1.handSprite.getRotation() << " " << inMeter1.targetRotation << endl;
			cout << "in2: " << inMeter2.handSprite.getRotation() << " " << inMeter2.targetRotation << endl;
			cout << "out: " << outMeter.handSprite.getRotation() << " " << outMeter.targetRotation << endl;
		}

		// fix rotations
		if (inMeter1.targetRotation < 0)
		{
			inMeter1.targetRotation = 360 + inMeter1.targetRotation;
		}
		if (inMeter1.targetRotation >= 360)
		{
			inMeter1.targetRotation = inMeter1.targetRotation - 360;
		}

		if (inMeter2.targetRotation < 0)
		{
			inMeter2.targetRotation = 360 + inMeter2.targetRotation;
		}
		if (inMeter2.targetRotation >= 360)
		{
			inMeter2.targetRotation = inMeter2.targetRotation - 360;
		}

		if (outMeter.targetRotation < 0)
		{
			outMeter.targetRotation = 360 + outMeter.targetRotation;
		}
		if (outMeter.targetRotation >= 360)
		{
			outMeter.targetRotation = outMeter.targetRotation - 360;
		}

		// rotate
		if (inMeter1.targetRotation != inMeter1.handSprite.getRotation())
		{
			can_click = false;
			if (inMeter1.rotation == clockwise)
			{
				inMeter1.handSprite.setRotation(inMeter1.handSprite.getRotation() + 70 * Helper::SecondsPerFrame());
				outMeter.handSprite.setRotation(outMeter.handSprite.getRotation() + 70 * Helper::SecondsPerFrame());
			}
			else if (inMeter1.rotation == anticlockwise)
			{
				inMeter1.handSprite.setRotation(inMeter1.handSprite.getRotation() - 70 * Helper::SecondsPerFrame());
				outMeter.handSprite.setRotation(outMeter.handSprite.getRotation() - 70 * Helper::SecondsPerFrame());
			}

			if (abs(inMeter1.handSprite.getRotation() - inMeter1.targetRotation) < 3)
			{
				inMeter1.handSprite.setRotation(inMeter1.targetRotation);
				inMeter1.currentRotation = inMeter1.handSprite.getRotation();
				outMeter.handSprite.setRotation(outMeter.targetRotation);
				outMeter.currentRotation = outMeter.handSprite.getRotation();
				can_click = true;
			}
		}
		else
		{
			can_click = true;
		}

		if (inMeter2.targetRotation != inMeter2.handSprite.getRotation())
		{
			can_click = false;
			if (inMeter2.rotation == clockwise)
			{
				inMeter2.handSprite.setRotation(inMeter2.handSprite.getRotation() + 70 * Helper::SecondsPerFrame());
				outMeter.handSprite.setRotation(outMeter.handSprite.getRotation() + 70 * Helper::SecondsPerFrame());
			}
			else if (inMeter2.rotation == anticlockwise)
			{
				inMeter2.handSprite.setRotation(inMeter2.handSprite.getRotation() - 70 * Helper::SecondsPerFrame());
				outMeter.handSprite.setRotation(outMeter.handSprite.getRotation() - 70 * Helper::SecondsPerFrame());
			}

			if (abs(inMeter2.handSprite.getRotation() - inMeter2.targetRotation) < 3)
			{
				inMeter2.handSprite.setRotation(inMeter2.targetRotation);
				inMeter2.currentRotation = inMeter2.handSprite.getRotation();
				outMeter.handSprite.setRotation(outMeter.targetRotation);
				outMeter.currentRotation = outMeter.handSprite.getRotation();
				can_click = true;
			}
		}
		else
		{
			can_click = true;
		}

		//stopwatch
		if (shouldStopEverything == false)
		{

			secondsRemain = int(secondsRemainStore - stopWatch.getElapsedTime().asSeconds());
		}
		if (secondsRemain < 0)
		{
			// failed.
			secondsRemain = 0;
			cout << "fail" << endl;
			meter1active = false;
			meter2active = false;
			shouldStopEverything = true;
			solved = false;
			state = Failed;
			break;
		}
		stopWatchText.setString("Time Remaining: " + to_string(int(secondsRemain)));

		// winning
		if (outMeter.handSprite.getRotation() == outMeter.hintSprite.getRotation())
		{
			outMeter.meterSprite.setTexture(GetRes::outMeterSuccess);
			cout << "win" << endl;
			meter1active = false;
			meter2active = false;
			shouldStopEverything = true;
			solved = true;
			state = Solved;
			break;
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			cout << "mpos: " << Mouse::getPosition(window).x << " " << Mouse::getPosition(window).y << endl;
		}

		//display
		window.draw(outMeter.meterSprite);
		window.draw(outMeter.handSprite);
		window.draw(outMeter.hintSprite);

		window.draw(inMeter1.meterSprite);
		window.draw(inMeter1.handSprite);

		window.draw(inMeter2.meterSprite);
		window.draw(inMeter2.handSprite);

		window.draw(stopWatchText);

		custext.Show(window, "Select left and right meter and\npress A and D to calibrate.\nYour goal is to set the same rotation\nto both hands of the output meter.", 24, watchRectangle.getPosition().x, watchRectangle.getPosition().y + watchRectangle.getSize().y + 10, -1, true, 0.01);

		GameUI::showMenuUI(window);

		window.display();
	}
	cout << "breaked" << endl;
}

Puzzle::State Puzzle::getState()
{
	return state;
}