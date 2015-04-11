#pragma once
#include "GameObject.h"
#include <SFML/System.hpp>
#define POUNCE_DELAY -3.0f
class Player : public GameObject {
public:
	Player();
	~Player();
	virtual void Update(float dt);
private:

	float m_MovementSpeed = 4.0f;

	void CheckAttack(float dt);
	void Maul();
	void Pounce();

	float m_Damage;
	sf::Texture m_Texture;
	glm::vec2 m_Direction;
	glm::vec2 m_PounceDirection;

	float m_MaulTimer;
	float m_PounceTimer;
	float m_HP;
};