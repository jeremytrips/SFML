#pragma once
#include <SFML/Graphics.hpp>

class StateManager;

class BaseState {
	friend StateManager;

public:
	BaseState(StateManager* stateManager)
		: m_stateManager(stateManager), m_transcendent(false), m_transparent(false) {}
	virtual ~BaseState() {}
	
	virtual void onCreate() = 0;
	virtual void onDestroy() = 0;

	virtual void activate() = 0;
	virtual void deActivate() = 0;

	virtual void update(const sf::Time& time) = 0;
	virtual void draw() = 0;

	void setTransparent(const bool& transparent) {
		m_transparent = transparent;
	}

	void setTranscendent(const bool& transcendent) {
		m_transcendent = transcendent;
	}

	bool isTransparent() const { return m_transparent; }
	bool isTranscendent() const { return m_transcendent; }

	StateManager* getStateManager() { return m_stateManager; }

protected:
	sf::Font m_font;

	StateManager* m_stateManager;
	bool m_transcendent;
	bool m_transparent;
};