#include "Game.h"

Game::Game(){
	
}

Game::~Game(){

}
//load textures and audio
void Game::Initialize(const sf::RenderWindow& window){
	m_Level.Initialize( "asset/levels/0", m_GameObjects );

	m_TextureHuman.loadFromFile("asset/sprite/human/human.png");
	m_TextureHuman.setSmooth(true); //turn on aa

	m_Font.loadFromFile("asset/arial.ttf");

	m_Player.SetPosition( 0.0f, 0.0f );
	m_Player.SetSize( glm::vec2( 1.0f, 3.0f ) );

	Enemy *enemyTemp = new Enemy();
	enemyTemp->SetTexture(&m_TextureHuman);
	enemyTemp->SetPosition( 5.0f, 0.5f );
	enemyTemp->SetSize( glm::vec2( 0.6f, 0.5f ) );
	enemyTemp->SetGoal(m_Level.GetClosestPOI(enemyTemp->GetPosition(), enemyTemp->GetPosition(), enemyTemp->GetPosition()));
	m_GameObjects.push_back(enemyTemp);
}
//update game state
void Game::Update(sf::Clock& gameTime){
	float dt = gameTime.restart().asSeconds();
	m_Player.Update(dt);
	m_Player.ContainWithinLevel( m_Level );

	for (auto& gameobject : m_GameObjects) {
		gameobject->Update(dt);
		Enemy* enemy = dynamic_cast<Enemy*>(gameobject);
		if (enemy){
			if (m_Player.GetBoundingBox().intersects(gameobject->GetBoundingBox()))
			{
				enemy->SetEaten(true);
			}

			if (glm::length(m_Player.GetPosition() - enemy->GetPosition()) < 5.0f){
				enemy->SetAlert(true);
			} else {
				enemy->SetAlert(false);
			}
			enemy->UpdatePOI(m_Level);
		}
	}

	CheckCollisions();
}
//render game state
void Game::Draw(sf::RenderWindow* window){
	g_Camera.Apply(window);
	m_Level.Draw( window );

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

void Game::CheckCollisions(){
	sf::FloatRect playerRect;
	sf::FloatRect enemyRect;

	for (auto& gameobject : m_GameObjects) {
		Enemy* enemy = dynamic_cast<Enemy*>(gameobject);
		if (enemy){
			if (m_Player.GetMauling()){
				if (m_Player.GetBoundingBoxMaul().intersects(gameobject->GetBoundingBox()))
				{
					enemy->TakeDamage(m_Player.GetDamage());
				}
			}
			if (m_Player.GetPouncing()){
				if (m_Player.GetBoundingBoxPounce().intersects(gameobject->GetBoundingBox()))
				{
					enemy->TakeDamage(m_Player.GetDamage());
				}
			}
		}
	}

	//playerRect = m_Player.GetBoundingBoxMaul();
}