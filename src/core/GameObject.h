#pragma once
#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
class GameObject {
public:
	GameObject();
	~GameObject();
	void SetTexture(sf::Texture* texture);
	void Update(float dt);
	void Draw(sf::RenderWindow* window);

private:
	sf::Sprite	m_Sprite;

	glm::vec2	m_Position;
	glm::vec2	m_Origin;
	float		m_Rotation;
	float		m_Scale;
};