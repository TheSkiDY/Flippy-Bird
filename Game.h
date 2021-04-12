#pragma once
#include "Bird.h"
#include "Pipe.h"
#include "Visuals.h"
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <sstream>

#define JUMP_BUTTON 1
#define RESET_BUTTON 2
#define EXIT_BUTTON 10

class Game
{
private:
	Visuals graphics;
	Bird bird;
	Pipe* pipes;

	const unsigned pipeCount = 5;

	const float distanceMultiplier = 0.2f;
	const float gapHeightMulitplier = 0.2f;
	const float pipeWidthMultiplier = 1.0f / 15.0f;
	const float gapRandomizingMulitplier = 7.0f / 12.0f;
	const float velocityRotationMutliplier = 10.0f;
	const float pipeStartMultiplier = 5.0f / 4.0f;

	const float pipeHitboxTolerance = 5.0f;
	const float hitboxRangeLeft = 1.0f;
	const float hitboxRangeRight = 3.0f;

	const float minJumpHeight = 20.0f;

	const float scoreTextPosX = 20.0f;
	const float scoreTextPosY = 20.0f;
	const float hsTextPosX = 20.0f;
	const float hsTextPosY = 50.0f;

	float distanceBetweenPipes;

	float pipeGapHeight;
	float pipeWidth;

	bool isGameOver = false;
	bool keyBlock = false;
	long score;
	long highScore;

	const float gravity = 0.25f;
	float surfaceYPos;

	bool collisionCheckFlag = false;
	bool scoreAddingFlag = false;
	unsigned pipeIndexToCheck;

	//Inicjalizacja wartosci poczatkowych dla rur - polozenie i rozmiary
	void InitPipes();

	//Glowne funkcje umozliwiajace dzialanie gry
	void Update();
	void Logic();
	void Render();
	void HandleInput();

	//Poruszanie wszystkimi rurami
	void PipeMovement();

	//Sprawdzanie kolizji
	bool CollisionCheck();

	//Ustawienia rotacji ptaka przy zmianie wektora predkosci
	void SetRotation();

	//Aktualizacja polozenia sprite'ow na ekranie
	void UpdateSprites();


public:
	Game();
	~Game();
	void Reset();
	void Run();
	bool gameOver();
};

