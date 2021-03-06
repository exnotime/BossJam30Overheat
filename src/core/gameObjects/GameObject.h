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
	virtual void SetColor( const sf::Color& newColor );
	virtual sf::FloatRect GetBoundingBox();
	virtual glm::vec2 GetPosition();
	virtual float GetRotation(){ return m_Rotation; };
	virtual void SetDirection(glm::vec2 direction);
	virtual glm::vec2 GetDirection(){ return m_Direction; };
	virtual bool IsDead();
	virtual void SetDead(bool d);
	virtual void UpdatePosition(float dt, float speed); 
	virtual void TakeDamage(float damage);
protected:
	sf::Sprite	m_Sprite;

	glm::vec2	m_Position;
	glm::vec2	m_Direction;
	glm::vec2	m_Origin;
	glm::vec2	m_Size;
	float		m_Rotation;
	sf::Color	m_Color;
	bool		m_Dead = false;
	float m_TimerInvinsible;
	const float m_TimerInvinsibleMaxTime = 0.3f;
	float m_HP;
	bool m_VisualiseDamage = false;
};