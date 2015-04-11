#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include "gameObjects/Player.h"
#include "gameObjects/Enemy.h"
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
private:
	//these are all just example variables
	sf::Texture				m_Texture;
	sf::Texture				m_TextureHuman;
	sf::Texture				m_DeadEnemyTexture;
	sf::Font				m_Font;
	Player					m_Player;
	std::vector<GameObject*> m_GameObjects;
	Level					m_Level;
};