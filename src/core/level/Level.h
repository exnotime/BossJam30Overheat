#pragma once

#include <SFML/Graphics.hpp>

enum FLOOR_TYPE {
	FLOOR_TYPE_AISLE,
	FLOOR_TYPE_WOOD,
	FLOOR_TYPE_SIZE,	// KEEP SECOND TO LAST!!!
	FLOOR_TYPE_NONE		// KEEP LAST!!!
};

class Level
{
public:
	void		Initialize( const std::string& levelFolderPath );
	void		Draw( sf::RenderWindow* window ) const;

private:
	sf::Texture								m_FloorTextures[ FLOOR_TYPE_SIZE ];
	std::vector<std::vector<FLOOR_TYPE>>	m_Floor;
};