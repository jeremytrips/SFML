#pragma once

#include "../graphics/Window.h"

class Game
{
public:
	Game();
	~Game();

	Window* getWindow();

	void handlInput();
	void update();
	void render();

	sf::Time getElapsed() { return m_elapsed; }
	void restartClock() { m_elapsed += m_clock.restart(); }

private:
	Window m_window;
	sf::Clock m_clock;
	sf::Time m_elapsed;
};

