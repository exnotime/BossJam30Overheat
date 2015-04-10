#include "GlobalMouse.h"

GlobalMouse& GlobalMouse::GetInstance() {
	static GlobalMouse instance;
	return instance;
}

GlobalMouse::GlobalMouse() {
	m_LeftPressedThisFrame = false;
	m_LeftPressedPreviousFrame = false;
}

void GlobalMouse::Update(const sf::RenderWindow& window) {
	// Store previous frames state, and fetch current frames state.
	m_LeftPressedPreviousFrame = m_LeftPressedThisFrame;
	m_LeftPressedThisFrame = Mouse::isButtonPressed(Mouse::Button::Left);
	m_Position = Mouse::getPosition(window);
}

bool GlobalMouse::LeftClick() {
	return m_LeftPressedThisFrame && !m_LeftPressedPreviousFrame;
}

const Vector2i& GlobalMouse::Position() {
	return m_Position;
}