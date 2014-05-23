//
//  TrafficLight.cpp
//  MotorCity
//
//  Created by Karl Persson on 2013-12-18.
//  Copyright (c) 2013 Karl Persson. All rights reserved.
//

#include "TrafficLight.h"

TrafficLight::TrafficLight(Tile* tile, sf::Texture* green, sf::Texture* red):
mTile(tile), mCurrentIndex(0) {
    // Creating light poles
    if (tile->getNeighbours().size() > 2) {
        for (Tile* t : tile->getNeighbours()) {
            // Calculating values
            Tile::Direction direction = Tile::calculateDirection(t->getTilePosition(), tile->getTilePosition());
            mLightPoles.push_back(std::make_pair(LightPole(polePosition(direction), green, red), direction));
        }
    }
    // Set a green light
    nextPole();
}

// Get status on traffic lights for a specific direction
bool TrafficLight::getStatus(Tile::Direction direction) {
    // Returning state of specific light pole (true/green if none)
    for (auto n : mLightPoles) {
        if (n.second == direction) {
            return n.first.getState();
        }
    }
    return true;
}

// Update traffic light
void TrafficLight::update() {
    if (mClock.getElapsedTime().asSeconds() > 2) {
        // Set next pole
        nextPole();
        // Resetting timer
        mClock.restart();
    }
}

// Draw me!
void TrafficLight::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Drawing light poles
    for (auto n : mLightPoles) {
        n.first.draw(target, states);
    }
}

// Set next pole
void TrafficLight::nextPole() {
    // Setting current index to red
    mLightPoles[mCurrentIndex].first.setState(false);
    // Updating index
    mCurrentIndex = (mCurrentIndex + 1) % mLightPoles.size();
    // Setting new index to green
    mLightPoles[mCurrentIndex].first.setState(true);
}

// Calculate pole position
sf::Vector2f TrafficLight::polePosition(Tile::Direction direction) {
    sf::FloatRect rect = mTile->getGlobalBounds();
    float x, y;
    
    switch (direction) {
        case Tile::EAST:
            x = rect.left - 5;
            y = rect.top + rect.height;
            break;
        case Tile::SOUTH:
            x = rect.left - 5;
            y = rect.top - 12;
            break;
        case Tile::WEST:
            x = rect.left + rect.width;
            y = rect.top - 12;
            break;
        case Tile::NORTH:
            x = rect.left + rect.width;
            y = rect.top + rect.height;
            break;
        default:
            x = y = 0.0f;
            break;
    }
    return sf::Vector2f(x, y);
}