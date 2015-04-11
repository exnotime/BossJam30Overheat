#include "Player.h"
#include "../input/GlobalMouse.h"
#include "Camera.h"

Player::Player() {
	m_Origin = glm::vec2(90, 160);
	m_Position = glm::vec2(400);
	m_Damage = 0.0f;
	m_Texture.loadFromFile("asset/TigerCharacter.png");
	m_Texture.setSmooth(true); //turn on aa
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setTextureRect(sf::IntRect(0, 0, 120, 450));
	m_MaulTimer = 0.0f;
	m_PounceTimer = 0.0f;
	m_HP = 100.0f;
	m_Mauling = false;
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

	CheckAttack(dt);
}


void Player::CheckAttack(float dt){
	sf::Mouse mouse;

	if (mouse.isButtonPressed(mouse.Left)){
		Maul();
	}
	else if(mouse.isButtonPressed(mouse.Right)){
		Pounce();
	}

	if (m_MaulTimer != 3.0f){
		m_Mauling = false;
	}
	if (m_MaulTimer > 0.0f){
		m_MaulTimer -= dt;
	}
	if (m_PounceTimer > 0.0f){
		m_PounceTimer -= dt;
	}

	if (m_MaulTimer <= 0.0f && m_PounceTimer <= 0.0f){
		m_Sprite.setTextureRect(sf::IntRect(0, 0, 120, 450));
	}
}

void Player::Maul(){
	if (m_MaulTimer <= 0.0f){
		m_Sprite.setTextureRect(sf::IntRect(120, 0, 120, 450));
		m_MaulTimer = 3.0f;
		m_Mauling = true;
	}
}

void Player::Pounce(){
	m_Sprite.setTextureRect(sf::IntRect(240, 0, 120, 450));
	m_PounceTimer = 2.0f;
}

sf::FloatRect Player::GetBoundingBoxMaul(){
	sf::FloatRect rect, temp;
	temp = m_Sprite.getGlobalBounds();
	rect = sf::FloatRect(temp.left, temp.top + 1, 120, 50);
	return temp;
}

sf::FloatRect Player::GetBoundingBoxPounce(){
	sf::FloatRect rect, temp;
	temp = m_Sprite.getGlobalBounds();
	rect = sf::FloatRect(temp.left, temp.top + 100, 120, 50);
	return temp;
}

float Player::GetDamage(){
	if (m_Mauling){
		m_Damage = 50.0f;
	}
	if (m_Pouncing){
		m_Damage = 100.0f;
	}
	return m_Damage;
}

bool Player::GetMauling(){
	return m_Mauling;
}
