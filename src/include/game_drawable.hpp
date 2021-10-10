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
    virtual void setFont(sf::Font&);
    virtual void setFontSize(unsigned int);
    virtual void setLetterSpacing(double);
    virtual void fitBox();
    virtual void checkHover(sf::Vector2i);
};