//
//  ATiles.h
//  MotorCity
//
//  Created by Karl Persson on 2013-12-12.
//  Copyright (c) 2013 Karl Persson. All rights reserved.
//

#ifndef __MotorCity__ATiles__
#define __MotorCity__ATiles__

#include <iostream>
#include "ATile.h"

// Container for multiple ATiles.
// Used to aid the A* path finder
class ATiles {
public:
    ATiles();
    ~ATiles();
    
    // Add ATile
    void add(ATile* tile);
    // Remove ATile
    void remove(ATile* aTile);
    
    // Contains tile
    bool contains(Tile* tile);
    // Is it empty?
    bool empty();
    
    // Get tile with lowest F-value
    ATile* getLowestF();
    // Get all ATiles
    std::vector<ATile*>& getATiles();
    // Get last ATile
    ATile* getLastATile();
    
    // Clear all of its ATiles
    void clear();
    
private:
    std::vector<ATile*> mATiles;
};

#endif /* defined(__MotorCity__ATiles__) */
