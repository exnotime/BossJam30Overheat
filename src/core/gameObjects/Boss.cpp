#include "Boss.h"
#include "level/Level.h"
const int Boss::m_RunningAnimation[8] = { 0, 1, 3, 1, 0, 3, 4, 3 };
const int Boss::m_WalkAnimation[4] = { 0, 1, 0, 2 };

Boss::Boss(){
	m_Origin = glm::vec2(131, 84);
	m_Rotation = 0.0f;
	m_Direction = glm::vec2(1, 0);
	m_Sprite.setTextureRect(sf::IntRect(0, 0, 262, 168));
	m_HP = 100.0f;
}


Boss::~Boss(){

}

void Boss::Draw(sf::RenderWindow* window) {
	GameObject::Draw(window);
}

void Boss::Update(float dt){
	m_Direction = m_Goal - m_Position;
	m_Direction = glm::normalize(m_Direction);
	m_Origin = glm::vec2(60, 50);

	m_Position += m_MovementSpeed * m_Direction * dt;
	//look in the direction we are going
	m_Rotation = (atan2f(m_Direction.y, m_Direction.x) * 180.0f / 3.14f) + 90.0f; //adjust for sprite
	//animate
	if (m_Walking){
		m_AnimationTimer += dt * 10.0f;
		int frame = (int)m_AnimationTimer;
		m_Sprite.setTextureRect(sf::IntRect(262 * (m_WalkAnimation[frame % 4]), 0, 262, 168));
	}
	else{
		/*m_AnimationTimer += dt * 20.0f;
		int frame = (int)m_AnimationTimer;
		m_Sprite.setTextureRect(sf::IntRect(120 * (m_RunningAnimation[frame % 8]), 0, 120, 100));
	*/}

	GameObject::Update(dt);
}

void Boss::SetGoal(glm::vec2 goal){
	m_Goal = goal;
}

void Boss::TakeDamage(float damage){
	m_HP -= damage;
	if (m_HP <= 0.0f){
		m_Dead = true;
	}
}

void Boss::UpdatePOI(Level& level){
	//if (glm::distance(m_Goal, m_Position) < 0.01f){
	//	m_Position = m_Goal;
	//	glm::vec2 newGoal = level.GetClosestPOI(m_Position, m_Goal, m_OldGoal);
	//	m_OldGoal = m_Goal;
	//	m_Goal = newGoal;
	//}
}