#include "Game.h"

Game::Game()
	:m_window()
{

}

Game::~Game()
{
}

Window* Game::getWindow()
{
	return &m_window;
}

void Game::handlInput()
{
}

void Game::update()
{
	m_window.update();
}

void Game::render()
{
	m_window.beginDraw();

	// m_window.dra( );

	m_window.endDraw();
}
