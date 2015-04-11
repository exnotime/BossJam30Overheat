#include "Camera.h"

Camera::Camera(){
	m_View.setCenter(0, 0);
	m_View.setSize(24, 13.5f);	// Multiple of ( 16, 9 ) to avoid stretching, by keeping aspect ratio correct.
	
	m_GUIView.setCenter(0, 0);
	m_GUIView.setSize(1280, 720);
}

Camera::~Camera() {

}

Camera& Camera::GetInstance() {
	static Camera instance;
	return instance;
}

void Camera::Apply(sf::RenderWindow* window) {
	m_View.setCenter(m_Position.x, m_Position.y);
	window->setView(m_View);
}

void Camera::ApplyGUI(sf::RenderWindow* window) {
	m_View.setCenter(m_Position.x, m_Position.y);
	window->setView(m_GUIView);
}

void Camera::SetPosition(glm::vec2 pos) {
	m_Position = pos;
}