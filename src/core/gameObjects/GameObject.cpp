#include "GameObject.h"

GameObject::GameObject() {
	m_Position = glm::vec2(0);
	m_Direction = glm::vec2(0);
	m_Origin = glm::vec2(0);
	m_Rotation = 0.0f;
	m_Color = sf::Color::White;
}

GameObject::~GameObject() {

}

void GameObject::Update(float dt) {
	//update sprite
	m_Sprite.setPosition(m_Position.x, m_Position.y);
	m_Sprite.setOrigin(m_Origin.x, m_Origin.y);
	m_Sprite.setRotation(m_Rotation);

	if ( !m_VisualiseDamage || m_TimerInvinsible < 0.0f )
		m_Sprite.setColor( m_Color );
	else
		m_Sprite.setColor( sf::Color::Red );
}

void GameObject::Draw(sf::RenderWindow* window) {
	window->draw(m_Sprite);

	//sf::CircleShape dot;
	//dot.setPosition(m_Position.x, m_Position.y);
	//dot.setRadius(0.1f);
	//dot.setOrigin(0.05f, 0.05f);
	//window->draw(dot);
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

void GameObject::SetColor( const sf::Color& newColor ) {
	m_Color = newColor;
}

sf::FloatRect GameObject::GetBoundingBox(){
	return m_Sprite.getGlobalBounds();
}

glm::vec2 GameObject::GetPosition(){
	return m_Position;
}

bool GameObject::IsDead() {
	return m_Dead;
}
void GameObject::SetDead(bool d) { 
	m_Dead = d;
}

void GameObject::SetDirection(glm::vec2 direction){
	m_Direction = direction;
}

void GameObject::UpdatePosition(float dt, float speed){
	m_Position += m_Direction * dt * speed;
}

void GameObject::TakeDamage(float damage){
	if (m_TimerInvinsible < 0.0f){
		m_HP -= damage;
		if (m_HP <= 0.0f){
			m_Dead = true;
		}
		m_TimerInvinsible = m_TimerInvinsibleMaxTime;
	}
}