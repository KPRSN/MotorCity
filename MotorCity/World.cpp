//
//  World.cpp
//  MotorCity
//
//  Created by Karl Persson on 2013-12-09.
//  Copyright (c) 2013 Karl Persson. All rights reserved.
//

#include "World.h"

World::World() {
    // Initializing textures
    mTextureManager = TextureManager();
    
    // Generating roads
    MapGenerator::getRoads(mTiles, mDestinationTiles, mTextureManager);
    // Generating houses
    MapGenerator::getHouses(mHouses, mDestinationTiles, mTextureManager);
    // Initializing random number generation
    mRandomEngine = default_random_engine(mRandomDevice());
    mRandomDestinationTile = uniform_int_distribution<int>(0, mDestinationTiles.size()-1);
    // One second spawn timer
    mSpawnTimer = 1.0f;
    
    // Spawning a random car
    spawnCar();
}

World::~World() {
    clear();
}

// Draw everything
void World::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    vector<TrafficLight*> lights;
    // Draw tiles
    for (Tile* t : mTiles) {
        t->draw(target, states);
        // Add lights
        TrafficLight* light = t->getTrafficLight();
        if (light != NULL) {
            lights.push_back(light);
        }
    }
    // Draw lights
    for (TrafficLight* l : lights) {
        l->draw(target, states);
    }
    // Draw vehicles
    for (Vehicle* v : mVehicles) {
        v->draw(target, states);
    }
    // Draw houses
    for (House* h : mHouses) {
        h->draw(target, states);
    }
}

// Update everything
void World::update() {
    updateTrafficLights();
    updateVehicles();
    
    // Spawn car yet?
    if (mClock.getElapsedTime().asSeconds() > mSpawnTimer) {
        spawnCar();
    }
}


// Add a vehicle
void World::addVehicle(Vehicle* vehicle) {
    mVehicles.push_back(vehicle);
}

// Generate car for random route
void World::spawnCar() {
    if (mDestinationTiles.size() > 1) {
        // Generating two random, but not equal, destinations
        Tile* start = mDestinationTiles[mRandomDestinationTile(mRandomEngine)];
        Tile* destination;
        do {
            destination = mDestinationTiles[mRandomDestinationTile(mRandomEngine)];
        } while (start == destination);
        // Add car
        mVehicles.push_back(new Car(mTextureManager.getCar(), start, destination));
        // Reset spawn timer
        mClock.restart();
    }
}

// Update traffic lights
void World::updateTrafficLights() {
    // Update traffic lights
    for (Tile* t : mTiles) {
        TrafficLight* light = t->getTrafficLight();
        if (light) {
            light->update();
        }
    }
}

// Update vehicles
void World::updateVehicles() {
    // Remove finished vehicles
    for (vector<Vehicle*>::iterator it = mVehicles.begin(); it != mVehicles.end(); ++it) {
        if ((*it)->isFinished()) {
            delete (*it);
            mVehicles.erase(it);
            it--;
        }
    }
    // Update vehicles
    for (Vehicle* v : mVehicles) {
        // Block crashed vehicle
        crashCheck(v);
        v->update();
    }
}

// Run a crash check for a specific vehicle
bool World::crashCheck(Vehicle *vehicle) {
    // Return true if a crash is found
    for (Vehicle* v : mVehicles) {
        // Check collission (excluding self)
        if (vehicle != v && vehicle->getRect().intersects(v->getRect())) {
            // Check who ran into who (tested cars fault: tested car will be blocked)
            if (vehicle->checkCollision(v) && !v->checkCollision(vehicle)) {
                vehicle->block();
                return true;
            }
        }
    }
    return false;
}

// Clear from all objects
void World::clear() {
    // Clear all houses
    while (!mHouses.empty()) {
        House* house = *mHouses.begin();
        mHouses.erase(mHouses.begin());
        delete house;
    }
    
    // Clear all tiles
    while (!mTiles.empty()) {
        Tile* tile = *mTiles.begin();
        mTiles.erase(mTiles.begin());
        delete tile;
    }
    
    // Clear destination tiles
    mDestinationTiles.clear();
    
    //Clear all vehicle
    while (!mVehicles.empty()) {
        Vehicle* vehicle = *mVehicles.begin();
        mVehicles.erase(mVehicles.begin());
        delete vehicle;
    }
}


