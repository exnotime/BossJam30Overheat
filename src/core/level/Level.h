#pragma once

#include <SFML/Graphics.hpp>
#include "gameObjects/GameObject.h"

enum LEVEL_FLOOR_TYPE {
	LEVEL_FLOOR_TYPE_AISLE,
	LEVEL_FLOOR_TYPE_WOOD,
	LEVEL_FLOOR_TYPE_SIZE,		// KEEP SECOND TO LAST!!!
	LEVEL_FLOOR_TYPE_NONE		// KEEP LAST!!!
};

enum LEVEL_OBJECT_TYPE {
	LEVEL_OBJECT_TYPE_ARMCHAIR,
	LEVEL_OBJECT_TYPE_TABLE,
	LEVEL_OBJECT_TYPE_LAMP,
	LEVEL_OBJECT_TYPE_SOFA,
	LEVEL_OBJECT_TYPE_SIZE,		// KEEP SECOND TO LAST!!!
	LEVEL_OBJECT_TYPE_NONE		// KEEP LAST!!!
};

class Level
{
public:
	void		Initialize( const std::string& levelFolderPath, std::vector<GameObject*>& gameObjects );
	void		Draw( sf::RenderWindow* window ) const;
	glm::vec2	GetClosestPOI(glm::vec2 pos, glm::vec2 currentGoal, glm::vec2 oldGoal);

private:
	bool										ColorIsTable( const sf::Color& color ) const;

	sf::Texture									m_FloorTextures[ LEVEL_FLOOR_TYPE_SIZE ];
	sf::Texture									m_ObjectTextures[ LEVEL_OBJECT_TYPE_SIZE ];
	std::vector<std::vector<LEVEL_FLOOR_TYPE>>	m_Floor;
	std::vector<glm::vec2>						m_PointsOfInterest;
};