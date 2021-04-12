#include "Bird.h"

Bird::Bird(float x, float y, float width, float height)
{
	this->x = x;
	this->y = this->startingY = y;
	this->width = width;
	this->height = height;
	vel_y = startingVel;


}

float Bird::GetVelocity()
{
	return this->vel_y;
}

float Bird::GetX()
{
	return x;
}

float Bird::GetY()
{
	return y;
}

float Bird::GetHeight()
{
	return height;
}

float Bird::GetWidth()
{
	return width;
}

void Bird::Move(float gravity)
{
	UpdateVelocity(gravity);
	y += vel_y;
}

void Bird::UpdateVelocity(float gravity)
{
	if (vel_y < maxVel)
		this->vel_y += gravity;
}

void Bird::Jump()
{
	this->vel_y = jumpVel;
}

void Bird::Reset()
{
	this->y = startingY;
	this->vel_y = startingVel;
}

void Bird::Fall()
{
	this->vel_y = fallVel;
}