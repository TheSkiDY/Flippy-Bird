#include "Window.h"

Window::Window()
{
	Setup("Flippy Bird", sf::Vector2u(HEIGHT, WIDTH));
}

Window::Window(const string& windowTitle, const sf::Vector2u& windowSize)
{
	Setup(windowTitle, windowSize);
}

Window::~Window()
{
	this->window.close();
}

void Window::Setup(const string& windowTitle, const sf::Vector2u& windowSize)
{
	this->windowSize = windowSize;
	this->windowTitle = windowTitle;
	this->window.create({ this->windowSize.x,this->windowSize.y }, windowTitle, sf::Style::Close);
	this->window.setFramerateLimit(this->maxFPS);
}

void Window::ClearWindow()
{
	this->window.clear(sf::Color::Black);
}

void Window::Display()
{
	this->window.display();
}

void Window::DrawElement(sf::Drawable& drawable)
{
	this->window.draw(drawable);
}

int Window::CheckPressedButton()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			return 10;
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			switch (event.key.code)
			{
			case sf::Mouse::Left:
				return 1;
			}
		}
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Space:
			case sf::Keyboard::Up:
				return 1;
			case sf::Keyboard::R:
				return 2;
			case sf::Keyboard::Escape:
				return 10;
			}
		}
	}
	return 0;
}

sf::Vector2u Window::GetWindowSize()
{
	return this->windowSize;
}