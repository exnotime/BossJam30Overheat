#pragma once
#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
class GameObject {
public:
	GameObject();
	~GameObject();
	void SetTexture(sf::Texture* texture);
	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow* window);
	virtual void SetPosition(float x, float y);
	virtual void SetSize( const glm::vec2& newSize );
	virtual sf::FloatRect GetBoundingBox();
protected:
	sf::Sprite	m_Sprite;

	glm::vec2	m_Position;
	glm::vec2	m_Direction;
	glm::vec2	m_Origin;
	glm::vec2	m_Size;
	float		m_Rotation;
};