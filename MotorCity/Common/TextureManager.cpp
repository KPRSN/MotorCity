//
//  TextureManager.cpp
//  MotorCity
//
//  Created by Karl Persson on 2014-01-01.
//  Copyright (c) 2014 Karl Persson. All rights reserved.
//

#include "TextureManager.h"

TextureManager::TextureManager() {
    // Init random
    srand(time(NULL));
    
    // Load car textures
    for (std::string path : carPaths()) {
        // Create and load texture
        mCarTextures.push_back(sf::Texture());
        (*mCarTextures.rbegin()).loadFromFile(resourcePath() + path);
    }
    
    // Loading house texture
    mHouse.loadFromFile(resourcePath() + "House.png");
    
    // Loading traffic light texture
    mTrafficLight_red.loadFromFile(resourcePath() + "TrafficLight_Red2.png");
    mTrafficLight_green.loadFromFile(resourcePath() + "TrafficLight_Green2.png");
    
    // Load roads
    mRoadTile_blank.loadFromFile(resourcePath() + "Roads/RoadTile_Blank.png");
    mRoadTile_strait.loadFromFile(resourcePath() + "Roads/RoadTile_Strait.png");
    mRoadTile_turn.loadFromFile(resourcePath() + "Roads/RoadTile_Turn.png");
    mRoadTile_threeWay.loadFromFile(resourcePath() + "Roads/RoadTile_ThreeWay.png");
    mRoadTile_fourWay.loadFromFile(resourcePath() + "Roads/RoadTile_FourWay.png");
}

TextureManager::~TextureManager() {
    
}

// Get car texture
sf::Texture& TextureManager::getCar() {
    return mCarTextures[rand() % mCarTextures.size()];
}

// Get house texture
sf::Texture& TextureManager::getHouse() {
    return mHouse;
}

// Get traffic light textures
sf::Texture& TextureManager::getTrafficLight_green() {
    return mTrafficLight_green;
}
sf::Texture& TextureManager::getTrafficLight_red() {
    return mTrafficLight_red;
}

// Get road textures
sf::Texture& TextureManager::getRoad_blank() {
    return mRoadTile_blank;
}
sf::Texture& TextureManager::getRoad_strait() {
    return mRoadTile_strait;
}
sf::Texture& TextureManager::getRoad_turn() {
    return mRoadTile_turn;
}
sf::Texture& TextureManager::getRoad_threeWay() {
    return mRoadTile_threeWay;
}
sf::Texture& TextureManager::getRoad_fourWay() {
    return mRoadTile_fourWay;
}