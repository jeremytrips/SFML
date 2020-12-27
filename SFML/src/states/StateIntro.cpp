#include "StateIntro.h"
#include "../Manager/StateManager.h"




StateIntro::StateIntro(StateManager* stateManager)
	:BaseState(stateManager) {
	m_timePassed = 0;
}

StateIntro::~StateIntro()
{
}

void StateIntro::onCreate()
{
	m_timePassed = 0.0f;
	sf::Vector2u wSize = m_stateManager->getContext()->m_window->getWindowSize();

	m_introTexture.loadFromFile("assets/intro.png");
	m_introSprite.setTexture(m_introTexture);
	m_introSprite.setOrigin(m_introTexture.getSize().x / 2.0f, m_introTexture.getSize().y / 2.0f);
	m_introSprite.setPosition(wSize.x / 2.0f, wSize.y / 2.0f);

	m_font.loadFromFile("assets/font/intro_font.ttf");
	m_introText.setFont(m_font);
	m_introText.setString("PRESS SPACE TO CONTINUE");
	m_introText.setCharacterSize(45);
	sf::FloatRect textRect = m_introText.getLocalBounds();
	
	m_introText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_introText.setPosition(wSize.x / 2.0f, wSize.y / 2.0f);

	EventManager* eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->addCallback(StateType::Intro, "IntroContinue", &StateIntro::Continue, this);

}

void StateIntro::onDestroy()
{
	EventManager* eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->removeCallback(StateType::Intro, "IntroContinue");
}

void StateIntro::activate()
{
}

void StateIntro::deActivate()
{
}

void StateIntro::update(const sf::Time& l_time)
{
	if (m_timePassed < 5.0f) { // Less than five seconds.
		m_timePassed += l_time.asSeconds();
		m_introSprite.setPosition(
			m_introSprite.getPosition().x,
			m_introSprite.getPosition().y + (48 * l_time.asSeconds()));
	}
}

void StateIntro::draw()
{
	sf::RenderWindow* window = m_stateManager->getContext()->m_window->getRenderWindow();

	window->draw(m_introSprite);
	if (m_timePassed >= 5.0f) {
		window->draw(m_introText);
	}
}

void StateIntro::Continue(EventDetails* details)
{
	if (m_timePassed >= 5.0f) {
		m_stateManager->switchTo(StateType::MainMenu);
		m_stateManager->remove(StateType::Intro);
	}
}

