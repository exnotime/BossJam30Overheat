#include "Boss.h"
#include "level/Level.h"
#include "../pathfinding/AStar.h"

const int Boss::m_RunningAnimation[8] = { 0, 1, 3, 1, 0, 3, 4, 3 };
const int Boss::m_WalkAnimation[4] = { 0, 1, 0, 2 };

Boss::Boss(){
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
	m_Origin = glm::vec2(131, 84);

	m_Direction = m_Goal - m_Position;
	if ( glm::length( m_Direction ) > m_MovementSpeed * dt ) {
		m_Direction = glm::normalize(m_Direction);
		m_Origin = glm::vec2(60, 50);

		m_Position += m_MovementSpeed * m_Direction * dt;
		//look in the direction we are going
		m_Rotation = (atan2f(m_Direction.y, m_Direction.x) * 180.0f / 3.14f) + 90.0f; //adjust for sprite
	} else {
		m_Position = m_Goal;
		if ( !m_Path.empty() ) {
			m_Path.pop_back();
			if ( !m_Path.empty() ) {
				m_Goal = m_Path.back();
				m_Goal += glm::vec2( 0.5f );
			}
		}
	}
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

void Boss::UpdatePOI(Level& level, const glm::vec2& targetPosition, float deltaTime ){
	static AStar aStar;
	static float timer = 0.0f;
	static bool visionPrev = false;
	timer -= deltaTime;

	bool vision = true;
	glm::vec2 testpos;
	int nSamples = 1000;
	float maxDist = glm::min( 100.0f, glm::length( targetPosition - m_Position ) );
	int prevX(-1), prevY(-1);
	glm::vec2 normDir = glm::normalize(targetPosition - m_Position);
	for (int i = 0; i < nSamples; i++){
		float dist = (i / (float)nSamples) * maxDist;
		testpos = m_Position + normDir * dist;
		if ( prevX != (int)testpos.x || prevY != (int)testpos.y ) {
			prevX = (int)testpos.x;
			prevY = (int)testpos.y;
			if ( level.IsTileBlocked(prevX, prevY)){
				vision = false;
				continue;
			}
		}
	}
	if ( vision ) {
		m_Goal = targetPosition;
	} else if ( visionPrev || m_Path.empty() || timer <= 0.0f ) {
		timer = 5.0f;
		m_Path = aStar.findPath( level, glm::ivec2(m_Position), glm::ivec2(targetPosition) );
		if ( !m_Path.empty() ) {
			m_Goal = m_Path[ m_Path.size() - 1 ];
			m_Goal += glm::vec2( 0.5f );
		}
	}
	visionPrev = vision;
}