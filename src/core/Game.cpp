#include "Game.h"

Game::Game(){
	
}

Game::~Game(){

}
//load textures and audio
void Game::Initialize(const sf::RenderWindow& window){
	m_Texture.loadFromFile("asset/TigerCharacterSmaller.png");
	m_TextureHuman.loadFromFile("asset/sprite/human/human.png");
	m_Texture.setSmooth(true); //turn on aa
	m_TextureHuman.setSmooth(true); //turn on aa

	m_Font.loadFromFile("asset/arial.ttf");

	GameObject* go = new GameObject();
	go->SetTexture(&m_Texture);
	go->SetSize( glm::vec2( 2.0f, 6.0f ) );

	m_Player.SetTexture(&m_Texture);
	m_Player.SetPosition( 0.0f, 0.0f );
	m_Player.SetSize( glm::vec2( 1.0f, 3.0f ) );

	Enemy *enemyTemp = new Enemy();
	enemyTemp->SetTexture(&m_TextureHuman);
	enemyTemp->SetPosition( 2.0f, 0.5f );
	enemyTemp->SetSize( glm::vec2( 1.0f, 0.8f ) );

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