#include "Visuals.h"

Visuals::Visuals(int windowWidth, int windowHeight, string windowTitle,
	int pipeCount,
	string pathToBirdTexture, string pathToBgTexture,
	string pathToJumpSound, string pathToPointSound, string pathToHitSound,
	string pathToFont)
	: window(windowTitle, sf::Vector2u(windowWidth, windowHeight))
{
	pipeSpritesCount = 2 * pipeCount;
	pipeSprites = new sf::RectangleShape[pipeSpritesCount];

	LoadTexture(birdTexture, birdSprite, pathToBirdTexture);
	birdSprite.setOrigin(birdSprite.getLocalBounds().width / 2, birdSprite.getLocalBounds().height / 2);
	LoadTexture(bgTexture, bgSprite, pathToBgTexture);
	LoadSound(jumpBuffer, jumpSound, pathToJumpSound);
	LoadSound(hitBuffer, hitSound, pathToHitSound);
	LoadSound(pointBuffer, pointSound, pathToPointSound);

	font.loadFromFile(pathToFont);
	scoreText.setFillColor(sf::Color::Black);
	scoreText.setFont(font);
	scoreText.setCharacterSize(20);

	hsText.setFillColor(sf::Color::Black);
	hsText.setFont(font);
	hsText.setCharacterSize(20);

	SetSpritePos(bgSprite, sf::Vector2f(0, 0));
}

void Visuals::LoadSound(sf::SoundBuffer& buffer, sf::Sound& sound, string path)
{
	buffer.loadFromFile(path);
	sound.setBuffer(buffer);
}

void Visuals::LoadTexture(sf::Texture& texture, sf::Sprite& sprite, string path)
{
	texture.loadFromFile(path);
	sprite.setTexture(texture);
}

void Visuals::SetSpritePos(sf::Sprite& sprite, sf::Vector2f position)
{
	sprite.setPosition(position);
}

void Visuals::SetSpriteScale(sf::Sprite& sprite, sf::Vector2f measures)
{
	sprite.setScale(measures);
}

void Visuals::SetShapePos(sf::Shape& shape, sf::Vector2f position)
{
	shape.setPosition(position);
}

void Visuals::SetBirdSpritePos(float x, float y)
{
	SetSpritePos(birdSprite, sf::Vector2f(x, y));
}

void Visuals::SetBirdRotation(float angle)
{
	birdSprite.setRotation(angle);
}

void Visuals::SetBirdScale(float width, float height)
{
	//Dzielenie przez oryginalne wymiary tekstury, aby mozna bylo dzialac na wartosciach podanych w pikselach
	width /= birdTexture.getSize().x;
	height /= birdTexture.getSize().y;
	SetSpriteScale(birdSprite, sf::Vector2f(width, height));
}

void Visuals::InitPipe(int iterator, float x, float y, float width, float height)
{
	pipeSprites[iterator].setFillColor(sf::Color::Green);
	pipeSprites[iterator].setSize(sf::Vector2f(width, height));
	pipeSprites[iterator].setPosition(sf::Vector2f(x, y));
}

void Visuals::SetPipePos(int iterator, float x, float y)
{
	//Wartosc -1 informuje funkcje, ze y ma pozostac niezmienione
	float ypos = y;
	if (y == -1)
	{
		ypos = pipeSprites[iterator].getPosition().y;
	}
	pipeSprites[iterator].setPosition(sf::Vector2f(x, ypos));
}

void Visuals::SetPipeSize(int iterator, float width, float height)
{
	pipeSprites[iterator].setSize(sf::Vector2f(width, height));
}

void Visuals::SetTextPos(float x, float y)
{
	scoreText.setPosition(sf::Vector2f(x, y));
}

void Visuals::SetHSTextPos(float x, float y)
{
	hsText.setPosition(sf::Vector2f(x, y));
}

void Visuals::SetHSTextString(string text)
{
	hsText.setString(text);
}

void Visuals::SetTextString(string text)
{
	scoreText.setString(text);
}

int Visuals::GetWindowWidth()
{
	return window.GetWindowSize().x;
}

int Visuals::GetWindowHeight()
{
	return window.GetWindowSize().y;
}

void Visuals::PlaySound(sf::Sound& sound)
{
	sound.play();
}

void Visuals::PlayJumpSound()
{
	PlaySound(jumpSound);
}

void Visuals::PlayHitSound()
{
	PlaySound(hitSound);
}

void Visuals::PlayPointSound()
{
	PlaySound(pointSound);
}

void Visuals::WindowRender()
{
	//Glowna funkcja obslugujaca renderowanie sprite'ow na ekran za pomoca biblioteki SFML
	window.ClearWindow();
	window.DrawElement(bgSprite);
	for (unsigned i = 0; i < pipeSpritesCount; i++)
	{
		window.DrawElement(pipeSprites[i]);
	}
	window.DrawElement(birdSprite);
	window.DrawElement(scoreText);
	window.DrawElement(hsText);
	window.Display();
}

int Visuals::CheckPressedButton()
{
	return window.CheckPressedButton();
}
