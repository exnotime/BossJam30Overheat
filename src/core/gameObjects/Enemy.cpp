#include "Enemy.h"
#include "level/Level.h"
const int Enemy::m_RunningAnimation[8] = { 0, 1, 2, 1, 0, 3, 4, 3 };
const int Enemy::m_WalkAnimation[6] = { 0, 1, 1, 0, 3, 3 };

Enemy::Enemy(){
	m_Origin = glm::vec2(60, 50);
	m_Rotation = 0.0f;
	m_Direction = glm::vec2(1, 0);
	m_Sprite.setTextureRect(sf::IntRect(0, 0, 120, 100));
	m_HP = 100.0f;
}


Enemy::~Enemy(){

}

void Enemy::Draw(sf::RenderWindow* window) {
	GameObject::Draw(window);
}

void Enemy::Update(float dt){
	m_Direction = m_Goal - m_Position;
	m_Direction = glm::normalize(m_Direction);
	m_Origin = glm::vec2(60, 50);

	m_Position += m_MovementSpeed * m_Direction * dt;
	//look in the direction we are going
	m_Rotation = (atan2f(m_Direction.y,m_Direction.x) * 180.0f / 3.14f) + 90.0f; //adjust for sprite
	//animate
	if (m_Walking){
		m_AnimationTimer += dt * 10.0f;
		int frame = (int)m_AnimationTimer;
		m_Sprite.setTextureRect(sf::IntRect(120 * (m_WalkAnimation[frame % 6]), 0, 120, 100));
	}else{
		m_AnimationTimer += dt * 20.0f;
		int frame = (int)m_AnimationTimer;
		m_Sprite.setTextureRect(sf::IntRect(120 * (m_RunningAnimation[frame % 8]), 0, 120, 100));
	}

	GameObject::Update(dt);
}

void Enemy::SetAlert(bool alert){
	if (alert){
		m_Walking = false;
		m_MovementSpeed = 3.0f;
	}
	else{
		m_Walking = true;
		m_MovementSpeed = 1.0f;
	}
}

void Enemy::SetGoal(glm::vec2 goal){
	m_Goal = goal;
}

void Enemy::TakeDamage(float damage){
	m_HP -= damage;
	if (m_HP <= 0.0f){
		m_Dead = true;
	}
}

void Enemy::UpdatePOI(Level& level){
	if (glm::distance(m_Goal, m_Position) < 0.01f){
		m_Position = m_Goal;
		glm::vec2 newGoal = level.GetClosestPOI(m_Position, m_Goal, m_OldGoal);
		m_OldGoal = m_Goal;
		m_Goal = newGoal;
	}
}