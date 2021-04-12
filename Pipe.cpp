#include "Pipe.h"

Pipe::Pipe()
{
	this->width = WIDTH / 20;
	this->velX = this->startVelX = 1.5f;
	x = yGap = gapHeight = 0;
}

void Pipe::Move()
{
	this->x -= this->velX;
}

float Pipe::GetX()
{
	return this->x;
}

void Pipe::SetX(float x)
{
	this->x = x;
}

float Pipe::GetVelocity()
{
	return this->velX;
}

float Pipe::GetGapStartingPoint()
{
	return this->yGap;
}

float Pipe::GetGapHeight()
{
	return this->gapHeight;
}

void Pipe::SetGapHeight(float height)
{
	this->gapHeight = height;
}

void Pipe::SetGapStartingPoint(float y)
{
	this->yGap = y;
}

void Pipe::SetWidth(float width)
{
	this->width = width;
}

float Pipe::GetWidth()
{
	return width;
}

void Pipe::Stop()
{
	this->velX = 0;
}

void Pipe::Go()
{
	this->velX = this->startVelX;
}