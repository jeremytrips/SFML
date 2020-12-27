#pragma once
#include "BaseState.h"
#include "../Manager/EventManager.h"
#include "../Manager/StateManager.h"

class StateGame:public BaseState
{
public:
	StateGame(StateManager* stateManager);
	~StateGame();
	void onCreate();
	void onDestroy();
	void activate();
	void deActivate();
	void update(const sf::Time& time);
	void draw();

	void mainMenu(EventDetails* details);
	void pause(EventDetails* details);

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_increment;
};

