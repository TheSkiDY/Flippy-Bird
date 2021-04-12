#include "Game.h"

Game::Game() :
	graphics(WIDTH, HEIGHT, "Flippy Bird", 5, "bird.png", "background.png", "jump.wav", "point.wav", "hit.wav", "font.ttf"),
	bird(graphics.GetWindowWidth() / 2.0f, graphics.GetWindowHeight() / 2.0f, graphics.GetWindowWidth() / 15.0f, graphics.GetWindowHeight() / 15.0f)
{
	distanceBetweenPipes = graphics.GetWindowWidth() * distanceMultiplier;
	pipes = new Pipe[pipeCount];
	pipeGapHeight = graphics.GetWindowHeight() * gapHeightMulitplier;
	pipeWidth = graphics.GetWindowWidth() * pipeWidthMultiplier;
	InitPipes();

	surfaceYPos = (float)graphics.GetWindowHeight();

	graphics.SetBirdSpritePos(bird.GetX(), bird.GetY());
	graphics.SetBirdScale(bird.GetWidth(), bird.GetHeight());

	pipeIndexToCheck = 0;
	score = 0;

	ifstream file("score.txt");
	file >> highScore;
	file.close();

	graphics.SetTextPos(scoreTextPosX, scoreTextPosY);
	graphics.SetHSTextPos(hsTextPosX, hsTextPosY);
	stringstream s, h;
	s << "Score: " << score;
	h << "High Score: " << highScore;
	graphics.SetTextString(s.str());
	graphics.SetHSTextString(h.str());
}

Game::~Game()
{
	delete[] pipes;
}

void Game::Run()
{
	while (!gameOver())
	{
		HandleInput();
		Update();
		Render();
	}
}

void Game::Logic()
{
	//Koniec gry, jesli ptak dotknie podloza
	if (bird.GetY() >= surfaceYPos)
	{
		keyBlock = false;
		Reset();

	}

	//Poruszanie obiektami
	bird.Move(gravity);
	PipeMovement();

	if (collisionCheckFlag && CollisionCheck())
	{
		collisionCheckFlag = false;
		scoreAddingFlag = false;
		graphics.PlayHitSound();	//Zamysl jest taki, aby dzwiek uderzenia o rure odtwarzal sie za kazdym razem,
									//gdy taka sytuacja ma miejsce. Czasami jednak dzwiek nie jest w ogole odwtarzany
									//lub jest ale z opoznieniem lub nawet dwa razy. 
									//Nie jestem w stanie zdiagnozowac zrodla tego bledu.
									//Reszta dzwiekow w kazdym momencie dziala prawidlowo.

		//Klawiatura jest blokowana przy uderzeniu w rure + wszystkie rury sie zatrzymuja
		keyBlock = true;
		bird.Fall();
		for (unsigned i = 0; i < pipeCount; i++)
			pipes[i].Stop();
	}
}

bool Game::CollisionCheck()
{
	float tolerance = pipeHitboxTolerance; //Ustawienie tolerancji na uderzenie w rure (w pikselach)

	//Kolizja odbywa sie gdy przy ustawionej fladze sprawdzania kolizji, pozycja na osi Y ptaka nie znajduje sie w luce miedzy rurami
	return (bird.GetY() - bird.GetHeight() / 2.0f + tolerance < pipes[pipeIndexToCheck].GetGapStartingPoint() || bird.GetY() + bird.GetHeight() / 2.0f - tolerance > pipes[pipeIndexToCheck].GetGapStartingPoint() + pipes[pipeIndexToCheck].GetGapHeight());
}
void Game::PipeMovement()
{
	unsigned previous;

	for (unsigned i = 0; i < pipeCount; i++)
	{
		previous = (i == 0) ? pipeCount - 1 : i - 1;


		//Normalnie warunek powinien sprawdzac po prostu rownosc pozycji na osi X ptaka oraz pozycji na osi X rury
		//Jako ze dzialamy na floatach, taka rownosc niezawsze bedzie spelniona, nawet jesli rura faktycznie przechodzi przez ten punkt
		//Aby naprawic problem istnieja zmienne hitboxRange, ktore wyznaczaja zakres sprawdzania, ktory odpowiada warunkowi rownosci
		if (pipes[i].GetX() - bird.GetWidth() / 2.0f >= (graphics.GetWindowWidth() / 2.0f) - hitboxRangeLeft && pipes[i].GetX() - bird.GetWidth() / 2.0f <= (graphics.GetWindowWidth() / 2.0f) + hitboxRangeLeft)
		{
			//Flaga sprawdzania kolizji jest aktywna, tylko jesli rura znajduje sie w tej samej pozycji na osi X co ptak
			//Sprawia to, ze kolizja jest sprawdzana wylacznie, gdy jest to absolutnie potrzebne
			collisionCheckFlag = true;

			//Wprowadzenie zakresu za pomoca zmiennych hitboxRange wiaze sie z problemem,
			//ze czasem rura znajduje w sprawdzanym zakresie przez kilka iteracji glownej petli aplikacji.
			//Flaga dodawania punktow zapobiega dodawaniu kilku punktow za jedno przejscie przez luke rury
			scoreAddingFlag = true;

			//Indeks rury do sprawdzenia kolizji. Zadna inna nie jest sprawdzana.
			pipeIndexToCheck = i;
		}
		if (pipes[i].GetX() + pipes[i].GetWidth() + bird.GetWidth() / 2.0f >= (graphics.GetWindowWidth() / 2.0f) - hitboxRangeRight && pipes[i].GetX() + pipes[i].GetWidth() + bird.GetWidth() / 2.0f <= (graphics.GetWindowWidth() / 2) + hitboxRangeRight)
		{
			collisionCheckFlag = false;
			if (scoreAddingFlag)
			{
				//Mechanizm obslugi dodania punktu przez przejscie przez rure. Dzieje sie tylko raz
				//ze wzgledu na wprowadzenie flagi scoreAddingFlag
				score++;
				graphics.PlayPointSound();
				stringstream s;
				s << "Score: " << score;
				graphics.SetTextString(s.str());
				scoreAddingFlag = false;
			}

		}


		if (pipes[i].GetX() + pipes[i].GetWidth() < 0)
		{
			//Gdy rura wyjdzie za ekran jest ona cofana za ostatnia nadchodzaca z prawej strony
			//Losowane i ustawiane na nowo jest takze polozenie luki
			pipes[i].SetX(pipes[previous].GetX() + pipes[previous].GetWidth() + distanceBetweenPipes);
			pipes[i].SetGapStartingPoint((float)(rand() % (int)(graphics.GetWindowHeight() * gapRandomizingMulitplier)));

			graphics.SetPipeSize(2 * i, pipes[i].GetWidth(), pipes[i].GetGapStartingPoint());
			graphics.SetPipeSize(2 * i + 1, pipes[i].GetWidth(), graphics.GetWindowHeight() - pipes[i].GetGapHeight() - pipes[i].GetGapStartingPoint());
			graphics.SetPipePos(2 * i + 1, pipes[i].GetX(), pipes[i].GetGapStartingPoint() + pipes[i].GetGapHeight());
		}

		pipes[i].Move();
	}
}

void Game::Update()
{
	Logic();
	UpdateSprites();
}

void Game::Render()
{
	graphics.WindowRender();
}

void Game::HandleInput()
{
	switch (graphics.CheckPressedButton())
	{
	case JUMP_BUTTON:
		if (!keyBlock)

			//Skok mozna wykonac tylko w okreslonej odleglosci od sufitu,
			//aby zapobiec przeskakiwaniu nad rurami wychodzac poza ekran
			if (bird.GetY() >= minJumpHeight)
			{
				bird.Jump();
				graphics.PlayJumpSound();
			}
		break;
	case RESET_BUTTON:
		Reset();
		break;
	case EXIT_BUTTON:
		isGameOver = true;
		break;
	}
}

void Game::SetRotation()
{
	//Kat rotacji ptaka jest ustalony na podstawie jego wektora predkosci
	graphics.SetBirdRotation(velocityRotationMutliplier * bird.GetVelocity());
}

void Game::UpdateSprites()
{
	for (unsigned i = 0; i < pipeCount; i++)
	{
		graphics.SetPipePos(2 * i, pipes[i].GetX(), -1);
		graphics.SetPipePos(2 * i + 1, pipes[i].GetX(), -1);
	}
	graphics.SetBirdSpritePos(bird.GetX(), bird.GetY());
	SetRotation();
}

bool Game::gameOver()
{
	return isGameOver;
}

void Game::InitPipes()
{
	int j;
	srand((unsigned)time(NULL));
	float startingX = pipeStartMultiplier * graphics.GetWindowWidth();
	for (unsigned i = 0; i < pipeCount; i++)
	{
		//Losowanie polozenia luki miedzy gorna a dolna czescia rury
		pipes[i].SetGapStartingPoint((float)(rand() % (int)(gapRandomizingMulitplier * graphics.GetWindowHeight())));
		pipes[i].SetGapHeight(pipeGapHeight);

		pipes[i].SetWidth(pipeWidth);

		//Poczatkowo wszystkie rury ustawiane sa jedna po drugiej poza ekranem
		pipes[i].SetX(startingX + (pipes[i].GetWidth() + distanceBetweenPipes) * i);

		//Ustawienie parametrow prostokatow odpowiadajacych rurom
		//Dla kazdej rury istnieja dwa prostokaty (czesc gorna nad luka oraz czesc dolna pod luka)
		j = 2 * i;
		graphics.InitPipe(j, pipes[i].GetX(), 0, pipes[i].GetWidth(), pipes[i].GetGapStartingPoint());
		graphics.InitPipe(j + 1, pipes[i].GetX(), pipes[i].GetGapStartingPoint() + pipes[i].GetGapHeight(), pipes[i].GetWidth(), graphics.GetWindowHeight() - pipes[i].GetGapHeight() - pipes[i].GetGapStartingPoint());
	}
}

void Game::Reset()
{
	if (score > highScore)
	{
		highScore = score;
		ofstream file("score.txt");
		file << highScore;
		file.close();
	}

	score = 0;
	stringstream h;
	h << "High Score: " << highScore;
	graphics.SetTextString("Score: 0");
	graphics.SetHSTextString(h.str());

	InitPipes();
	bird.Reset();
	collisionCheckFlag = false;
	scoreAddingFlag = false;
	for (unsigned i = 0; i < pipeCount; i++)
		pipes[i].Go();
}