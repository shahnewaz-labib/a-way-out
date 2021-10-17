#pragma once
#include "game_drawable.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

using namespace sf;

class Item : public Game_Drawable {
protected:
    RectangleShape boundary;
    Sprite sprite;
    Texture texture;
    Vector2f pos;
public:
    void setBasics(RenderWindow *window,Vector2f pos,std::string textureFile);
    Item(RenderWindow *window,Vector2f size,std::string textureFile,Vector2f pos=Vector2f(0,0));
    void setTextureRect(bool hover=0);
    virtual void draw();
    void adjustSprite();
    virtual void setPosition(Vector2f pos);
    Item(){}
    bool contains(Vector2f pos);
};
