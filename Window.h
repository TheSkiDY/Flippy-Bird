#pragma once
#include <SFML/Graphics.hpp>

#define WIDTH 640
#define HEIGHT 480

using namespace std;

class Window
{
private:
	void Setup(const string& windowTitle, const sf::Vector2u& windowSize);

	string windowTitle;
	sf::Vector2u windowSize;
	sf::RenderWindow window;

	const int maxFPS = 60;

public:
	Window();
	Window(const string& windowTitle, const sf::Vector2u& windowSize);
	~Window();

	void ClearWindow();
	void Display();
	bool CheckWindowClosing();
	int CheckPressedButton();
	void DrawElement(sf::Drawable&);

	sf::Vector2u GetWindowSize();
};

