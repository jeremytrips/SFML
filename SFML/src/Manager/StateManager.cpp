#include "StateManager.h"
#include "../states/StateIntro.h"
#include "../states/StateMainMenu.h"
#include "../states/StateGame.h"
#include "../states/StatePaused.h"

StateManager::StateManager(SharedContext* sharedContext)
	: m_sharedContext(sharedContext)
{
	registerState<StateIntro>(StateType::Intro);
	registerState<StateMainMenu>(StateType::MainMenu);
	registerState<StateGame>(StateType::Game);
	registerState<StatePaused>(StateType::Paused);
}

StateManager::~StateManager()
{
	for (auto &state : m_states) {
		state.second->onDestroy();
		delete state.second;
	}
}

void StateManager::update(const sf::Time& time)
{
	if (m_states.empty())
		return;
	if (m_states.back().second->isTranscendent() && m_states.size() > 1) {
		// There's a kind of hierarchy in the states. Starting from the top of the queue
		// We check if previous states needs to be rendered if it need it we check the 
		// previous one until one dont need. 
		// It means that if we have : need, need, dont need, need situation
		// only the two first will be rendered
		auto itr = m_states.end();
		while (itr != m_states.begin()) {
			if (itr != m_states.end()) {
				if (!itr->second->isTranscendent())
					break;
			}
			--itr;
		}
		for (; itr != m_states.end(); ++itr)
			itr->second->update(time);
	}
	else {
		m_states.back().second->update(time);
	}

}

void StateManager::draw()
{
	if (m_states.empty())
		return;
	// Transparency useless if size equal 1 as we see if it's needed to render more than one state
	if (m_states.back().second->isTransparent() && m_states.size() > 1) {
		// There's a kind of hierarchy in the states. Starting from the top of the queue
		// We check if previous states needs to be rendered if it need it we check the 
		// previous one until one dont need. 
		// It means that if we have : need, need, dont need, need situation
		// only the two first will be rendered
		auto itr = m_states.end();
		while (itr != m_states.begin()) {
			if (itr != m_states.end()) {
				if (!itr->second->isTransparent())
					break;
			}
			--itr;
		}
		for (; itr != m_states.end(); ++itr)
			itr->second->draw();
	}
	else {
		m_states.back().second->draw();
	}
}

bool StateManager::hasState(const StateType& type)
{
	for (auto s_itr = m_states.begin(); s_itr != m_states.end(); ++s_itr) {
		if (s_itr->first == type) {
			auto removed = std::find(m_toRemove.begin(), m_toRemove.end(), type);
			if (removed == m_toRemove.end())
				return true;
			return false;
		}
	}
	return false;
}

void StateManager::processRequest()
{
	while(m_toRemove.begin() != m_toRemove.end()){
		RemoveState(*m_toRemove.begin());
		m_toRemove.erase(m_toRemove.begin());
	}
}

void StateManager::switchTo(const StateType& type)
{
	m_sharedContext->m_eventManager->setCurrentState(type);
	for (auto s_itr = m_states.begin(); s_itr != m_states.end(); s_itr++) {
		if (s_itr->first == type) {
			m_states.back().second->deActivate();
			StateType tmpType = s_itr->first;
			BaseState* tmpState = s_itr->second;
			m_states.erase(s_itr);
			m_states.emplace_back(tmpType, tmpState);
			tmpState->activate();
			return;
		}
	}
	if (!m_states.empty()) {
		m_states.back().second->deActivate();
	}
	createState(type);
	m_states.back().second->activate();
}

void StateManager::remove(const StateType& type)
{
	m_toRemove.push_back(type);
}

void StateManager::createState(const StateType& type)
{
	auto newState = m_stateFactory.find(type);
	if (newState == m_stateFactory.end())
		return;
	BaseState* state = newState->second();
	m_states.emplace_back(type, state);
	state->onCreate();
}

void StateManager::RemoveState(const StateType& type)
{
	for (auto s_itr = m_states.begin(); s_itr != m_states.end(); s_itr++) {
		if (s_itr->first == type) {
			s_itr->second->onDestroy();
			delete s_itr->second;
			m_states.erase(s_itr);
			return;
		}
	}
}
