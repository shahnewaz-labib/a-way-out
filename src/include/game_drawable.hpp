#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Game_Drawable
{
protected:
    float x, y;
    float width, height;
    sf::RenderWindow *window;

public:
    Game_Drawable(sf::RenderWindow *_win);
    virtual void draw() = 0;
};