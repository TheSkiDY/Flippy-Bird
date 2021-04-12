#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Window.h"

using namespace std;

class Visuals
{
private:
	sf::Texture birdTexture, bgTexture;
	sf::Sprite birdSprite, bgSprite;
	sf::RectangleShape* pipeSprites;
	unsigned pipeSpritesCount;

	sf::SoundBuffer jumpBuffer, pointBuffer, hitBuffer;
	sf::Sound jumpSound, pointSound, hitSound;

	sf::Font font;
	sf::Text scoreText;
	sf::Text hsText;

	Window window;

	void LoadTexture(sf::Texture& texture, sf::Sprite& sprite, string path);
	void LoadSound(sf::SoundBuffer& buffer, sf::Sound& sound, string path);
	void SetSpritePos(sf::Sprite& sprite, sf::Vector2f position);
	void SetSpriteScale(sf::Sprite& sprite, sf::Vector2f measures);
	void SetShapePos(sf::Shape& shape, sf::Vector2f position);
	void PlaySound(sf::Sound& sound);
public:
	Visuals(int windowWidth, int windowHeight, string windowTitle, int pipeCount, string pathToBirdTexture, string pathToBgTexture, string pathToJumpSound, string pathToPointSound, string pathToHitSound, string pathToFont);;
	void SetBirdSpritePos(float x, float y);
	void SetBirdScale(float width, float height);
	void InitPipe(int iterator, float x, float y, float width, float height);
	void SetPipePos(int iterator, float x, float y);
	void SetPipeSize(int iterator, float width, float height);
	void SetBirdRotation(float angle);
	void SetTextPos(float x, float y);
	void SetHSTextPos(float x, float y);
	void SetTextString(string text);
	void SetHSTextString(string text);

	void PlayJumpSound();
	void PlayHitSound();
	void PlayPointSound();

	int CheckPressedButton();
	int GetWindowHeight();
	int GetWindowWidth();
	void WindowRender();

};

