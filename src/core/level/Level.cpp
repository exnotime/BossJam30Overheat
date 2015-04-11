#include "Level.h"

#include <SFML/Graphics.hpp>

#define LEVEL_FLOOR_COLOR_AISLE		sf::Color::White
#define LEVEL_FLOOR_COLOR_WOOD		sf::Color::Black

#define LEVEL_OBJECT_COLOR_NONE		sf::Color::White
#define LEVEL_OBJECT_COLOR_ARMCHAIR	sf::Color::Blue
#define LEVEL_OBJECT_COLOR_SOFA		sf::Color::Red
#define LEVEL_OBJECT_COLOR_LAMP		sf::Color::Black
#define LEVEL_OBJECT_COLOR_TABLE	sf::Color::Green

void Level::Initialize( const std::string& levelFolderPath, std::vector<GameObject*>& gameObjects ) {
	m_FloorTextures[ LEVEL_FLOOR_TYPE_AISLE ].loadFromFile( "asset/sprite/floor/aisle.png" );
	m_FloorTextures[ LEVEL_FLOOR_TYPE_WOOD ].loadFromFile( "asset/sprite/floor/wood.png" );

	m_ObjectTextures[ LEVEL_OBJECT_TYPE_ARMCHAIR ].loadFromFile( "asset/sprite/furniture/armchair.png" );

	for ( int i = 0; i < LEVEL_FLOOR_TYPE_SIZE; ++i ) {
		m_FloorTextures[i].setSmooth( true );
	}
	for ( int i = 0; i < LEVEL_OBJECT_TYPE_SIZE; ++i ) {
		m_ObjectTextures[i].setSmooth( true );
	}

	sf::Image floorMap, objectMap;
	floorMap.loadFromFile( levelFolderPath + "/floor.png" );
	objectMap.loadFromFile( levelFolderPath + "/objects.png" );

	m_Floor.resize( floorMap.getSize().y );
	for ( unsigned int y = 0; y < floorMap.getSize().y; ++y ) {
		m_Floor[y].resize( floorMap.getSize().x );

		for ( unsigned int x = 0; x < floorMap.getSize().x; ++x ) {
			sf::Color			texelColour	= floorMap.getPixel( x, y );
			LEVEL_FLOOR_TYPE&	floorTile	= m_Floor[y][x];

			if ( texelColour == LEVEL_FLOOR_COLOR_AISLE ) {
				floorTile = LEVEL_FLOOR_TYPE_AISLE;
			} else if ( texelColour == LEVEL_FLOOR_COLOR_WOOD ) {
				floorTile = LEVEL_FLOOR_TYPE_WOOD;
			} else {
				floorTile = LEVEL_FLOOR_TYPE_NONE;
			}
		}
	}

	for ( unsigned int y = 0; y < objectMap.getSize().y; ++y ) {
		for ( unsigned int x = 0; x < objectMap.getSize().x; ++x ) {
			sf::Color texelColour = objectMap.getPixel( x, y );

			if ( texelColour == LEVEL_OBJECT_COLOR_NONE ) {
				// Do nothing.
			} else if ( texelColour == LEVEL_OBJECT_COLOR_ARMCHAIR ) {
				GameObject* armchair = new GameObject();
				armchair->SetTexture( &m_ObjectTextures[ LEVEL_OBJECT_TYPE_ARMCHAIR ] );
				armchair->SetPosition( static_cast<float>(x), static_cast<float>(y) );
				armchair->SetSize( glm::vec2( 1.0f ) );
				gameObjects.push_back( armchair );
			} else {
				// Do nothing.
			}
		}
	}
}

void Level::Draw( sf::RenderWindow* window ) const {
	sf::Sprite sprite;

	for ( unsigned int y = 0; y < m_Floor.size(); ++y ) {
		for ( unsigned int x = 0; x < m_Floor[y].size(); ++x ) {
			sprite.setTexture( m_FloorTextures[ static_cast<unsigned int>(m_Floor[y][x]) ] );
			sprite.setPosition( static_cast<float>(x), static_cast<float>(y) );
			sprite.setScale( 1.0f / sprite.getTexture()->getSize().x, 1.0f / sprite.getTexture()->getSize().y );
			window->draw( sprite );
		}
	}
}