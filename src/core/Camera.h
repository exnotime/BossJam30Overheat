#pragma once
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

#define g_Camera Camera::GetInstance()
class Camera {
public:
	static Camera& GetInstance();
	void SetPosition(glm::vec2 pos);
	void Apply(sf::RenderWindow* window);
	void ApplyGUI(sf::RenderWindow* window);


	glm::vec2& GetPosition() { return m_Position; };

	sf::View& GetView(){ return m_View; };
private:
	Camera();
	~Camera();
	sf::View	m_View;
	sf::View	m_GUIView;
	glm::vec2	m_Position;
};