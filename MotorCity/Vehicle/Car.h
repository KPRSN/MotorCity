//
//  Car.h
//  MotorCity
//
//  Created by Karl Persson on 2013-12-10.
//  Copyright (c) 2013 Karl Persson. All rights reserved.
//

#ifndef __MotorCity__Car__
#define __MotorCity__Car__

#include <iostream>
#include "Vehicle.h"

// A driveable road vehicle
class Car : public Vehicle {
public:
    Car(sf::Texture& texture, Tile* startPosition, Tile* endPosition);
    ~Car();
    
    // Update vehicle position etc.
    virtual void update();

    // Draw me
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
private:
    // Set start position (spawn)
    void setStartPosition(Tile* start);
    // Update position
    void updatePosition();
    // Update sprite direction
    void updateSpriteDirection();
    // Advance one tile (aim for the next tile
    void nextTile();
    // Starting route
    void startRoute();
    // What to do when the route is finished
    void routeFinished();
    
    //TilePositioner::Direction mDirection;
    sf::Vector2f mNextCheckpoint;
};

#endif /* defined(__MotorCity__Car__) */