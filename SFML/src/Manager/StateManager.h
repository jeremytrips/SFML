#pragma once

#include <vector>
#include <unordered_map>
#include <functional>

#include "EventManager.h"
#include "../graphics/Window.h"
#include "../states/BaseState.h"
#include "../states/StateIntro.h"
#include "../utils/SharedContext.h"

enum class StateType {
	Intro = 1,
	MainMenu,
	Game,
	Paused, 
	GameOver, 
	Credits
};

using StateContainer = std::vector<std::pair<StateType, BaseState*>>;
using TypeContainer = std::vector<StateType>;

using StateFactory = std::unordered_map<StateType, std::function<BaseState* (void)>>;

class StateManager {
public:
	StateManager(SharedContext* sharedContext);
	~StateManager();

	void update(const sf::Time& time);
	void draw();

	bool hasState(const StateType& type);

	void processRequest();
	SharedContext* getContext() { return m_sharedContext; }

	void switchTo(const StateType& type);
	void remove(const StateType& type);

private:
	void createState(const StateType& type);
	void RemoveState(const StateType& type);

	template<class T>
	void registerState(const StateType& type) {
		m_stateFactory[type] = [this]()->BaseState*
		{
			return new T(this);
		};
	}

	SharedContext* m_sharedContext;
	StateContainer m_states;
	TypeContainer m_toRemove;			// Store the state that we want to remove to avoid errors in transitions
	StateFactory m_stateFactory;
};