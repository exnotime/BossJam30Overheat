#include "Enemy.h"


Enemy::Enemy(){
	m_Origin = glm::vec2(60, 30);
	m_Rotation = 0.0f;
	m_Direction = glm::vec2(1, 0);
	m_Eaten = false;
	m_HP = 100.0f;
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
	//look in the direction we are going
	m_Rotation = (atan2f(m_Direction.y,m_Direction.x) * 180.0f / 3.14f) + 90.0f; //adjust for sprite
	GameObject::Update(dt);
}

void Enemy::SetEaten(bool eaten)
{
	m_Eaten = eaten;
}