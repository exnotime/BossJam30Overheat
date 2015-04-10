#include "Game.h"

Game::Game(){
	
}

Game::~Game(){

}
//load textures and audio
void Game::Initialize(const sf::RenderWindow& window){
	m_Texture.loadFromFile("asset/TigerCharacterSmaller.png");
	m_Texture.setSmooth(true); //turn on aa
	
	m_Font.loadFromFile("asset/arial.ttf");

	GameObject* go = new GameObject();
	go->SetTexture(&m_Texture);

	m_Player.SetTexture(&m_Texture);

	Enemy *enemyTemp = new Enemy();
	enemyTemp->SetTexture(&m_Texture);
	enemyTemp->SetPosition(200, 50);

	m_GameObjects.push_back(go);
	m_GameObjects.push_back(enemyTemp);
	m_Level.Initialize( "asset/levels/0" );
}
//update game state
void Game::Update(sf::Clock& gameTime){
	float dt = gameTime.restart().asSeconds();
	m_Player.Update(dt);

	for (auto& gameobject : m_GameObjects) {
		gameobject->Update(dt);
		Enemy* enemy = dynamic_cast<Enemy*>(gameobject);
		if (enemy){
			if (m_Player.GetBoundingBox().intersects(gameobject->GetBoundingBox()))
			{
				enemy->SetEaten(true);
			}
		}
	}
}
//render game state
void Game::Draw(sf::RenderWindow* window){
	g_Camera.Apply(window);
	m_Player.Draw(window);
	for (auto& enemy : m_Enemies) {
		enemy.Draw(window);
	}
	for (auto& gameobject : m_GameObjects) {
		gameobject->Draw(window);
	}
	m_Player.Draw(window);
}

void Game::Shutdown(){
	for (unsigned int i = 0; i < m_GameObjects.size(); i++){
		delete m_GameObjects[i];
	}
	m_GameObjects.clear();
}