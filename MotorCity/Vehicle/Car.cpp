//
//  Car.cpp
//  MotorCity
//
//  Created by Karl Persson on 2013-12-10.
//  Copyright (c) 2013 Karl Persson. All rights reserved.
//

#include "Car.h"

// Constructor with destination
Car::Car(sf::Texture& texture, Tile* startPosition, Tile* destination) {
    mMaxSpeed = 0.12f;
    mBlocked = false;
    mFinished = true;
    mGreenlit = false;
    mCurrentIntersection = NULL;
    
    // Set texture
    mSprite.setTexture(texture);
    // Set position/rotation origin
    mSprite.setOrigin(5.0f, 5.0f);
    // Set start position
    setStartPosition(startPosition);
    // Calculate and start route
    calculateRoute(destination);
    startRoute();
}

Car::~Car() {
    
}

// Update vehicle position etc.
void Car::update() {
    if (!isFinished()) {
        // Updating direction of the sprite
        updateSpriteDirection();
        // Update if not blocked
        if (!mBlocked) {
            updatePosition();
        }
        
        // Route is finished
        if (mDirection == Tile::NO_DIRECTION) {
            routeFinished();
        }
        mBlocked = false;
    }
}

// Draw me!
void Car::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(mSprite);
}

// Set start position (spawn)
void Car::setStartPosition(Tile* start) {
    // Set tile
    mCurrentTile = start;
    // Set the right start position
    if (start->getNeighbours().size() > 0) {
        Tile::Direction direction = Tile::calculateDirection(start->getTilePosition(), start->getNeighbours()[0]->getTilePosition());
        mSprite.setPosition(start->getDrivingPosition(direction));
    }
    else {
        mSprite.setPosition(start->getCenterPosition());
    }
}

// Update position
void Car::updatePosition() {
    // Did we arrive to the next position?
    switch (mDirection) {
        case Tile::EAST:
            if (getCenterPosition().x >= mNextCheckpoint.x) {
                nextTile();
            }
            break;
        case Tile::SOUTH:
            if (getCenterPosition().y >= mNextCheckpoint.y) {
                nextTile();
            }
            break;
        case Tile::WEST:
            if (getCenterPosition().x <= mNextCheckpoint.x) {
                nextTile();
            }
            break;
        case Tile::NORTH:
            if (getCenterPosition().y <= mNextCheckpoint.y) {
                nextTile();
            }
            break;
        default:
            break;
    }
    
    // Traffic light check
    TrafficLight* light = mNextTile->getTrafficLight();
    // Resetting greenlight (avoid stopping IN an intersection)
    if (mCurrentIntersection) {
        // Gone past intersection
        if (!mCurrentIntersection->isInside(getRect())) {
            mCurrentIntersection = NULL;
            mGreenlit = false;
        }
    }
    // Do not drive past a red light
    // (Drive if: no light, green light or not yet inside next tile)
    if (!light || light->getStatus(mDirection) || !mNextTile->isInside(getRect()) || mGreenlit) {
        // Set greenlight (avoid stopping IN an intersection)
        if (light && mNextTile->isInside(getRect()) && light->getStatus(mDirection)) {
            mCurrentIntersection = mNextTile;
            mGreenlit = true;
        }
        move(mDirection);
    }
}

// Update sprite direction
void Car::updateSpriteDirection() {
    switch (mDirection) {
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

// Advance one tile
void Car::nextTile() {
    // Next tile
    mCurrentTile = mRoute.back();
    mRoute.pop_back();
    mNextTile = mRoute.back();
    
    // Fetch direction
    mDirection = Tile::calculateDirection(mCurrentTile->getTilePosition(), mNextTile->getTilePosition());
    
    // Set next check point
    // Turning
    if (mRoute.size() > 2 && mDirection != Tile::calculateDirection(mNextTile->getTilePosition(), mRoute.at(mRoute.size()-2)->getTilePosition())) {
        mNextCheckpoint = mNextTile->getDrivingPosition(Tile::calculateDirection(mNextTile->getTilePosition(), mRoute.at(mRoute.size()-2)->getTilePosition()));
    }
    // Strait forward
    else {
        if (mDirection == Tile::EAST || mDirection == Tile::WEST) {
            mNextCheckpoint = mNextTile->getCenterPosition();
        }
        else {
            mNextCheckpoint = mNextTile->getCenterPosition();
        }
    }
}

// Start route
void Car::startRoute() {
    mFinished = false;
    mCurrentTile = mRoute.back();
    nextTile();
}

// What to do when the route is finished?
void Car::routeFinished() {
    // Clear the route
    clearRoute();
    mFinished = true;
}










