//
//  LightPole.h
//  MotorCity
//
//  Created by Karl Persson on 2013-12-18.
//  Copyright (c) 2013 Karl Persson. All rights reserved.
//

#ifndef __MotorCity__LightPole__
#define __MotorCity__LightPole__

#include <iostream>
#include <SFML/Graphics.hpp>

// Simple light pole
// To be controlled by TrafficLight
class LightPole : sf::Drawable {
public:
    LightPole(sf::Vector2f position, sf::Texture* green, sf::Texture* red);
    
    // Set/get state of the pole
    void setState(bool state);
    bool getState();
    
    // Draw me!
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    
private:
    bool mState;
    sf::Texture* mGreen;
    sf::Texture* mRed;
    
    sf::Sprite mSprite;
};

#endif /* defined(__MotorCity__LightPole__) */
