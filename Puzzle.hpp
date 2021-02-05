#ifndef puzzle_air321
#define puzzle_air321

using namespace std;
using namespace sf;
#include "CustomText.hpp"

class Puzzle
{
private:
	bool solved;
	bool stopWatchStarted;
	bool shouldStopEverything;
	bool can_click;
	IntRect buttonRect;
	vector<Sprite> buttons;
	RectangleShape watchRectangle;
	CustomText custext;
	enum Rotation
	{
		no_rotation = 0,
		clockwise = 1,
		anticlockwise = 2
	};
	class OutputMeter
	{
	public:
		Sprite meterSprite;
		Sprite handSprite;
		Sprite hintSprite;
		// int handRotation;
		// int hintRotation;
		float targetRotation;
		float currentRotation;
		Rotation rotation;
		// bool targetRotationSet;
	};
	class InputMeter
	{
	public:
		Sprite meterSprite;
		Sprite handSprite;
		float handRotation;
		float targetRotation;
		float currentRotation;
		Rotation rotation;
		// bool targetRotationSet;
	};
	Vector2f mousePosition;
	Vector2f mousePositionClicked;
	float temp;
	bool meter1active;
	bool meter2active;
	bool shouldRotate;
	bool rotateClockwise;
	bool shouldSetRotation;
	// int targetRotation;

	Text stopWatchText;
	Clock stopWatch;
	float secondsRemainStore;
	float secondsRemain;

public:
	Puzzle();
	enum State
	{
		Nothing = 0,
		Solved = 1,
		Failed = 2
	};
	void make(int outTicksInit, int outHintTicks, int inTicksInit1, int inTicks1, int inTicksInit2, int inTicks2, float timeRemain);
	void Show(RenderWindow& window, Event& event);
	State getState();
	// vector<InputMeter> inMeters;
	OutputMeter outMeter;
	InputMeter inMeter1;
	InputMeter inMeter2;
	Puzzle::State state;
	int k;
	unsigned i, j;
};
#endif