#pragma once
#include "BaseState.h"
#include "../Manager/EventManager.h"
#include "../Manager/StateManager.h"

class StatePaused: public BaseState
{
public:
	StatePaused(StateManager* stateManager);
	~StatePaused();
	virtual void onCreate() override;
	virtual void onDestroy() override;
	virtual void activate() override;
	virtual void deActivate() override;
	virtual void update(const sf::Time& time) override;
	virtual void draw() override;

	void unpause(EventDetails* details);

private:
	sf::Font m_font;
	sf::Text m_text;
	sf::RectangleShape m_rect;
};
