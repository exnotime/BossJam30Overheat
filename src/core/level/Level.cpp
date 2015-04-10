#include "Level.h"

#include <SFML/Graphics.hpp>

#define LEVEL_OBJECT_NONE	sf::Color::White
#define LEVEL_OBJECT_SOFA	sf::Color::Red
#define LEVEL_OBJECT_LAMP	sf::Color::Blue
#define LEVEL_OBJECT_TABLE	sf::Color::Green
#define LEVEL_OBJECT_CHAIR	sf::Color::Black

void Level::Initialize( const std::string& levelFolderPath ) {
	sf::Image objectMap;
	objectMap.loadFromFile( levelFolderPath + "/objects.png" );

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