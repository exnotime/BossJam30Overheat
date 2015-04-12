#pragma once
#include "GameObject.h"
#include <SFML/System.hpp>
class Level;
class Enemy :
	public GameObject
{
public:
	Enemy();
	~Enemy();
	void Draw(sf::RenderWindow* window) override;
	void Update(float dt) override;
	void SetAlert(bool alert);
	void SetGoal(glm::vec2 goal);
	
	void UpdatePOI(Level& level);

	float GetVisionDist();
	float GetVisionCone();
private:
	float m_MovementSpeed = 1.0f;
	float m_AnimationTimer = 0.0f;
	glm::vec2 m_Goal;
	glm::vec2 m_OldGoal;
	bool m_Walking = true;
	bool m_StandingStill;
	static const int m_RunningAnimation[];
	static const int m_WalkAnimation[];
	float m_VisionCone; //cos(angle)
	float m_VisionDistance;

};