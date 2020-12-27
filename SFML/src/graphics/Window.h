#pragma once
#include <string>
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "../Manager/EventManager.h"

class Window {
public:
	Window();
	Window(const std::string& title, const sf::Vector2u& size);
	~Window();

	void beginDraw();
	void endDraw();

	void update();

	bool isDone();
	bool isFullscreen();
	bool isFocused();

	void toggleFullscreen(EventDetails* l_details);
	void close(EventDetails* l_details = nullptr);

	sf::RenderWindow* getRenderWindow() { return &m_window; }
	sf::Vector2u getWindowSize() { return m_windowSize; }
	EventManager* getEventManager() { return &m_eventManager; }

private:
	void setup(const std::string& title, const sf::Vector2u& size);
	void create();

	EventManager m_eventManager;

	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	bool m_isFullScreen;
	bool m_isFocused;
};