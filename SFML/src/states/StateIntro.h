#pragma once
#include "BaseState.h"
#include "../Manager/EventManager.h" 

class StateIntro : public BaseState
{
public:
	StateIntro(StateManager* stateManager);
	~StateIntro();

	void onCreate();
	void onDestroy();

	void activate();
	void deActivate();

	void draw();
	void update(const sf::Time& l_time);

	void Continue(EventDetails* details);
private:
	sf::Texture m_introTexture;
	sf::Sprite m_introSprite;
	sf::Text m_introText;
	float m_timePassed;
};

