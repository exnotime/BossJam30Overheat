#include "Level.h"

#include <SFML/Graphics.hpp>

#define LEVEL_FLOOR_COLOR_AISLE		sf::Color::White
#define LEVEL_FLOOR_COLOR_WOOD		sf::Color::Black

#define LEVEL_OBJECT_COLOR_NONE		sf::Color::White
#define LEVEL_OBJECT_COLOR_ARMCHAIR	sf::Color::Blue
#define LEVEL_OBJECT_COLOR_TABLE	sf::Color::Red
#define LEVEL_OBJECT_COLOR_TABLE_C	sf::Color( 255, 2, 3 )
#define LEVEL_OBJECT_COLOR_LAMP		sf::Color::Black
#define LEVEL_OBJECT_COLOR_BED		sf::Color::Green
#define LEVEL_OBJECT_COLOR_BED_C	sf::Color( 2, 255, 3 )
#define LEVEL_OBJECT_COLOR_WALL		sf::Color( 111, 111, 111 )

void Level::Initialize( const std::string& levelFolderPath, std::vector<GameObject*>& gameObjects ) {
	m_FloorTextures[ LEVEL_FLOOR_TYPE_AISLE ].loadFromFile( "asset/sprite/floor/aisle.png" );
	m_FloorTextures[ LEVEL_FLOOR_TYPE_WOOD ].loadFromFile( "asset/sprite/floor/wood.png" );

	m_ObjectTextures[ LEVEL_OBJECT_TYPE_ARMCHAIR ].loadFromFile( "asset/sprite/furniture/armchair.png" );
	m_ObjectTextures[ LEVEL_OBJECT_TYPE_TABLE ].loadFromFile( "asset/sprite/furniture/table.png" );
	m_ObjectTextures[ LEVEL_OBJECT_TYPE_LAMP ].loadFromFile( "asset/sprite/furniture/lamp.png" );
	m_ObjectTextures[ LEVEL_OBJECT_TYPE_BED ].loadFromFile( "asset/sprite/furniture/bed.png" );
	m_ObjectTextures[ LEVEL_OBJECT_TYPE_WALL ].loadFromFile( "asset/sprite/levelStuff/wall.png" );

	for ( int i = 0; i < LEVEL_FLOOR_TYPE_SIZE; ++i ) {
		m_FloorTextures[i].setSmooth( true );
	}
	for ( int i = 0; i < LEVEL_OBJECT_TYPE_SIZE; ++i ) {
		m_ObjectTextures[i].setSmooth( true );
	}

	sf::Image floorMap, objectMap, colourMap, POIMap;
	floorMap.loadFromFile( levelFolderPath + "/floor.png" );
	objectMap.loadFromFile( levelFolderPath + "/objects.png" );
	colourMap.loadFromFile( levelFolderPath + "/colours.png" );
	POIMap.loadFromFile(levelFolderPath + "/PathPoints.png");

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
				armchair->SetPosition( x + 0.5f, y + 0.5f );
				armchair->SetSize( glm::vec2( 1.0f ) );
				armchair->SetColor( colourMap.getPixel( x, y ) );

				if ( y != 0 && ColorIsTable( objectMap.getPixel( x, y - 1 ) ) ) {
					armchair->SetRotation( 0.0f );
				} else if ( x != 0 && ColorIsTable( objectMap.getPixel( x - 1, y ) ) ) {
					armchair->SetRotation( 270.0f );
				} else if ( y < objectMap.getSize().y - 1 && ColorIsTable( objectMap.getPixel( x, y + 1 ) ) ) {
					armchair->SetRotation( 180.0f );
				} else if ( x < objectMap.getSize().x - 1 && ColorIsTable( objectMap.getPixel( x + 1, y ) ) ) {
					armchair->SetRotation( 90.0f );
				} else {
					armchair->SetRotation( 90.0f * (rand() % 4) );
				}

				gameObjects.push_back( armchair );
			} else if ( texelColour == LEVEL_OBJECT_COLOR_TABLE ) {
				GameObject* table = new GameObject();
				table->SetTexture( &m_ObjectTextures[ LEVEL_OBJECT_TYPE_TABLE ] );
				table->SetPosition( x + 0.5f, y + 0.5f );
				table->SetSize( glm::vec2( 2.0f, 1.0f ) );
				table->SetOrigin( glm::vec2( 64 ) );

				if ( x != objectMap.getSize().x && objectMap.getPixel( x + 1, y ) == LEVEL_OBJECT_COLOR_TABLE ) {
					table->SetRotation( 0.0f );
					objectMap.setPixel( x + 1, y, LEVEL_OBJECT_COLOR_TABLE_C );
				} else if ( y != objectMap.getSize().y && objectMap.getPixel( x, y + 1 ) == LEVEL_OBJECT_COLOR_TABLE ) {
					table->SetRotation( 90.0f );
					objectMap.setPixel( x, y + 1, LEVEL_OBJECT_COLOR_TABLE_C );
				}
				gameObjects.push_back( table );
			} else if ( texelColour == LEVEL_OBJECT_COLOR_LAMP ) {
				GameObject* lamp = new GameObject();
				lamp->SetTexture( &m_ObjectTextures[ LEVEL_OBJECT_TYPE_LAMP ] );
				lamp->SetPosition( x + 0.5f, y + 0.5f );
				lamp->SetSize( glm::vec2( 1.0f ) );
				lamp->SetRotation( 90.0f * (rand() % 4) );

				gameObjects.push_back( lamp );
			} else if ( texelColour == LEVEL_OBJECT_COLOR_BED ) {
				GameObject* bed = new GameObject();
				bed->SetTexture( &m_ObjectTextures[ LEVEL_OBJECT_TYPE_BED ] );
				bed->SetSize( glm::vec2( 2.0f, 3.0f ) );

				if ( x < objectMap.getSize().x - 2 && objectMap.getPixel( x + 2, y ) == LEVEL_OBJECT_COLOR_BED ) {
					objectMap.setPixel( x + 1, y    , LEVEL_OBJECT_COLOR_BED_C );
					objectMap.setPixel( x + 2, y    , LEVEL_OBJECT_COLOR_BED_C );
					objectMap.setPixel( x    , y + 1, LEVEL_OBJECT_COLOR_BED_C );
					objectMap.setPixel( x + 1, y + 1, LEVEL_OBJECT_COLOR_BED_C );
					objectMap.setPixel( x + 2, y + 1, LEVEL_OBJECT_COLOR_BED_C );

					bed->SetPosition( x + 1.5f, y + 1.0f );
					bed->SetRotation( 90.0f );
				} else {
					objectMap.setPixel( x + 1, y    , LEVEL_OBJECT_COLOR_BED_C );
					objectMap.setPixel( x    , y + 1, LEVEL_OBJECT_COLOR_BED_C );
					objectMap.setPixel( x + 1, y + 1, LEVEL_OBJECT_COLOR_BED_C );
					objectMap.setPixel( x    , y + 2, LEVEL_OBJECT_COLOR_BED_C );
					objectMap.setPixel( x + 1, y + 2, LEVEL_OBJECT_COLOR_BED_C );

					bed->SetPosition( x + 1.0f, y + 1.5f );
					bed->SetRotation( 180.0f );
				}

				gameObjects.push_back( bed );
			} else if ( texelColour == LEVEL_OBJECT_COLOR_WALL ) {
				GameObject* wall = new GameObject();
				wall->SetTexture( &m_ObjectTextures[ LEVEL_OBJECT_TYPE_WALL ] );
				wall->SetPosition( x + 0.5f, y + 0.5f );
				wall->SetSize( glm::vec2( 1.0f ) );
				wall->SetColor( sf::Color( 20, 20, 20 ) );

				gameObjects.push_back( wall );
			} else {
				// Do nothing.
			}
		}
	}

	for (unsigned int y = 0; y < POIMap.getSize().y; ++y) {
		for (unsigned int x = 0; x < POIMap.getSize().x; ++x) {
			sf::Color texelColour = POIMap.getPixel(x, y);
			if (texelColour == sf::Color::Red){
				m_PointsOfInterest.push_back(glm::vec2(x, y) + glm::vec2(0.5f));
			}
		}
	}
}

void Level::Draw( sf::RenderWindow* window ) const {
	sf::Sprite floorSprite;

	for ( unsigned int y = 0; y < m_Floor.size(); ++y ) {
		for ( unsigned int x = 0; x < m_Floor[y].size(); ++x ) {
			floorSprite.setTexture( m_FloorTextures[ static_cast<unsigned int>(m_Floor[y][x]) ] );
			floorSprite.setPosition( static_cast<float>(x), static_cast<float>(y) );
			floorSprite.setScale( 1.0f / floorSprite.getTexture()->getSize().x, 1.0f / floorSprite.getTexture()->getSize().y );
			window->draw( floorSprite );
		}
	}

	sf::RectangleShape border;
	border.setFillColor( sf::Color( 120, 120, 120 ) );
	border.setSize( sf::Vector2f( 0.05f, 1.0f ) );

	for ( unsigned int y = 0; y < m_Floor.size(); ++y ) {
		for ( unsigned int x = 0; x < m_Floor[y].size() - 1; ++x ) {
			if ( m_Floor[y][x] != m_Floor[y][x + 1] ) {
				border.setPosition( static_cast<float>(x + 0.975f), static_cast<float>(y) );
				window->draw( border );
			}
		}
	}

	border.setSize( sf::Vector2f( 1.0f, 0.05f ) );
	unsigned int y = 0;
	for ( unsigned int x = 0; x < m_Floor[y].size(); ++x ) {
		for ( y = 0; y < m_Floor.size() - 1; ++y ) {
			if ( m_Floor[y][x] != m_Floor[y + 1][x] ) {
				border.setPosition( static_cast<float>(x), static_cast<float>(y + 0.975f) );
				window->draw( border );
			}
		}
	}
}

bool Level::ColorIsTable(const sf::Color& color) const {
	return (color == LEVEL_OBJECT_COLOR_TABLE || color == LEVEL_OBJECT_COLOR_TABLE_C);
}

glm::vec2 Level::GetClosestPOI(glm::vec2 pos, glm::vec2 currentGoal, glm::vec2 oldGoal){
	glm::vec2 closest = glm::vec2(0.0f);
	float closestDist = 10000.0f;
	for (auto& it : m_PointsOfInterest){
		float dist = glm::distance(pos, it);
		if (dist < closestDist && (oldGoal != it && currentGoal != it)){
			closest = it;
			closestDist = dist;
		}
	}
	return closest;
}