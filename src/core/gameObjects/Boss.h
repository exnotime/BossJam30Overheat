#pragma once
#include "GameObject.h"
#include <SFML/System.hpp>
class Level;
class Boss :
	public GameObject
{
public:
	Boss();
	~Boss();
	void Draw(sf::RenderWindow* window) override;
	void Update(float dt) override;
	void TakeDamage(float damage) override;
	void SetGoal(glm::vec2 goal);

	void UpdatePOI(Level& level, const glm::vec2& targetPosition, float deltaTime);

private:
	float m_MovementSpeed = 2.0f;

	void Shot();
	bool BulletHit(sf::FloatRect playerRect);
private:

	float m_AnimationTimer = 0.0f;
	glm::vec2 m_Goal;
	glm::vec2 m_OldGoal;

	const float m_ShootingTimerMax = 0.1;
	float m_ShootingTimer;
	bool m_Shot = false;
	bool m_Shooting = false;
	bool m_Walking = true;
	static const int m_RunningAnimation[];
	static const int m_WalkAnimation[];
	float m_HP;
	std::vector<glm::ivec2>	m_Path;
	float m_TimerInvinsible;
	const float m_TimerInvinsibleMaxTime = 0.3f;
	sf::Texture	m_TextureProjectile;
	std::vector<GameObject> m_Projectiles;
};