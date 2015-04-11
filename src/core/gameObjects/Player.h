#pragma once
#include "GameObject.h"
#include <SFML/System.hpp>
class Player : public GameObject {
public:
	Player();
	~Player();
	virtual void Update(float dt);

	sf::FloatRect GetBoundingBoxMaul();
	sf::FloatRect GetBoundingBoxPounce();
	float GetDamage();
	bool GetMauling();
	bool GetPouncing();
private:

	float m_MovementSpeed = 4.0f;
	const float MAULTIME = 1.0f;
	const float POUNCETIME = 0.2f;
	const float POUNCE_DELAY = -3.0f;

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

	bool m_Mauling;
	bool m_Pouncing;
};