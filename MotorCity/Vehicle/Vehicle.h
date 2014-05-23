//
//  Vehicle.h
//  MotorCity
//
//  Created by Karl Persson on 2013-12-10.
//  Copyright (c) 2013 Karl Persson. All rights reserved.
//

#ifndef __MotorCity__Vehicle__
#define __MotorCity__Vehicle__

#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include "ATiles.h"
#include "TrafficLight.h"

// Vehicle base class
class Vehicle : sf::Drawable {
public:
    virtual ~Vehicle();
    
    // Block movement next update
    virtual void block();
    // Get bounding rect
    virtual sf::FloatRect getRect() const;
    // Get current direction
    virtual Tile::Direction getDirection() const;
    
    // Signal collision with specific vehicle (block this vehicle, or not?)
    virtual bool checkCollision(Vehicle* vehicle);
    // Is the route finished?
    virtual bool isFinished();
    
    // Update vehicle position etc.
    virtual void update() = 0;
    
    // Draw me!
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    
    
    
protected:
    // Calculate route using the A* algorithm
    // Current tile to destination
    bool calculateRoute(Tile* destination);
    // Finilize route
    void finilizeRoute(ATiles& closedList);
    // Clear route
    void clearRoute();
    // Move in specified direction
    void move(Tile::Direction direction);
    
    // Get center position of the vehicle
    sf::Vector2f getCenterPosition() const;
    // Set center position of the vehicle
    void setCenterPosition(sf::Vector2f position);
    
    // Sprite
    sf::Sprite mSprite;
    // Current tile
    Tile* mCurrentTile;
    // Next tile
    Tile* mNextTile;
    // Its travel route (starting at the end of the vector)
    Tiles mRoute;
    // Direction
    Tile::Direction mDirection;
    // Maximum speed
    float mMaxSpeed;
    // Movement blocked
    bool mBlocked;
    // Route finished
    bool mFinished;
    
    // Had a green light
    bool mGreenlit;
    // Current traffic light/intersection (if any)
    Tile* mCurrentIntersection;
};

#endif /* defined(__MotorCity__Vehicle__) */
