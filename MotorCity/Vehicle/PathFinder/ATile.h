//
//  ATile.h
//  MotorCity
//
//  Created by Karl Persson on 2013-12-11.
//  Copyright (c) 2013 Karl Persson. All rights reserved.
//

#ifndef __MotorCity__ATile__
#define __MotorCity__ATile__

#include "Tile.h"

// Class used when storing tiles and info for the A* path finding algorithm
class ATile {
public:
    // Constructor - starting position (no parent)
    ATile(Tile* tile, Tile* destination);
    // Constructor - with parent
    ATile(Tile* tile, Tile* destination, ATile* parent);
    
    // Get stuff
    Tile* getTile();
    ATile* getParent();
    // G + H
    int getF();
    // Number of steps from starting point
    int getG();
    // Length to destination (manhattan/shortest/bird)
    int getH();
    
private:
    Tile* mTile;
    Tile* mDestination;
    ATile* mParent;
    int mG;
    int mH;
    
    // Calculate cost from tile to destination (Manhattan)
    int calculateH();
};

#endif /* defined(__MotorCity__ATile__) */
