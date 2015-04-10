#include "Level.h"

#include <SFML/Graphics.hpp>

void Level::Initialize( const std::string& levelFolderPath ) {
	sf::Texture objectMap;
	objectMap.loadFromFile( levelFolderPath + "/objects.png" );
}