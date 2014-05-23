//
//  DestinationTile.cpp
//  MotorCity
//
//  Created by Karl Persson on 2013-12-09.
//  Copyright (c) 2013 Karl Persson. All rights reserved.
//

#include "DestinationTile.h"

// Constructor
DestinationTile::DestinationTile(sf::Texture& texture, sf::Vector2i tilePosition) {
    mTrafficLight = NULL;
    
    // Setting texture
    mSprite.setTexture(texture);
    
    // Setting tile position
    setTilePosition(tilePosition);
    
    // Rotational/positional origin
    mSprite.setOrigin(10.0f, 10.0f);
}

// Draw me! (won't draw anything)
void DestinationTile::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(mSprite);
}