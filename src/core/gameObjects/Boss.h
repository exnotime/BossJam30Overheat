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
	void TakeDamage(float damage);
	void SetGoal(glm::vec2 goal);
private:
	float m_MovementSpeed = 1.0f;
	float m_AnimationTimer = 0.0f;
	glm::vec2 m_Goal;
	glm::vec2 m_OldGoal;

	bool m_Walking = true;
	static const int m_RunningAnimation[];
	static const int m_WalkAnimation[];
	float m_HP;
};