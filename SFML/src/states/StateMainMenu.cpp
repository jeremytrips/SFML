#include "StateMainMenu.h"
#include "../Manager/StateManager.h"


StateMainMenu::StateMainMenu(StateManager* stateManager)
	:BaseState(stateManager)
{}

StateMainMenu::~StateMainMenu()
{
}

void StateMainMenu::onCreate()
{
	m_font.loadFromFile("assets/font/intro_font.ttf");
	m_text.setFont(m_font);
	m_text.setString(sf::String("MAIN MENU:"));
	m_text.setCharacterSize(18);

	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);

	m_text.setPosition(400, 100);

	m_buttonSize = sf::Vector2f(300.0f, 32.0f);
	m_buttonPos = sf::Vector2f(400, 200);
	m_buttonPadding = 4; // 4px.

	std::string str[3];
	str[0] = "PLAY";
	str[1] = "CREDITS";
	str[2] = "EXIT";

	for (int i = 0; i < 3; ++i) {
		sf::Vector2f buttonPosition(m_buttonPos.x, m_buttonPos.y +
			(i * (m_buttonSize.y + m_buttonPadding)));
		m_rects[i].setSize(m_buttonSize);
		m_rects[i].setFillColor(sf::Color::Red);

		m_rects[i].setOrigin(m_buttonSize.x / 2.0f, m_buttonSize.y / 2.0f);
		m_rects[i].setPosition(buttonPosition);

		m_labels[i].setFont(m_font);
		m_labels[i].setString(sf::String(str[i]));
		m_labels[i].setCharacterSize(12);

		sf::FloatRect rect = m_labels[i].getLocalBounds();
		m_labels[i].setOrigin(rect.left + rect.width / 2.0f,
			rect.top + rect.height / 2.0f);

		m_labels[i].setPosition(buttonPosition);
	}

	EventManager* eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->addCallback(StateType::MainMenu, "MouseLeft", &StateMainMenu::mouseClick, this);
}

void StateMainMenu::onDestroy()
{
	EventManager* evMgr = m_stateManager->getContext()->m_eventManager;
	evMgr->removeCallback(StateType::MainMenu, "Mouse_Left");
}

void StateMainMenu::activate()
{
	if (m_stateManager->hasState(StateType::Game) && m_labels[0].getString() == "PLAY")
	{
		m_labels[0].setString(sf::String("RESUME"));
		sf::FloatRect rect = m_labels[0].getLocalBounds();
		m_labels[0].setOrigin(rect.left + rect.width / 2.0f,
			rect.top + rect.height / 2.0f);
	}
}

void StateMainMenu::deActivate()
{
}

void StateMainMenu::update(const sf::Time& time)
{

}

void StateMainMenu::draw()
{
	sf::RenderWindow* window = m_stateManager->getContext()->m_window->getRenderWindow();
	window->draw(m_text);
	for (int i = 0; i < 3; ++i) {
		window->draw(m_rects[i]);
		window->draw(m_labels[i]);
	}
}

void StateMainMenu::mouseClick(EventDetails* details)
{
	printf("%i, %i", details->m_mouse.x, details->m_mouse.y);
	sf::Vector2i mousePos = details->m_mouse;

	float halfX = m_buttonSize.x / 2.0f;
	float halfY = m_buttonSize.y / 2.0f;
	for (int i = 0; i < 3; ++i) {
		if (mousePos.x >= m_rects[i].getPosition().x - halfX &&
			mousePos.x <= m_rects[i].getPosition().x + halfX &&
			mousePos.y >= m_rects[i].getPosition().y - halfY &&
			mousePos.y <= m_rects[i].getPosition().y + halfY)
		{
			if (i == 0) {
				m_stateManager->switchTo(StateType::Game);
			}
			else if (i == 1) {
				// Credits state.
			}
			else if (i == 2) {
				m_stateManager->getContext()->m_window->close();
			}
		}
	}
}
