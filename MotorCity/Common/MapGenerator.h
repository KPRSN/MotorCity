//
//  MapGenerator.h
//  MotorCity
//
//  Created by Karl Persson on 2013-12-09.
//  Copyright (c) 2013 Karl Persson. All rights reserved.
//

#ifndef __MotorCity__MapGenerator__
#define __MotorCity__MapGenerator__

#include <iostream>
#include <set>
#include <SFML/Graphics.hpp>

#include "RoadTile.h"
#include "DestinationTile.h"
#include "ResourcePath.hpp"
#include "TrafficLight.h"
#include "House.h"
#include "Common.h"

using namespace std;

#endif /* defined(__MotorCity__MapGenerator__) */

// Static functions for generating a map / loading map from file
class MapGenerator {
public:
    // Get roads from bitmap
    static bool getRoads(Tiles& tiles, Tiles& destinationTiles, TextureManager& textureManager);
    // Get houses from bitmap
    static void getHouses(Houses& houses, Tiles& destinationTiles, TextureManager& textureManager);
    
private:
    // Map all neighbours
    static void mapNeighbours(Tiles& tiles);
    // Map traffic lights
    static void mapLights(Tiles& tiles, Tiles& destinationTiles, TextureManager& textureManager);
    // Does tile exist in tiles?
    static bool tileInTiles(Tile* tile, Tiles& tiles);
};
