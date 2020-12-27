#include "Game.h"


Game::Game() : 
	m_window("Chapter 4", sf::Vector2u(800, 600)), m_stateManager(&m_sharedContext){
	m_sharedContext.m_window = &m_window;
	m_sharedContext.m_eventManager = m_window.getEventManager();
	m_stateManager.switchTo(StateType::Intro);

	m_clock.restart();
	srand(time(nullptr));
}

Game::~Game() {}

sf::Time Game::getElapsed() { return m_clock.getElapsedTime(); }
void Game::restartClock() { m_elapsed = m_clock.restart(); }
Window* Game::getWindow() { return &m_window; }

void Game::update() {
	m_window.update();
	m_stateManager.update(m_elapsed);
}

void Game::render() {
	m_window.beginDraw();
	// Render here.
	m_stateManager.draw();
	m_window.endDraw();
}

void Game::lateUpdate() {
	m_stateManager.processRequest();
	restartClock();
}