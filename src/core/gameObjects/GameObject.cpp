#include "GameObject.h"

GameObject::GameObject() {
	m_Position = glm::vec2(0);
	m_Direction = glm::vec2(0);
	m_Origin = glm::vec2(0);
	m_Rotation = 0.0f;
}

GameObject::~GameObject() {

}

void GameObject::Update(float dt) {
	//update sprite
	m_Sprite.setPosition(m_Position.x, m_Position.y);
	m_Sprite.setOrigin(m_Origin.x, m_Origin.y);
	m_Sprite.setRotation(m_Rotation);
}

void GameObject::Draw(sf::RenderWindow* window) {
	window->draw(m_Sprite);
}

void GameObject::SetTexture(sf::Texture* texture) {
	m_Sprite.setTexture(*texture);

	m_Origin.x = 0.5f * texture->getSize().x;
	m_Origin.y = 0.5f * texture->getSize().y;
}

void GameObject::SetPosition(float x, float y){
	m_Position = glm::vec2(x, y);
}

void GameObject::SetRotation(float rot) {
	m_Rotation = rot;
}

void GameObject::SetOrigin( const glm::vec2& newOrigin ) {
	m_Origin = newOrigin;
}

void GameObject::SetSize( const glm::vec2& newSize ) {
	m_Sprite.setScale( newSize.x / m_Sprite.getTextureRect().width, newSize.y / m_Sprite.getTextureRect().height );
	m_Size = newSize;
}

sf::FloatRect GameObject::GetBoundingBox(){
	return m_Sprite.getGlobalBounds();
}

glm::vec2 GameObject::GetPosition(){
	return m_Position;
}