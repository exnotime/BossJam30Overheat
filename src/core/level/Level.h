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
	LEVEL_OBJECT_TYPE_BED,
	LEVEL_OBJECT_TYPE_WALL,
	LEVEL_OBJECT_TYPE_SIZE,		// KEEP SECOND TO LAST!!!
	LEVEL_OBJECT_TYPE_NONE		// KEEP LAST!!!
};

class Level
{
public:
	void		Initialize( const std::string& levelFolderPath, std::vector<GameObject*>& gameObjects );
	void		Draw( sf::RenderWindow* window ) const;
	glm::vec2	GetNextGoal(glm::vec2 pos);
	bool		IsTileBlocked( int x, int y ) const;
	glm::vec2	GetRandomFreeTile();

private:
	bool										ColorIsTable( const sf::Color& color ) const;

	sf::Texture									m_FloorTextures[ LEVEL_FLOOR_TYPE_SIZE ];
	sf::Texture									m_ObjectTextures[ LEVEL_OBJECT_TYPE_SIZE ];
	std::vector<std::vector<LEVEL_FLOOR_TYPE>>	m_Floor;
	std::vector<glm::vec2>						m_PointsOfInterest;
	std::vector<std::vector<bool>>				m_BlockedTiles;
	std::vector<std::vector<glm::vec2>>			m_FlowMap;
	glm::vec2									m_LevelSize;
};