//
//  DestinationTile.h
//  MotorCity
//
//  Created by Karl Persson on 2013-12-09.
//  Copyright (c) 2013 Karl Persson. All rights reserved.
//

#ifndef __MotorCity__DestinationTile__
#define __MotorCity__DestinationTile__

#include "Tile.h"

// Tile used for destination/starting point
class DestinationTile : public Tile {
public:
    DestinationTile(sf::Texture& texture, sf::Vector2i tilePosition);
    
    // Draw me!
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif /* defined(__MotorCity__DestinationTile__) */
