#pragma once

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

#include <unordered_map>
#include <functional>
#include <vector>

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>


enum class EventType {
	KeyDown = sf::Event::KeyPressed,
	KeyUp = sf::Event::KeyReleased,
	MButtonDown = sf::Event::MouseButtonPressed,
	MButtonUp = sf::Event::MouseButtonReleased,
	MouseWheel = sf::Event::MouseWheelMoved,
	WindowResized = sf::Event::Resized,
	GainedFocus = sf::Event::GainedFocus,
	LostFocus = sf::Event::LostFocus,
	MouseEntered = sf::Event::MouseEntered,
	MouseLeft = sf::Event::MouseLeft,
	Closed = sf::Event::Closed,
	TextEntered = sf::Event::TextEntered,
	keyboard = sf::Event::Count + 1,
	Mouse,
	Joystick
};

struct EventInfo {
	EventInfo() { m_code = 0; }
	EventInfo(int event) { m_code = event; }
	union {
		int m_code;
	};
};

struct EventDetails {
	EventDetails(const std::string& bindName)
		: m_name(bindName)
	{
		clear();
	}
	std::string m_name;

	sf::Vector2i m_size;
	sf::Uint32 m_textEntered;
	sf::Vector2i m_mouse;
	int m_mouseWheelDelta;
	int m_keyCode;

	void clear() {
		m_size = sf::Vector2i(0, 0);
		m_textEntered = 0;
		m_mouse = sf::Vector2i(0, 0);
		m_mouseWheelDelta = 0;
		m_keyCode = -1;
	}
};

// unordered_map are kind of python dictionnary with unique key
/*
	for (const auto& m : unordered_map){
		m.first
		m.second
	}
*/

using Events = std::vector<std::pair<EventType, EventInfo>>;

using Callbacks = std::unordered_map< std::string, std::function<void(EventDetails*)>>;

struct Binding
{
	Binding(const std::string& name)
		: m_name(name), m_details(name), c(0) {}

	void bindEvent(EventType eventType, EventInfo eventInfo = EventInfo()) {
		m_events.emplace_back(eventType, eventInfo);
	}
	Events m_events;
	std::string m_name;
	int c;

	EventDetails m_details;

};

using Bindings = std::unordered_map<std::string, Binding*>;

class EventManager
{
public:
	EventManager();
	~EventManager();

	bool addBindings(Binding* binding);
	bool removeBindings(std::string name);

	void setFocus(const bool& focus);

	template<class T>
	bool addCallback(const std::string& name, void(T::* func)(EventDetails*), T* instance) {
		// std::bind allow one to bind an object call to one class or anything else 
		// One can pass unbinded args to func with _1, ...
		// std::placeholdes::-1 because func take one argument
		auto temp = std::bind(func, instance, std::placeholders::_1);
		// return true or false if the insertion hapoened
		return m_callbacks.emplace(name, temp).second;
	}

	void removeCallback(const std::string& name) {
		m_callbacks.erase(name);
	}

	void handleEvent(sf::Event& l_event);
	void update();
	void ShowBindings();
	sf::Vector2i getMousePos(sf::RenderWindow* window = nullptr) {
		return (window ? sf::Mouse::getPosition(*window) : sf::Mouse::getPosition());
	}

private:
	void loadBindings();
	Bindings m_bindings;
	Callbacks m_callbacks;
	bool m_hasFocus;
};

