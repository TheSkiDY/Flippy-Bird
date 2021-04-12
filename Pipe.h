#pragma once
#include "Window.h"

class Pipe
{
private:
	float x, yGap, gapHeight;
	float width;
	float velX;
	float startVelX;

public:
	Pipe();

	void Move();
	void Stop();
	void Go();
	float GetX();
	float GetVelocity();
	float GetGapStartingPoint();
	float GetGapHeight();
	float GetWidth();
	void SetX(float x);
	void SetGapHeight(float height);
	void SetGapStartingPoint(float y);
	void SetWidth(float width);
};

