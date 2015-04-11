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
	glm::vec2 m_BoundingBoxDirection;
private:
	const float DEFAULT_SPEED = 4.0f;
	float m_MovementSpeed = DEFAULT_SPEED;
	const float MAULTIME = 0.1f;
	const float MAUL_DELAY = -0.2f;
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
	bool m_Walking;
	float m_AnimationTimer = 0.0f;
	static const int m_RunningAnimation[];
	static const int m_WalkAnimation[];

	glm::vec2 m_Aim;
};