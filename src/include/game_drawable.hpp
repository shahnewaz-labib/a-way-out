#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
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
    Game_Drawable(){}
    void getBoundary(sf::Vector2f pos,sf::Vector2f size);
    virtual void draw() = 0;
    virtual ~Game_Drawable(){}
};
