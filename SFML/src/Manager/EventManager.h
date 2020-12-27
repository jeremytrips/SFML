#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <sstream>
#include <iostream>

enum class StateType;

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
	Keyboard = sf::Event::Count + 1, Mouse, Joystick
};

// Store as it says the event info.
// Event may be binded to a key and so it is stored in m_code
// Some event do not requiers key so it is stored as 0.
struct EventInfo {
	EventInfo() { m_code = 0; }
	EventInfo(int code):m_code(code) {}
	union {
		int m_code;
	};
};

// Arguments that get passed to each callbacks
// Contains the details of the events
struct EventDetails {
	EventDetails(const std::string& bindName)
		: m_name(bindName) {
		clear();
	}
	std::string m_name;

	sf::Vector2i m_size;
	sf::Uint32 m_textEntered;
	sf::Vector2i m_mouse;
	int m_mouseWheelDelta;
	int m_keyCode; // Single key code.

	void clear() {
		m_size = sf::Vector2i(0, 0);
		m_textEntered = 0;
		m_mouse = sf::Vector2i(0, 0);
		m_mouseWheelDelta = 0;
		m_keyCode = -1;
	}
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

// Hold the event information 
struct Binding {
	Binding(const std::string& name) : m_name(name), m_details(name), c(0) {}
	void bindEvent(EventType type, EventInfo info = EventInfo()) {
		m_events.emplace_back(type, info);
	}

	Events m_events;
	std::string m_name;
	int c; // Count of events that are "happening".

	EventDetails m_details;
};

using Bindings = std::unordered_map<std::string, Binding*>;
using CallbackContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;
using Callbacks = std::unordered_map<StateType, CallbackContainer>;

class EventManager {
public:
	EventManager();
	~EventManager();

	bool addBinding(Binding* binding);
	bool removeBinding(std::string name);

	void setFocus(const bool& focus);
	void setCurrentState(StateType state) { m_currentState = state; }

	// Needs to be defined in the header!
	template<class T>
	bool addCallback(StateType state, const std::string& name, void(T::* func)(EventDetails*), T* instance)
	{
		auto itr = m_callbacks.emplace(state, CallbackContainer()).first;
		auto temp = std::bind(func, instance, std::placeholders::_1);

		return itr->second.emplace(name, temp).second;
	}

	bool removeCallback(StateType state, const std::string& name) {
		auto s_itr = m_callbacks.find(state);
		if (s_itr == m_callbacks.end())
			return false;
		auto e_itr = s_itr->second.find(name);
		if (e_itr == s_itr->second.end())
			return false;
		s_itr->second.erase(name);
		return true;

	}

	void handleEvent(sf::Event& l_event);
	void update();

	sf::Vector2i getMousePos(sf::RenderWindow* l_wind = nullptr) {
		return (l_wind ? sf::Mouse::getPosition(*l_wind) : sf::Mouse::getPosition());
	}
private:
	void loadBindings();
	Bindings m_bindings;
	Callbacks m_callbacks;
	bool m_hasFocus;
	StateType m_currentState;
};
