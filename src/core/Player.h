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
	const float MOVEMENT_SPEED = 1000.0f;
};