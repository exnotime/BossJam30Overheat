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
	m_VisionDistance = 10.0f;
	m_VisionCone = cosf(0.785398163);
	m_StandingStill = rand() % 8 == 0 ? false : true;
	m_TimerInvinsible = 0.0f;
	m_VisualiseDamage = true;
}


Enemy::~Enemy(){

}

void Enemy::Draw(sf::RenderWindow* window) {
	if (m_Walking){
		//render vision cone
	}
	GameObject::Draw(window);
}

void Enemy::Update(float dt){
	m_Direction = m_Goal - m_Position;
	m_Direction = glm::normalize(m_Direction);
	m_Origin = glm::vec2(60, 50);
		m_Rotation = (atan2f(m_Direction.y,m_Direction.x) * 180.0f / 3.14f) + 90.0f; //adjust for sprite

	if ( !m_StandingStill ) {
		m_Position += m_MovementSpeed * m_Direction * dt;
		//look in the direction we are going

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
	}

	m_TimerInvinsible -= dt;
	GameObject::Update(dt);
}

void Enemy::SetAlert(bool alert){
	if (alert){
		m_StandingStill = false;
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



void Enemy::UpdatePOI(Level& level){
	m_Goal = level.GetNextGoal(m_Position);
}

float Enemy::GetVisionDist(){
	return m_VisionDistance;
}
float Enemy::GetVisionCone(){
	return m_VisionCone;
}