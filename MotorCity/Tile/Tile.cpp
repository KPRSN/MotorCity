//
//  Tile.cpp
//  MotorCity
//
//  Created by Karl Persson on 2013-12-09.
//  Copyright (c) 2013 Karl Persson. All rights reserved.
//

#include "Tile.h"

// Get/set position in tiles
sf::Vector2i Tile::getTilePosition() const {
    return mTilePosition;
}

// Set tile position
void Tile::setTilePosition(sf::Vector2i &position) {
    mTilePosition = position;
    mSprite.setPosition(tilePositionToPosition(position));
}

// Get global center position
sf::Vector2f Tile::getCenterPosition() const {
    return mSprite.getPosition();
}

// Get driving position (center) on the upcoming tile, based on direction
sf::Vector2f Tile::getDrivingPosition(Tile::Direction direction) const {
    sf::Vector2f position = getCenterPosition();
    
    switch (direction) {
        case Tile::EAST:
            position.y = (float)mSprite.getGlobalBounds().top + 3 * (mSprite.getGlobalBounds().height / 4);
            break;
        case Tile::WEST:
            position.y = (float)mSprite.getGlobalBounds().top + mSprite.getGlobalBounds().height / 4;
            break;
        case Tile::NORTH:
            position.x = (float)mSprite.getGlobalBounds().left + 3 * mSprite.getGlobalBounds().width / 4;
            break;
        case Tile::SOUTH:
            position.x = (float)mSprite.getGlobalBounds().left + (mSprite.getGlobalBounds().width / 4);
            break;
        default:
            break;
    }
    return position;
}

// Get global surrounding rect
sf::FloatRect Tile::getGlobalBounds() const {
    return mSprite.getGlobalBounds();
}

// Get/set traffic light
TrafficLight* Tile::getTrafficLight() {
    return mTrafficLight;
}

void Tile::setTrafficLight(TrafficLight* trafficLight) {
    mTrafficLight = trafficLight;
}

// Test if point/object is inside/on tile
bool Tile::isInside(const sf::Vector2f& point) {
    return mSprite.getGlobalBounds().contains(point);
}
bool Tile::isInside(const sf::Vector2i& point) {
    return mSprite.getGlobalBounds().contains((float)point.x, (float)point.y);
}
bool Tile::isInside(const sf::FloatRect& rect) {
    return mSprite.getGlobalBounds().intersects(rect);
}

// Get all neighbours
const Tiles& Tile::getNeighbours() {
    return mNeighbours;
}

// Add a neighbour
void Tile::addNeighbour(Tile *neighbour) {
    mNeighbours.push_back(neighbour);
}

// Get direction between two tiles
Tile::Direction Tile::calculateDirection(const sf::Vector2i &from, const sf::Vector2i &to) {
        int xDiff = to.x - from.x;
        int yDiff = to.y - from.y;
        
        // Move east
        if (xDiff > 0)      return EAST;
        // Move west
        else if (xDiff < 0) return WEST;
        // Move south
        else if (yDiff > 0) return SOUTH;
        // Move north
        else if (yDiff < 0) return NORTH;
        // No registered direction
        else                return NO_DIRECTION;
}

// Convert tile position to center position
sf::Vector2f Tile::tilePositionToPosition(sf::Vector2i tilePosition) {
    sf::Vector2f position;
    position.x = tilePosition.x * 20 + 10;
    position.y = tilePosition.y * 20 + 10;
    return position;
}