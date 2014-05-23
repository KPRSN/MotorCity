//
//  House.cpp
//  MotorCity
//
//  Created by Karl Persson on 2014-01-03.
//  Copyright (c) 2014 Karl Persson. All rights reserved.
//

#include "House.h"

// Constructor
House::House(sf::Texture& texture, Tile* tile):
mTile(tile) {
    mSprite.setTexture(texture);
    mSprite.setPosition(tile->getCenterPosition());
    mSprite.setOrigin(10, 10);
    
    // Fetching direction
    Tile::Direction dir = Tile::calculateDirection(tile->getTilePosition(), tile->getNeighbours()[0]->getTilePosition());
    // Rotating house
    switch (dir) {
        case Tile::NORTH:
            mSprite.setRotation(0.0f);
            break;
        case Tile::EAST:
            mSprite.setRotation(90.0f);
            break;
        case Tile::SOUTH:
            mSprite.setRotation(180.0f);
            break;
        case Tile::WEST:
            mSprite.setRotation(270.0f);
            break;
        default:
            break;
    }
}

// Destructor
House::~House() {
    
}

void House::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mSprite);
}