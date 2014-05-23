//
//  MapGenerator.cpp
//  MotorCity
//
//  Created by Karl Persson on 2013-12-09.
//  Copyright (c) 2013 Karl Persson. All rights reserved.
//

#include "MapGenerator.h"

// Get roads from bitmap
bool MapGenerator::getRoads(Tiles& tiles, Tiles& destinationTiles, TextureManager& textureManager) {
    sf::Image image;
    
    // Read file
    if (!image.loadFromFile(resourcePath() + "WorldMap.png")) {
        // No map!
        return false;
    }
    else {
        // Going through each row
        for (int y = 0; y < image.getSize().y; y++) {
            for (int x = 0; x < image.getSize().x; x++) {
                // Fetch color
                sf::Color color = image.getPixel(x, y);
                // Add road tile (black)
                if (color == sf::Color::Black) {
                    RoadTile* currentTile = new RoadTile(&textureManager, sf::Vector2i(x, y));
                    // Add to tiles
                    tiles.push_back(currentTile);
                }
                // Add destination tile (red)
                else if (color == sf::Color::Red) {
                    Tile* tile = new DestinationTile(textureManager.getRoad_blank(), sf::Vector2i(x, y));
                    tiles.push_back(tile);
                    destinationTiles.push_back(tile);
                }
            }
        }
        // Map neighbours
        mapNeighbours(tiles);
        // Map lights
        mapLights(tiles, destinationTiles, textureManager);
    }
    
    return true;
}

void MapGenerator::getHouses(Houses& houses, Tiles& destinationTiles, TextureManager& textureManager) {
    for (Tile* t : destinationTiles) {
        houses.push_back(new House(textureManager.getHouse(), t));
    }
}

// Map all neighbours
void MapGenerator::mapNeighbours(Tiles &tiles) {
    for (Tile* t : tiles) {
        // Fetching possible positions
        int x = t->getTilePosition().x;
        int y = t->getTilePosition().y;
        vector<sf::Vector2i> neighbouringPositions;
        neighbouringPositions.push_back(sf::Vector2i(x + 1, y));
        neighbouringPositions.push_back(sf::Vector2i(x - 1, y));
        neighbouringPositions.push_back(sf::Vector2i(x, y + 1));
        neighbouringPositions.push_back(sf::Vector2i(x, y - 1));
        
        // Comparing positions to all the other
        for (Tile* compareTo : tiles) {
            // Comparing to all neigh. positions
            for (int i = 0; i < neighbouringPositions.size(); i++) {
                // Add neighbour and remove position from neighPos.
                if (compareTo->getTilePosition() == neighbouringPositions[i]) {
                    t->addNeighbour(compareTo);
                    // Removing
                    swap(neighbouringPositions[i], neighbouringPositions[neighbouringPositions.size()-1]);
                    neighbouringPositions.pop_back();
                }
            }
        }
    }
}

// Map lights
void MapGenerator::mapLights(Tiles &tiles, Tiles &destinationTiles, TextureManager& textureManager) {
    for (Tile* t : tiles) {
        // Add if four-way-crossing
        if (t->getNeighbours().size() > 3) {
            t->setTrafficLight(new TrafficLight(t, &textureManager.getTrafficLight_green(), &textureManager.getTrafficLight_red()));
        }
        // If three-way-crossing, only add if no destination tiles.
        else if (t->getNeighbours().size() == 3) {
            bool ok = true;
            for (Tile* neighbour : t->getNeighbours()) {
                if (tileInTiles(neighbour, destinationTiles)) {
                    ok = false;
                }
            }
            if (ok) {
                t->setTrafficLight(new TrafficLight(t, &textureManager.getTrafficLight_green(), &textureManager.getTrafficLight_red()));
            }
        }
    }
}

// Does tile exist in tiles?
bool MapGenerator::tileInTiles(Tile *tile, Tiles &tiles) {
    for (Tile* t : tiles) {
        if (t == tile) {
            return true;
        }
    }
    return false;
}