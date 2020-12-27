#pragma once
#include "BaseState.h"
#include "../Manager/StateManager.h"


class EventDetails;

class StateMainMenu: public BaseState
{
public:
	StateMainMenu(StateManager* stateManager);
	~StateMainMenu();

	void onCreate();
	void onDestroy();
	void activate();
	void deActivate();
	void update(const sf::Time& time);
	void draw();

	void mouseClick(EventDetails* details);
private:
	sf::Text m_text;
	sf::Vector2f m_buttonSize;
	sf::Vector2f m_buttonPos;
	unsigned int m_buttonPadding;

	sf::RectangleShape m_rects[3];
	sf::Text m_labels[3];
};

