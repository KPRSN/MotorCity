//
//  Main.cpp
//  MotorCity
//
//  Created on 2013-12-09.
//

#include <SFML/Graphics.hpp>
#include "World.h"

#include "ResourcePath.hpp"

int main(int, char const**) {
    // Window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Motor City");

    // Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());


    // Background
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "Background.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite background(texture);
    
    
    // Creating world
    World world;

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed : exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        // Clear window
        window.clear();
        // Update simulation
        world.update();
        // Draw background
        window.draw(background);
        // Draw simulation
        window.draw(world);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
