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
	virtual void SetRotation(float rot);
	virtual void SetOrigin( const glm::vec2& newOrigin );
	virtual void SetSize( const glm::vec2& newSize );
	virtual sf::FloatRect GetBoundingBox();
	virtual glm::vec2 GetPosition();
protected:
	sf::Sprite	m_Sprite;

	glm::vec2	m_Position;
	glm::vec2	m_Direction;
	glm::vec2	m_Origin;
	glm::vec2	m_Size;
	float		m_Rotation;
};