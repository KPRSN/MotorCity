//
//  RoadTile.h
//  MotorCity
//
//  Created by Karl Persson on 2013-12-09.
//  Copyright (c) 2013 Karl Persson. All rights reserved.
//

#ifndef __MotorCity__RoadTile__
#define __MotorCity__RoadTile__

#include <set>
#include "Tile.h"
#include "TextureManager.h"

// Tile for road use
class RoadTile : public Tile {
public:
    typedef std::set<Tile::Direction> Directions;
    
    RoadTile(TextureManager* textureManager, sf::Vector2i tilePosition);
    
    // Draw me!
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    // Add a neihgbouring tile
    virtual void addNeighbour(Tile* neighbour);
    
private:
    TextureManager* mTextureManager;
    
    // Update texture and texture direction
    void updateTile();
    
    // Get all neigbouring directions
    Directions getNeighbouringDirections();
};

#endif /* defined(__MotorCity__RoadTile__) */
