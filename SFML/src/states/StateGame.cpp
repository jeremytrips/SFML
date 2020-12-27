#include "StateGame.h"

StateGame::StateGame(StateManager* stateManager)
	:BaseState(stateManager)
{}

StateGame::~StateGame()
{
}

void StateGame::onCreate()
{
	m_texture.loadFromFile("Mushroom.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(0, 0);
	m_increment = sf::Vector2f(400.0f, 400.0f);

	EventManager* eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->addCallback(StateType::Game, "KeyEsc", &StateGame::mainMenu, this);
	eventManager->addCallback(StateType::Game, "KeyP", &StateGame::pause, this);
}

void StateGame::onDestroy()
{
	EventManager* eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->removeCallback(StateType::Game, "KeyEsc");
	eventManager->removeCallback(StateType::Game, "KeyP");
}

void StateGame::activate()
{
}

void StateGame::deActivate()
{
}

void StateGame::update(const sf::Time& time)
{
	sf::Vector2u l_windSize = m_stateManager->getContext()->m_window->getWindowSize();
	sf::Vector2u l_textSize = m_texture.getSize();

	if ((m_sprite.getPosition().x > l_windSize.x - l_textSize.x && m_increment.x > 0) ||
		(m_sprite.getPosition().x < 0 && m_increment.x < 0))
	{
		m_increment.x = -m_increment.x;
	}

	if ((m_sprite.getPosition().y > l_windSize.y - l_textSize.y && m_increment.y > 0) ||
		(m_sprite.getPosition().y < 0 && m_increment.y < 0))
	{
		m_increment.y = -m_increment.y;
	}

	m_sprite.setPosition(m_sprite.getPosition().x + (m_increment.x * time.asSeconds()),
		m_sprite.getPosition().y + (m_increment.y * time.asSeconds()));
}

void StateGame::draw()
{
	m_stateManager->getContext()->m_window->getRenderWindow()->draw(m_sprite);
}

void StateGame::mainMenu(EventDetails* details)
{
	m_stateManager->switchTo(StateType::MainMenu);
}

void StateGame::pause(EventDetails* details)
{
	m_stateManager->switchTo(StateType::Paused);
}
