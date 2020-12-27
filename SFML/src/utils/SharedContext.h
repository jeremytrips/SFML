#pragma once

class Window;
class EventManager;

struct SharedContext {
	SharedContext() : m_window(nullptr), m_eventManager(nullptr) {}

	Window* m_window;
	EventManager* m_eventManager;
};