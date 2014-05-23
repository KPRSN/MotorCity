//
//  TextureManager.h
//  MotorCity
//
//  Created by Karl Persson on 2014-01-01.
//  Copyright (c) 2014 Karl Persson. All rights reserved.
//

#ifndef __MotorCity__TextureManager__
#define __MotorCity__TextureManager__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

// Keeping track of textures for roads, vehicles etc.
class TextureManager {
public:
    typedef std::vector<sf::Texture> Textures;
    
    TextureManager();
    ~TextureManager();
    
    // Get car texture
    sf::Texture& getCar();
    
    // Get house texture
    sf::Texture& getHouse();
    
    // Get traffic light textures
    sf::Texture& getTrafficLight_green();
    sf::Texture& getTrafficLight_red();
    
    // Get road textures
    sf::Texture& getRoad_blank();
    sf::Texture& getRoad_strait();
    sf::Texture& getRoad_turn();
    sf::Texture& getRoad_threeWay();
    sf::Texture& getRoad_fourWay();
    
private:
    Textures mCarTextures;
    
    sf::Texture mHouse;
    
    sf::Texture mTrafficLight_green;
    sf::Texture mTrafficLight_red;
    
    sf::Texture mRoadTile_blank;
    sf::Texture mRoadTile_strait;
    sf::Texture mRoadTile_turn;
    sf::Texture mRoadTile_threeWay;
    sf::Texture mRoadTile_fourWay;
};

#endif /* defined(__MotorCity__TextureManager__) */
