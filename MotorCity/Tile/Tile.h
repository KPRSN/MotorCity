//
//  Tile.h
//  MotorCity
//
//  Created by Karl Persson on 2013-12-09.
//  Copyright (c) 2013 Karl Persson. All rights reserved.
//

#ifndef __MotorCity__Tile__
#define __MotorCity__Tile__

#include <SFML/Graphics.hpp>
#include "Common.h"

class TrafficLight;

// Drivable tile
class Tile : public sf::Drawable {
public:
    // Directions
    enum Direction {NO_DIRECTION, NORTH, EAST, SOUTH, WEST};
    
    // Draw me!
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    
    // Get/Set position in tiles
    virtual sf::Vector2i getTilePosition() const;
    virtual void setTilePosition(sf::Vector2i& position);
    // Get global center position
    virtual sf::Vector2f getCenterPosition() const;
    // Get driving position (center) on the upcomping tile, based on direction
    virtual sf::Vector2f getDrivingPosition(Tile::Direction direction) const;
    // Get global surrounding rect
    virtual sf::FloatRect getGlobalBounds() const;
    // Get/Set traffic light
    virtual TrafficLight* getTrafficLight();
    virtual void setTrafficLight(TrafficLight* trafficLight);
    
    // Test if point/object is inside/on tile
    virtual bool isInside(const sf::Vector2f& point);
    virtual bool isInside(const sf::Vector2i& point);
    virtual bool isInside(const sf::FloatRect& rect);
    
    // Get all neighbours
    virtual const Tiles& getNeighbours();
    // Add a neihgbour
    virtual void addNeighbour(Tile* neighbour);
    
    // Static
    // Get direction between two tiles
    static Direction calculateDirection(const sf::Vector2i& from, const sf::Vector2i& to);
    
protected:
    // Position in tiles
    sf::Vector2i mTilePosition;
    // Sprite
    sf::Sprite mSprite;
    
    // Traffic light
    TrafficLight* mTrafficLight;
    
    // Neighbouring tiles
    Tiles mNeighbours;
    
    // Static
    // Convert tile position to center position
    static sf::Vector2f tilePositionToPosition(sf::Vector2i tilePosition);
};

#endif /* defined(__MotorCity__Tile__) */