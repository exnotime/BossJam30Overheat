#include "Game.h"

Game::Game(){
	
}

Game::~Game(){

}
//load textures and audio
void Game::Initialize(const sf::RenderWindow& window){
	m_Level.Initialize( "asset/levels/1", m_GameObjects );

	m_TextureHuman.loadFromFile("asset/sprite/human/human.png");
	m_TextureHuman.setSmooth(true); //turn on aa
	m_DeadEnemyTexture.loadFromFile("asset/sprite/human/dead.png");
	m_DeadEnemyTexture.setSmooth(true);
	m_TextureBossman.loadFromFile("asset/sprite/boss/Bossen.png");
	m_DeadEnemyTexture.setSmooth(true);
	m_Font.loadFromFile("asset/arial.ttf");

	m_Player.SetPosition( 27.0f, 43.0f );
	m_Player.SetSize( glm::vec2( 1.0f, 3.0f ) );

	Enemy *enemyTemp = new Enemy();
	enemyTemp->SetTexture(&m_TextureHuman);
	enemyTemp->SetPosition( 5.0f, 0.5f );
	enemyTemp->SetSize(glm::vec2(0.6f, 0.5f) * 1.3f);
	enemyTemp->SetGoal(m_Level.GetNextGoal(enemyTemp->GetPosition()));
	m_GameObjects.push_back(enemyTemp);

	m_Boss.SetPosition( 20.0f, 20.0f );
	m_Boss.SetSize(glm::vec2(2.0f, 1.28f));
	m_Boss.SetTexture(&m_TextureBossman);

	m_HighScore = 0;
	m_KillCount = 0;
	m_KillStreak = 0;
	m_TimerKillStreak = 0.0f;
	m_TextHighScore = sf::Text("HighScore: ", m_Font, 30);
	m_TextHighScore.setPosition(-630, -350);
	m_TextHighScore.setString("HighScore: " + std::to_string(m_HighScore));
	m_TextKillCount = sf::Text("Killcount: ", m_Font, 30);
	m_TextKillCount.setPosition(-630, -310);
	m_TextKillCount.setString("Killcount: " + std::to_string(m_KillCount));
	m_TextKillStreak = sf::Text("", m_Font, 30);
	m_TextKillStreak.setPosition(-100, 0);
	m_TextTimerKillStreak = sf::Text("Killstreak Countdown: ", m_Font, 30);
	m_TextTimerKillStreak.setPosition(-630, -270);

	m_EnemySpawnTimer = 5.0f;

}
//update game state
void Game::Update(sf::Clock& gameTime){
	float dt = gameTime.restart().asSeconds();
	m_Player.Update(dt);
	m_Player.ContainWithinLevel( m_Level );

	m_Boss.Update(dt);
	m_Boss.UpdatePOI( m_Level, m_Player.GetPosition(), dt );

	std::vector<GameObject*> objectsToBeAdded;
	for (auto& gameobject : m_GameObjects) {
		gameobject->Update(dt);
		Enemy* enemy = dynamic_cast<Enemy*>(gameobject);
		if (enemy){
			//calc vision cone
			glm::vec2 enemyToPlayer = m_Player.GetPosition() - enemy->GetPosition();
			float angle = glm::dot(glm::normalize(enemyToPlayer), glm::normalize(enemy->GetDirection()));
			if (glm::length(enemyToPlayer) < enemy->GetVisionDist() && angle > enemy->GetVisionCone()){
				if (VisionTest(enemy->GetPosition(), enemyToPlayer))
					enemy->SetAlert(true);
			}
			enemy->UpdatePOI(m_Level);
			if (enemy->IsDead()){
				GameObject* deadbody = new GameObject();
				deadbody->SetPosition(enemy->GetPosition().x, enemy->GetPosition().y);
				deadbody->SetRotation(enemy->GetRotation());
				deadbody->SetTexture(&m_DeadEnemyTexture);
				deadbody->SetSize(glm::vec2(0.5f, 1.0f) * 1.7f);
				deadbody->Update(dt);
				objectsToBeAdded.push_back(deadbody);
			}
		}
	}
	for (auto& it : objectsToBeAdded){
		it->Update(dt);
		m_GameObjects.push_back(it);
	}
	objectsToBeAdded.clear();
	for (int i = 0; i < (int)m_GameObjects.size(); i++){
		if (m_GameObjects[i]->IsDead()){
			delete m_GameObjects[i];
			m_GameObjects.erase(m_GameObjects.begin() + i);
			i--;
		}
	}
	m_EnemySpawnTimer -= dt;
	if (m_EnemySpawnTimer <= 0.0f){
		Enemy *enemyTemp = new Enemy();
		enemyTemp->SetTexture(&m_TextureHuman);
		glm::vec2 pos = m_Level.GetRandomFreeTile();
		enemyTemp->SetPosition(pos.x,pos.y );
		enemyTemp->SetSize(glm::vec2(0.6f, 0.5f) * 1.3f);
		enemyTemp->SetGoal(m_Level.GetNextGoal(enemyTemp->GetPosition()));
		m_GameObjects.push_back(enemyTemp);
		m_EnemySpawnTimer = 5.0f;
	}
	CheckCollisions();
	m_TimerKillStreak -= dt;
	if (m_TimerKillStreak > 0.0f){
		m_TextTimerKillStreak.setString("Killstreak Countdown: " + std::to_string((int)std::ceilf(m_TimerKillStreak)));
	} else {
		m_TextTimerKillStreak.setString("Killstreak Countdown: 0");
	}
	if (m_TimerKillStreak < 0.0f){
		if (m_KillStreak >= 3){
			m_TextKillStreak.setString("WOW you love swedes!");
			m_HighScore += 1000;
		}
		if (m_KillStreak >= 5){
			m_TextKillStreak.setString("Careful you are getting sick of meatballs!");
			m_HighScore += 2000;
		}
		if (m_KillStreak >= 8){
			m_TextKillStreak.setString("Keep Eating and even Ingrad Kamprad will look tasty");
			m_HighScore += 5000;
		}
		if (m_KillStreak >= 10){
			m_TextKillStreak.setString("Swedes are now hailing the TigerKING");
			m_HighScore += 10000;
		}
		if (m_TimerKillStreak < -3.0f){
			m_TextKillStreak.setString("");
		}
		m_KillStreak = 0;
	}
	m_TextHighScore.setString("HighScore: " + std::to_string(m_HighScore));
	m_TextKillCount.setString("Killcount: " + std::to_string(m_KillCount));
}
//render game state
void Game::Draw(sf::RenderWindow* window){
	g_Camera.Apply(window);
	m_Level.Draw( window );

	for (auto& gameobject : m_GameObjects) {
		gameobject->Draw(window);
	}
	m_Player.Draw(window);
	m_Boss.Draw(window);
	g_Camera.ApplyGUI(window);
	window->draw(m_TextHighScore);
	window->draw(m_TextKillCount);
	window->draw(m_TextKillStreak);
	window->draw(m_TextTimerKillStreak);
}

void Game::Shutdown(){
	for (unsigned int i = 0; i < m_GameObjects.size(); i++){
		delete m_GameObjects[i];
	}
	m_GameObjects.clear();
}

void Game::CheckCollisions(){
	for (auto& gameobject : m_GameObjects) {
		Enemy* enemy = dynamic_cast<Enemy*>(gameobject);
		if (enemy){
			if (!enemy->IsDead()){
				if (m_Player.GetMauling()){
					if (m_Player.GetBoundingBoxMaul().intersects(gameobject->GetBoundingBox()))
					{
						enemy->TakeDamage(m_Player.GetDamage());
						if (enemy->IsDead()){
							GiveScore(100);
						}
					}
				}
				if (m_Player.GetPouncing()){
					if (m_Player.GetBoundingBoxPounce().intersects(gameobject->GetBoundingBox()))
					{
						enemy->TakeDamage(m_Player.GetDamage());
						if (enemy->IsDead()){
							GiveScore(200);
						}
					}
				}
			}
		}
	}
}

void Game::GiveScore(unsigned int points){
	m_HighScore += points;
	m_KillCount += 1;
	m_KillStreak += 1;
	m_TimerKillStreak = 3.0f;
}

bool Game::VisionTest(glm::vec2 pos, glm::vec2 dir){
	glm::vec2 testpos;
	int nSamples = 1000;
	glm::vec2 normDir = glm::normalize(dir);
	for (int i = 0; i < nSamples; i++){
		float dist = (i / (float)nSamples) * 10.0f;
		testpos = pos + normDir * dist;
		if (m_Level.IsTileBlocked(testpos.x, testpos.y)){
			return false;
		}
	}
	return true;
}