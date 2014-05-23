//
//  ATile.cpp
//  MotorCity
//
//  Created by Karl Persson on 2013-12-11.
//  Copyright (c) 2013 Karl Persson. All rights reserved.
//

#include "ATile.h"

// Constructor - starting position (no parent)
ATile::ATile(Tile* tile, Tile* destination):
mTile(tile), mDestination(destination), mParent(NULL), mG(0) {
    calculateH();
}

// Constructor - with parent
ATile::ATile(Tile* tile, Tile* destination, ATile* parent):
mTile(tile), mDestination(destination), mParent(parent) {
    mG = parent->getG() + 1;
    calculateH();
}

Tile* ATile::getTile() {
    return mTile;
}

ATile* ATile::getParent() {
    return mParent;
}

int ATile::getF() {
    return mG + mH;
}

int ATile::getG() {
    return mG;
}

int ATile::getH() {
    return mH;
}

// Calculate length from tile to destination (shortest path/bird/manhattan)
int ATile::calculateH() {
    // Calculating absolute distance between points
    return (abs(mTile->getTilePosition().x - mDestination->getTilePosition().y) +
            abs(mTile->getTilePosition().y - mDestination->getTilePosition().y));
}