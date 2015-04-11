#pragma once
#include "GameObject.h"
#include <SFML/System.hpp>
class Enemy :
	public GameObject
{
public:
	Enemy();
	~Enemy();
	void Draw(sf::RenderWindow* window) override;
	void Update(float dt) override;
	void SetEaten(bool eaten);
	void SetAlert(bool alert);
private:
	float m_MovementSpeed = 1.0f;
	bool m_Eaten;
	float m_AnimationTimer = 0.0f;

	bool m_Walking = true;
	static const int m_RunningAnimation[];
	static const int m_WalkAnimation[];
	float m_HP;
};



