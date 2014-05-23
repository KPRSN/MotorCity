//
//  LightPole.cpp
//  MotorCity
//
//  Created by Karl Persson on 2013-12-18.
//  Copyright (c) 2013 Karl Persson. All rights reserved.
//

#include "LightPole.h"

LightPole::LightPole(sf::Vector2f position, sf::Texture* green, sf::Texture* red):
mState(false), mGreen(green), mRed(red) {
    // Setting figure
    mSprite.setTexture(*mRed);
    mSprite.setPosition(position);
}

void LightPole::setState(bool state) {
    mState = state;
    
    // Setting sprite
    if (state) {
        mSprite.setTexture(*mGreen);
    }
    else {
        mSprite.setTexture(*mRed);
    }
}

bool LightPole::getState() {
    return mState;
}

// Draw me!
void LightPole::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(mSprite);
}