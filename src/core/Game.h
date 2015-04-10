#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

class GameObject;
#include "level/Level.h"

class Game
{
public:
	Game();
	~Game();
	void Initialize(const sf::RenderWindow& window);
	void Update(sf::Clock& gameTime);
	void Draw(sf::RenderWindow* window);
private:
	//these are all just example variables
	sf::Texture m_Texture;
	sf::Font m_Font;

	std::vector<GameObject> m_GameObjects;
	Level					m_Level;
};