#pragma once

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "../Manager/EventManager.h"


class Window
{

public: 
	Window();
	Window(std::string& title, const sf::Vector2u& size);
	~Window();

	void beginDraw();
	void endDraw();

	void update();
	void draw(sf::Drawable& drawable);

	bool isFocused() { return m_isFocused; }
	bool isDone();
	bool isFullScreen();

	sf::Vector2u getWindowSize();
	EventManager* getEventManager() { return &m_eventManager; }

	void toggleFullScreen(EventDetails* details);
	void close(EventDetails* details = nullptr);



private:
	void setup(const std::string& title, const sf::Vector2u& size);
	void destroy();
	void create();

	EventManager m_eventManager;

	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	bool m_isFullScreen;
	bool m_isFocused;
};

