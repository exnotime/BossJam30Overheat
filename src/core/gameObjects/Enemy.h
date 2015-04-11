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
private:
	const float MOVEMENT_SPEED = 3.0f;
	bool m_Eaten;
};

