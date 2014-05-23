//
//  World.h
//  MotorCity
//
//  Created by Karl Persson on 2013-12-09.
//  Copyright (c) 2013 Karl Persson. All rights reserved.
//

#ifndef __MotorCity__World__
#define __MotorCity__World__

#include <iostream>
#include <SFML/Graphics.hpp>
#include <set>
#include <random>

#include "MapGenerator.h"
#include "Car.h"

using namespace std;

// The main class for handling all significant objects and traffic mechanics
class World : public sf::Drawable {
public:
    World();
    ~World();
    
    // Draw everything
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    // Update everything
    void update();
    
private:
    // Texture manager
    TextureManager mTextureManager;
    
    Tiles mTiles;
    Tiles mDestinationTiles;
    Vehicles mVehicles;
    Houses mHouses;
    
    // Vehicle spawn timer objects
    sf::Clock mClock;
    float mSpawnTimer;
    
    // Random number generator
    random_device mRandomDevice;
    default_random_engine mRandomEngine;
    uniform_int_distribution<int> mRandomDestinationTile;
    
    // Add a vehicle
    void addVehicle(Vehicle* vehicle);
    // Generate car for random route
    void spawnCar();
    
    // Update traffic lights
    void updateTrafficLights();
    // Update vehicles
    void updateVehicles();
    // Run a crash check for a specific vehicle
    bool crashCheck(Vehicle* vehicle);
    
    // Clear from all objects
    void clear();
};

#endif /* defined(__MotorCity__World__) */
