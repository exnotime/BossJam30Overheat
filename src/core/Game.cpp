#include "Game.h"

#include "GameObject.h"
Game::Game(){
	
}

Game::~Game(){

}
//load textures and audio
void Game::Initialize(const sf::RenderWindow& window){
	m_Texture.loadFromFile("asset/circle.jpg");
	m_Texture.setSmooth(true); //turn on aa

	m_Font.loadFromFile("asset/arial.ttf");

	GameObject go;
	go.SetTexture(&m_Texture);
	m_GameObjects.push_back(go);
}
//update game state
void Game::Update(sf::Clock& gameTime){
	float dt = gameTime.restart().asSeconds();

	for (auto& gameobject : m_GameObjects) {
		gameobject.Update(dt);
	}
}
//render game state
void Game::Draw(sf::RenderWindow* window){
	for (auto& gameobject : m_GameObjects) {
		gameobject.Draw(window);
	}
}