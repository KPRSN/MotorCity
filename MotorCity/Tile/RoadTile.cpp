//
//  RoadTile.cpp
//  MotorCity
//
//  Created by Karl Persson on 2013-12-09.
//  Copyright (c) 2013 Karl Persson. All rights reserved.
//

#include "RoadTile.h"

// Constructor
RoadTile::RoadTile(TextureManager* textureManager, sf::Vector2i tilePosition):
mTextureManager(textureManager) {
    mTrafficLight = NULL;
    
    // Setting position
    setTilePosition(tilePosition);
    
    // Setting rotational/positional origin
    mSprite.setOrigin(10.0f, 10.0f);
    
    // Update tile texture
    updateTile();
}

// Draw me!
void RoadTile::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(mSprite);
}

// Add a neighbouring tile
void RoadTile::addNeighbour(Tile *neighbour) {
    Tile::addNeighbour(neighbour);
    
    // Updating tile texture/direction
    updateTile();
}

// Update texture and texture direction
void RoadTile::updateTile() {
    Directions dir = getNeighbouringDirections();
    int size = dir.size();
    // Find which directions exist
    bool east, west, south, north = false;
    east = (std::find(dir.begin(), dir.end(), Tile::EAST) != dir.end());
    south = (std::find(dir.begin(), dir.end(), Tile::SOUTH) != dir.end());
    west = (std::find(dir.begin(), dir.end(), Tile::WEST) != dir.end());
    north = (std::find(dir.begin(), dir.end(), Tile::NORTH) != dir.end());
    
    // Rotating
    if (size == 2) {
        // Strait
        if ((east && west) || (south && north)) {
            mSprite.setTexture(mTextureManager->getRoad_strait());
            if (south || north) mSprite.setRotation(90.0f);
            else mSprite.setRotation(0.0f);
        }
        // Turn
        else {
            mSprite.setTexture(mTextureManager->getRoad_turn());
            if (west && north) mSprite.setRotation(90.0f);
            else if (north && east) mSprite.setRotation(180.0f);
            else if (east && south) mSprite.setRotation(270.0f);
            else mSprite.setRotation(0.0f);
        }
    }
    // Three-way
    else if (size == 3) {
        mSprite.setTexture(mTextureManager->getRoad_threeWay());
        if (north && west && south) mSprite.setRotation(90.0f);
        else if (east && north && west) mSprite.setRotation(180.0f);
        else if (south && east && north) mSprite.setRotation(270.0f);
        else mSprite.setRotation(0.0f);
    }
    // Four-way
    else if (size == 4) {
        mSprite.setTexture(mTextureManager->getRoad_fourWay());
    }
    // Dead end
    else {
        mSprite.setTexture(mTextureManager->getRoad_blank());
        mSprite.setRotation(0.0f);
    }
}

// Get all neighbouring directions
RoadTile::Directions RoadTile::getNeighbouringDirections() {
    Directions dir;
    for (Tile* t : getNeighbours()) {
        dir.insert(Tile::calculateDirection(getTilePosition(), t->getTilePosition()));
    }
    return dir;
}





