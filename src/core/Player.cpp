#include "Player.h"
#include "../input/GlobalMouse.h"
Player::Player() {
	m_Origin = glm::vec2(90, 160);
	m_Position = glm::vec2(400);
}


Player::~Player() {

}

void Player::Update(float dt) {
	glm::vec2 aim = glm::vec2(g_Mouse.Position().x, g_Mouse.Position().y) - m_Position;
	m_Rotation = (atan2f(aim.y, aim.x) + 3.14f * 0.5f) * 180.0f / 3.14f; //adjust for sprite
	sf::Keyboard kb;

	if (kb.isKeyPressed(sf::Keyboard::W)){
		m_Position.y -= MOVEMENT_SPEED * dt;
	}
	if (kb.isKeyPressed(sf::Keyboard::S)){
		m_Position.y += MOVEMENT_SPEED * dt;
	}
	if (kb.isKeyPressed(sf::Keyboard::D)){
		m_Position.x += MOVEMENT_SPEED * dt;
	}
	if (kb.isKeyPressed(sf::Keyboard::A)){
		m_Position.x -= MOVEMENT_SPEED * dt;
	}
	GameObject::Update(dt); //will update the sprite
}