#include "EventManager.h"

EventManager::EventManager()
	:m_hasFocus(true)
{
	loadBindings();
}

EventManager::~EventManager()
{
	for (auto& itr : m_bindings) {
		delete itr.second;
		itr.second = nullptr;
	}
}

bool EventManager::addBindings(Binding* binding)
{
	if (m_bindings.find(binding->m_name) != m_bindings.end())
		return false;

	return m_bindings.emplace(binding->m_name, binding).second;
}

bool EventManager::removeBindings(std::string name)
{
	auto itr = m_bindings.find(name);
	if (itr == m_bindings.end())
		return false;
	delete itr->second;
	m_bindings.erase(itr);
	return true;
}

void EventManager::setFocus(const bool& focus)
{
	m_hasFocus = focus;
}

void EventManager::handleEvent(sf::Event& l_event)
{
	std::cout << l_event.type << std::endl;
	for (auto& b_itr : m_bindings) {
		// Binding are obviously the stuff create in .cfg (for the moment)
		Binding* bind = b_itr.second;
		std::cout << "" << std::endl;
		for (auto& e_itr : bind->m_events) {
			EventType sfmlEvent = (EventType)l_event.type;
			if (e_itr.first != sfmlEvent) {
				std::cout << "event do not match " << std::endl;
				continue; 
			}
			if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp) {
				std::cout << "Key event" << std::endl;
				std::cout << "key = " << l_event.key.code << std::endl;
				if (e_itr.second.m_code == l_event.key.code) {
					// Matching event/keystroke.
					// Increase count.
					if (bind->m_details.m_keyCode != -1) {
						bind->m_details.m_keyCode = e_itr.second.m_code;
					}
					++(bind->c);
					break;
				}
			}
			else if (sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp) {
				std::cout << "Mouse event" << std::endl;
				if (e_itr.second.m_code == l_event.mouseButton.button) {
					// Matching event/keystroke.
					// Increase count.
					bind->m_details.m_mouse.x = l_event.mouseButton.x;
					bind->m_details.m_mouse.y = l_event.mouseButton.y;
					if (bind->m_details.m_keyCode != -1) {
						bind->m_details.m_keyCode = e_itr.second.m_code;
					}
					++(bind->c);
					break;
				}
			}
			else {
				// No need for additional checking.
				if (sfmlEvent == EventType::MouseWheel) {
					bind->m_details.m_mouseWheelDelta = l_event.mouseWheel.delta;
				}
				else if (sfmlEvent == EventType::WindowResized) {
					std::cout << "Window resize event" << std::endl;
					bind->m_details.m_size.x = l_event.size.width;
					bind->m_details.m_size.y = l_event.size.height;
				}
				else if (sfmlEvent == EventType::TextEntered) {
					std::cout << "TextEntered event" << std::endl;
					bind->m_details.m_textEntered = l_event.text.unicode;
				}
				++(bind->c);
			}
		}
	}
}

void EventManager::update()
{
	if (!m_hasFocus)
		return;
	for (auto &b_itr : m_bindings) {
		Binding* bind = b_itr.second;
		for (auto &e_itr: bind->m_events) {
			switch (e_itr.first)
			{
			case EventType::keyboard:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(e_itr.second.m_code))) {
					if (bind->m_details.m_keyCode!= 1) {
						bind->m_details.m_keyCode = e_itr.second.m_code;
					}
					++(bind->c);
				}
				break;
			case (EventType::Mouse):
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button(e_itr.second.m_code))) {
					if(bind->m_details.m_keyCode != -1){
						bind->m_details.m_keyCode == e_itr.second.m_code;
					}
					++(bind->c);
				}
				break;
			case(EventType::Joystick):
				// bite
				break;
			}
		}
		if (bind->m_events.size() == bind->c) {
			auto callitr = m_callbacks.find(bind->m_name);
			if (callitr != m_callbacks.end()) {
				callitr->second(&bind->m_details);
			}
		}
			bind->c = 0;
			bind->m_details.clear();
	}
}

void EventManager::ShowBindings()
{
	for (auto& iter : m_bindings)
	{
		std::cout << iter.first.c_str() << "|" << iter.second->m_details.m_keyCode << "|" << iter.second->c << std::endl;
	}
}


void EventManager::loadBindings()
{
	std::string delimiter = ":";
	std::ifstream bindings;
	bindings.open("config.cfg.txt");
	if (!bindings.is_open()) { std::cout << "! Failed loading keys.cfg." << std::endl; return; }
	std::string line;
	while (std::getline(bindings, line)) {
		std::stringstream keystream(line);
		std::string callbackName;
		keystream >> callbackName;
		Binding* bind = new Binding(callbackName);
		while (!keystream.eof()) {
			std::string keyval;
			keystream >> keyval;
			int start = 0;
			int end = keyval.find(delimiter);
			if (end == std::string::npos) { delete bind; bind = nullptr; break; }
			EventType type = EventType(stoi(keyval.substr(start, end - start)));
			std::cout << stoi(keyval.substr(start, end - start)) << std::endl;
			int code = stoi(keyval.substr(end + delimiter.length(), keyval.find(delimiter, end + delimiter.length())));
			EventInfo eventInfo(stoi(keyval.substr(end + delimiter.length(), keyval.find(delimiter, end + delimiter.length()))));
			std::cout << "event code " << code <<std::endl;

			bind->bindEvent(type, eventInfo);
		}

		if (!addBindings(bind)) { delete bind; }
		bind = nullptr;
	}
	bindings.close();
}
