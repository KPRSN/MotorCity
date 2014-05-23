//
//  ATiles.cpp
//  MotorCity
//
//  Created by Karl Persson on 2013-12-12.
//  Copyright (c) 2013 Karl Persson. All rights reserved.
//

#include "ATiles.h"

// Constructor
ATiles::ATiles() {
    
}
// Destructor
ATiles::~ATiles() {
    // Clear all atiles
    clear();
}

// Add ATile
void ATiles::add(ATile* aTile) {
    mATiles.push_back(aTile);
}

// Remove ATile
void ATiles::remove(ATile* aTile) {
    mATiles.erase(std::remove(mATiles.begin(), mATiles.end(), aTile), mATiles.end());
}

// Does it contain the specified tile?
bool ATiles::contains(Tile* tile) {
    // Search
    for (ATile* t : mATiles) {
        if (t->getTile() == tile) {
            return true;
        }
    }
    return false;
}

// Is it empty
bool ATiles::empty() {
    return mATiles.empty();
}

// Get the tile with the lowest F-value
ATile* ATiles::getLowestF() {
    ATile* lowest = *mATiles.begin();
    int lowestF = lowest->getF();
    
    for (ATile* t : mATiles) {
        // Set new lowest-F ATile if f is lower
        int f = t->getF();
        if (f < lowestF) {
            lowest = t;
        }
    }
    return lowest;
}

// Get all tiles
std::vector<ATile*>& ATiles::getATiles() {
    return mATiles;
}

// Clear all of its ATiles
void ATiles::clear() {
    while (!mATiles.empty()) {
        ATile* aTile = *mATiles.begin();
        mATiles.erase(mATiles.begin());
        delete aTile;
    }
}

// Get last ATile
ATile* ATiles::getLastATile() {
    return *mATiles.rbegin();
}