#pragma once

class Bird
{
private:
	float x, y;
	float height, width;
	float vel_y;
	float startingY;

	const float startingVel = -5.0f;
	const float jumpVel = -4.0f;
	const float maxVel = 4.0f;
	const float fallVel = 5.5f;

	void UpdateVelocity(float);

public:
	Bird(float, float, float, float);

	float GetX();
	float GetY();
	float GetHeight();
	float GetWidth();
	float GetVelocity();

	void Reset();
	void Move(float gravity);
	void Jump();
	void Fall();
};

