#pragma once
#include "GameObject.h"
#include <SFML/System.hpp>

class Player : public GameObject {
public:
	Player();
	~Player();
	virtual void Update(float dt);

	glm::vec2& GetPosition();
private:

	const float MOVEMENT_SPEED = 4.0f;

	void CheckAttack(float dt);
	void Maul();
	void Pounce();

	float m_Damage;
	sf::Texture m_Texture;

	float m_MaulTimer;
	float m_PounceTimer;
	float m_HP;
};