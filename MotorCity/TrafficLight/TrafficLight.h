//
//  TrafficLight.h
//  MotorCity
//
//  Created by Karl Persson on 2013-12-18.
//  Copyright (c) 2013 Karl Persson. All rights reserved.
//

#ifndef __MotorCity__TrafficLight__
#define __MotorCity__TrafficLight__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "LightPole.h"
#include "Tile.h"

// A traffic light, to be used in crossings
class TrafficLight : sf::Drawable {
public:
    typedef std::vector<std::pair<LightPole, Tile::Direction> > LightPoles;
    
    // Constructor
    TrafficLight(Tile* tile, sf::Texture* green, sf::Texture* red);
    
    // Get status on traffic lights for a specific direction
    bool getStatus(Tile::Direction direction);
    // Get tile
    Tile* getTile();
    
    // Update traffic light
    void update();
    
    // Draw traffic light
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
private:
    LightPoles mLightPoles;
    Tile* mTile;
    sf::Clock mClock;
    int mCurrentIndex;
    
    // Set next light pole
    void nextPole();
    
    // Calculate pole position
    sf::Vector2f polePosition(Tile::Direction direction);
};

#endif /* defined(__MotorCity__TrafficLight__) */
