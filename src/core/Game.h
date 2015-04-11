#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include "gameObjects/Player.h"
#include "gameObjects/Enemy.h"
#include "gameObjects/Boss.h"
class GameObject;
#include "level/Level.h"
#include "Camera.h"

class Game
{
public:
	Game();
	~Game();
	void Initialize(const sf::RenderWindow& window);
	void Update(sf::Clock& gameTime);
	void Draw(sf::RenderWindow* window);
	void Shutdown();

	void CheckCollisions();
	void GiveScore(unsigned int points);

private:
	//these are all just example variables
	sf::Texture				m_Texture;
	sf::Texture				m_TextureHuman;
	sf::Texture				m_DeadEnemyTexture;
	sf::Texture				m_TextureBossman;
	sf::Font				m_Font;
	Player					m_Player;
	std::vector<GameObject*> m_GameObjects;
	Boss					m_Boss;
	Level					m_Level;

	unsigned int			m_HighScore;
	unsigned int			m_KillCount;
	unsigned int			m_KillStreak;
	sf::Text				m_TextHighScore;
	sf::Text				m_TextKillCount;
	float 					m_EnemySpawnTimer;
	sf::Text				m_TextKillStreak;
	float					m_TimerKillStreak;
	sf::Text				m_TextTimerKillStreak;
};