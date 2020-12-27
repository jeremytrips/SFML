#include "StatePaused.h"

StatePaused::StatePaused(StateManager* stateManager)
	:BaseState(stateManager)
{
}

StatePaused::~StatePaused()
{
}

void StatePaused::onCreate()
{
	printf("In state paused");
	//setTransparent(true); // Set our transparency flag.
	m_font.loadFromFile("assets/font/intro_font.ttf");
	m_text.setFont(m_font);
	m_text.setString(sf::String("PAUSED"));
	m_text.setCharacterSize(14);
	m_text.setStyle(sf::Text::Bold);

	sf::Vector2u windowSize = m_stateManager->getContext()->m_window->getRenderWindow()->getSize();

	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	m_rect.setSize(sf::Vector2f(windowSize));
	m_rect.setPosition(0, 0);
	m_rect.setFillColor(sf::Color(0, 0, 0, 150));

	EventManager* evMgr = m_stateManager->getContext()->m_eventManager;
	evMgr->addCallback(StateType::Paused, "KeyP", &StatePaused::unpause, this);
}

void StatePaused::onDestroy()
{
	EventManager* evMgr = m_stateManager->getContext()->m_eventManager;
	evMgr->removeCallback(StateType::Paused, "KeyP");
}

void StatePaused::activate()
{
}

void StatePaused::deActivate()
{
}

void StatePaused::update(const sf::Time& time)
{
	m_stateManager->switchTo(StateType::Game);
}

void StatePaused::draw()
{
	printf("Drawing paused");
	sf::RenderWindow* wind = m_stateManager->getContext()->m_window->getRenderWindow();
	wind->draw(m_rect);
	wind->draw(m_text);
}

void StatePaused::unpause(EventDetails* details)
{
}
