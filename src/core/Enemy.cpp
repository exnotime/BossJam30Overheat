#include "Enemy.h"


Enemy::Enemy(){
	m_Origin = glm::vec2(20, 20);
	m_Rotation = 0.0f;
	m_Direction = glm::vec2(100, 0);
	m_Eaten = false;
}


Enemy::~Enemy(){

}

void Enemy::Draw(sf::RenderWindow* window) {
	if (!m_Eaten){
		GameObject::Draw(window);
	}
}

void Enemy::Update(float dt){
	if (m_Eaten){
		return;
	}

	m_Direction = glm::normalize(m_Direction);

	//m_Rotation += MOVEMENT_SPEED * dt;
	m_Position += MOVEMENT_SPEED * m_Direction * dt;

	GameObject::Update(dt);
}

void Enemy::SetEaten(bool eaten)
{
	m_Eaten = eaten;
}