#include "Player.h"
#include "../input/GlobalMouse.h"
#include "Camera.h"

Player::Player() {
	m_Origin = glm::vec2(32);
	m_Position = glm::vec2(400);
}


Player::~Player() {

}


void Player::Update(float dt) {


	glm::vec2 aim = glm::vec2(g_Mouse.Position().x, g_Mouse.Position().y) / glm::vec2(1280, 720);
	aim = aim * 2.0f - 1.0f;
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

	g_Camera.SetPosition(m_Position);
	GameObject::Update(dt); //will update the sprite
}

glm::vec2& Player::GetPosition(){
	return m_Position;
}