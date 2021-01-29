#include "Puzzle.hpp"
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
	stopWatchText.setFillColor(Color::Red);
	stopWatchText.setPosition(20, 20);

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
}

void Puzzle::Show(RenderWindow& window, Event& event)
{
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
		window.clear(Color::Blue);

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
		stopWatchText.setString(to_string(int(secondsRemain)));

		// winning
		if (outMeter.handSprite.getRotation() == outMeter.hintSprite.getRotation())
		{
			cout << "win" << endl;
			meter1active = false;
			meter2active = false;
			shouldStopEverything = true;
			solved = true;
			state = Solved;
			break;
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
		GameUI::showMenuUI(window);

		window.display();
	}
	cout << "breaked" << endl;
}

Puzzle::State Puzzle::getState()
{
	return state;
}