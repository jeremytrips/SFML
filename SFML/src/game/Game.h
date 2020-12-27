#pragma once
#include "../graphics/Window.h"
#include "../Manager/EventManager.h"
#include "../Manager/StateManager.h"
#include <iostream>

class Game {
public:
	Game();
	~Game();

	void update();
	void render();
	void lateUpdate();

	sf::Time getElapsed();

	Window* getWindow();
private:
	Window m_window;
	SharedContext m_sharedContext;
	StateManager m_stateManager;
	sf::Clock m_clock;
	sf::Time m_elapsed;
	void restartClock();
};
