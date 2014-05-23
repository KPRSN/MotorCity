//
//  House.h
//  MotorCity
//
//  Created by Karl Persson on 2014-01-03.
//  Copyright (c) 2014 Karl Persson. All rights reserved.
//

#ifndef __MotorCity__House__
#define __MotorCity__House__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Tile.h"

// Drawable house for destination
class House : public sf::Drawable {
public:
    House(sf::Texture& texture, Tile* tile);
    ~House();
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
private:
    sf::Sprite mSprite;
    
    Tile* mTile;
};

#endif /* defined(__MotorCity__House__) */