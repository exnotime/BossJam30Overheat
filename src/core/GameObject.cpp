#include "GameObject.h"

GameObject::GameObject() {
	m_Position = glm::vec2(0);
	m_Direction = glm::vec2(0);
	m_Origin = glm::vec2(0);
	m_Rotation = 0.0f;
	m_Scale = 1.0f; 
}

GameObject::~GameObject() {

}

void GameObject::Update(float dt) {
	//update sprite
	m_Sprite.setPosition(m_Position.x, m_Position.y);
	m_Sprite.setScale(m_Scale, m_Scale);
	m_Sprite.setOrigin(m_Origin.x, m_Origin.y);
	m_Sprite.setRotation(m_Rotation);
}

void GameObject::Draw(sf::RenderWindow* window) {
	window->draw(m_Sprite);
}

void GameObject::SetTexture(sf::Texture* texture) {
	m_Sprite.setTexture(*texture);
}

void GameObject::SetPosition(float x, float y){
	m_Position = glm::vec2(x, y);
}

sf::FloatRect GameObject::GetBoundingBox(){
	return m_Sprite.getGlobalBounds();
}
