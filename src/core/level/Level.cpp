#include "Level.h"

#include <SFML/Graphics.hpp>

#define LEVEL_FLOOR_AISLE	sf::Color::White
#define LEVEL_FLOOR_WOOD	sf::Color::Black

#define LEVEL_OBJECT_NONE	sf::Color::White
#define LEVEL_OBJECT_SOFA	sf::Color::Red
#define LEVEL_OBJECT_LAMP	sf::Color::Blue
#define LEVEL_OBJECT_TABLE	sf::Color::Green
#define LEVEL_OBJECT_CHAIR	sf::Color::Black

void Level::Initialize( const std::string& levelFolderPath ) {
	m_FloorTextures[ FLOOR_TYPE_AISLE ].loadFromFile( "asset/sprite/floor/aisle.png" );
	m_FloorTextures[ FLOOR_TYPE_WOOD ].loadFromFile( "asset/sprite/floor/wood.png" );

	sf::Image floorMap, objectMap;
	floorMap.loadFromFile( levelFolderPath + "/floor.png" );
	objectMap.loadFromFile( levelFolderPath + "/objects.png" );

	m_Floor.resize( floorMap.getSize().y );
	for ( unsigned int y = 0; y < floorMap.getSize().y; ++y ) {
		m_Floor[y].resize( floorMap.getSize().x );

		for ( unsigned int x = 0; x < floorMap.getSize().x; ++x ) {
			sf::Color	texelColour	= floorMap.getPixel( x, y );
			FLOOR_TYPE&	floorTile	= m_Floor[y][x];

			if ( texelColour == LEVEL_FLOOR_AISLE ) {
				floorTile = FLOOR_TYPE_AISLE;
			} else if ( texelColour == LEVEL_FLOOR_WOOD ) {
				floorTile = FLOOR_TYPE_WOOD;
			} else {
				floorTile = FLOOR_TYPE_NONE;
			}
		}
	}

	std::vector<std::string> derp;
	derp.resize( objectMap.getSize().y );

	for ( unsigned int y = 0; y < objectMap.getSize().y; ++y ) {
		for ( unsigned int x = 0; x < objectMap.getSize().x; ++x ) {
			sf::Color texelColour = objectMap.getPixel( x, y );

			if ( texelColour == LEVEL_OBJECT_NONE ) {
				derp[y].append( "." );
			} else if ( texelColour == LEVEL_OBJECT_SOFA ) {
				derp[y].append( "S" );
			} else if ( texelColour == LEVEL_OBJECT_LAMP ) {
				derp[y].append( "L" );
			} else if ( texelColour == LEVEL_OBJECT_TABLE ) {
				derp[y].append( "T" );
			} else if ( texelColour == LEVEL_OBJECT_CHAIR ) {
				derp[y].append( "C" );
			} else {
				derp[y].append( "." );
			}
		}
	}
}

void Level::Draw( sf::RenderWindow* window ) const {
	sf::Sprite sprite;

	for ( unsigned int y = 0; y < m_Floor.size(); ++y ) {
		for ( unsigned int x = 0; x < m_Floor[y].size(); ++x ) {
			sprite.setTexture( m_FloorTextures[ static_cast<unsigned int>(m_Floor[y][x]) ] );
			sprite.setPosition( x, y );
			sprite.setScale( 1.0f / sprite.getTexture()->getSize().x, 1.0f / sprite.getTexture()->getSize().y );
			window->draw( sprite );
		}
	}
}