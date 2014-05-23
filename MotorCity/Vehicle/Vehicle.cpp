//
//  Vehicle.cpp
//  MotorCity
//
//  Created by Karl Persson on 2013-12-10.
//  Copyright (c) 2013 Karl Persson. All rights reserved.
//

#include "Vehicle.h"

Vehicle::~Vehicle() {
    
}

// Block movement next update
void Vehicle::block() {
    mBlocked = true;
}

// Get bounding rect
sf::FloatRect Vehicle::getRect() const {
    return mSprite.getGlobalBounds();
}

// Get current direction
Tile::Direction Vehicle::getDirection() const {
    return mDirection;
}

// Signal collision with specific vehicle
// Am I responsible or not?
bool Vehicle::checkCollision(Vehicle* vehicle) {
    // One in front of the other?
    if (mDirection == Tile::NORTH && getCenterPosition().y > vehicle->getCenterPosition().y) {
        return true;
    }
    else if (mDirection == Tile::SOUTH && getCenterPosition().y < vehicle->getCenterPosition().y) {
        return true;
    }
    else if (mDirection == Tile::WEST && getCenterPosition().x > vehicle->getCenterPosition().x) {
        return true;
    }
    else if (mDirection == Tile::EAST && getCenterPosition().x < vehicle->getCenterPosition().x) {
        return true;
    }
    else return false;
}

// Is the route finished
bool Vehicle::isFinished() {
    return mFinished;
}

// Calculating route
// Current tile to destination
bool Vehicle::calculateRoute(Tile *destination) {
    // Current tile used when calculating
    // Not to mix with the vehicles actual current tile
    ATile* current;
    
    ATiles openList;     // Tiles considered for shortest path
    ATiles closedList;   // Tiles to not reconsider
    
    // Adding starting point
    openList.add(new ATile(mCurrentTile, destination));
    // Finding route
    do {
        // Get tile with lowest F
        current = openList.getLowestF();
        
        // Add to closed and remove from open
        closedList.add(current);
        openList.remove(current);
        
        // Destination reached?
        if (closedList.contains(destination)) {
            finilizeRoute(closedList);
            return true;
        }
        
        // Fetch and control current neighbours
        Tiles neighbours = current->getTile()->getNeighbours();
        for (Tile* t : neighbours) {
            // Ignore if already in closed
            if (closedList.contains(t)) {
                continue;
            }
            
            // Add if not in the open list
            // Otherwise it will already be considered
            if (!openList.contains(t)) {
                openList.add(new ATile(t, destination, current));
            }
        }
    } while (!openList.empty());
    // No path found
    return false;
}

// Finalizing route
void Vehicle::finilizeRoute(ATiles& closedList) {
    // Setting last tile and adding it to the route
    ATile* parent = closedList.getLastATile();
    mRoute.push_back(parent->getTile());
    
    // Following breadcrumbs/tile parents to the start
    while (parent != NULL) {
        mRoute.push_back(parent->getTile());
        parent = parent->getParent();
    }
}

// Clear the route
void Vehicle::clearRoute() {
    while (!mRoute.empty()) {
        mRoute.pop_back();
    }
}

// Move in specified direction
void Vehicle::move(Tile::Direction direction) {
    switch (direction) {
        case Tile::EAST:
            mSprite.move(mMaxSpeed, 0.0f);
            break;
        case Tile::WEST:
            mSprite.move(-mMaxSpeed, 0.0f);
            break;
        case Tile::SOUTH:
            mSprite.move(0.0f, mMaxSpeed);
            break;
        case Tile::NORTH:
            mSprite.move(0.0f, -mMaxSpeed);
            break;
        default:
            break;
    }
}

// Get center position of the vehicle
sf::Vector2f Vehicle::getCenterPosition() const {
    return mSprite.getPosition();
}

// Set center position of the vehicle
void Vehicle::setCenterPosition(sf::Vector2f position) {
    mSprite.setPosition(position);
}