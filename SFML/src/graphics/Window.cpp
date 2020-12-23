#include "Window.h"

Window::Window()
{
	setup("SFML window", sf::Vector2u(720, 480));
}

Window::Window(std::string& title, const sf::Vector2u& size)
{
	setup(title, size);
}

Window::~Window()
{
}

void Window::beginDraw()
{
	m_window.clear();
}

void Window::endDraw()
{
	m_window.display();
}

void Window::update()
{
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::LostFocus) {
			m_isFocused = false;
			m_eventManager.setFocus(false);
		}
		else if (event.type == sf::Event::GainedFocus) {
			m_isFocused = true;
			m_eventManager.setFocus(true);
		}
		else if (event.type == sf::Event::KeyPressed) {
			std::cout << "ouiouiouiouiouioui" << std::endl;
			std::cout << event.key.code << std::endl;
		}
		std::cout << event.type << std::endl;
		//m_eventManager.handleEvent(event);
	}
	m_eventManager.update();
}

bool Window::isDone()
{
	return m_isDone;
}

bool Window::isFullScreen()
{
	return m_isFullScreen;
}

sf::Vector2u Window::getWindowSize()
{
	return m_windowSize;
}

void Window::toggleFullScreen(EventDetails* details)
{
	std::cout << "toggle fullscren" << std::endl;
	std::cout << details->m_name << std::endl;
	std::cout << details->m_keyCode << std::endl;
	m_isFullScreen = !m_isFullScreen;
	destroy();
	create();
}

void Window::close(EventDetails* details)
{
	std::cout << "close" << std::endl;
	std::cout << details->m_name << std::endl;
	std::cout << details->m_keyCode << std::endl;
	m_isDone = true;
}

void Window::draw(sf::Drawable& drawable)
{
	m_window.draw(drawable);
}

void Window::setup(const std::string& title, const sf::Vector2u& size)
{
	m_isFocused = true;
	m_windowTitle = title;
	m_windowSize = size;
	m_isDone = false;
	m_isFullScreen = false;
	m_eventManager.addCallback("Window_close", &Window::close, this);
	m_eventManager.addCallback("FullscreenToggle", &Window::toggleFullScreen, this);
	create();
}

void Window::destroy()
{
	m_window.close();
}

void Window::create()
{
	auto type = m_isFullScreen ? sf::Style::Fullscreen : sf::Style::Default;
	m_window.create({ m_windowSize.x, m_windowSize.y, 32 }, m_windowTitle, type);
}
