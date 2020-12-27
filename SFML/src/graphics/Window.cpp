#include "Window.h"

Window::Window() {
	setup("Window", sf::Vector2u(720, 480));
}

Window::Window(const std::string& title, const sf::Vector2u& size) {
	setup(title, size);
}

Window::~Window() { 
	m_window.close();
}

void Window::setup(const std::string& title, const sf::Vector2u& size)
{
	m_isFocused = true;
	m_windowTitle = title;
	m_windowSize = size;
	m_isDone = false;
	m_isFullScreen = false;
	m_eventManager.addCallback(StateType(0), "WindowClose", &Window::close, this);
	m_eventManager.addCallback(StateType(0), "FullscreenToggle", &Window::toggleFullscreen, this);
	create();
}

void Window::create() {
	sf::Uint32 style = sf::Style::Default;
	if (m_isFullScreen) { 
		style = sf::Style::Fullscreen; 
	}

	m_window.create(sf::VideoMode(m_windowSize.x, m_windowSize.y, 32), m_windowTitle, style);
}

void Window::beginDraw() {
	m_window.clear(sf::Color::Black); 
}
void Window::endDraw(){
	m_window.display();
}
void Window::update(){
	sf::Event event;
	while (m_window.pollEvent(event)) {
		
		if (event.type == sf::Event::LostFocus) { 
			m_isFocused = true; 
			m_eventManager.setFocus(true); 
		}
		else if (event.type == sf::Event::GainedFocus) { 
			m_isFocused = true;
			m_eventManager.setFocus(true); 
		}

		m_eventManager.handleEvent(event);
	}
	m_eventManager.update();
}

bool Window::isDone() { return m_isDone; }
bool Window::isFullscreen() { return m_isFullScreen; }
bool Window::isFocused() { return m_isFocused; }


void Window::toggleFullscreen(EventDetails* l_details) {
	m_isFullScreen = !m_isFullScreen;
	m_window.close();
	create();
}

void Window::close(EventDetails* l_details){
	m_isDone = true;
}


