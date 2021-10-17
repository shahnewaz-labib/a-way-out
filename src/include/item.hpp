#pragma once
#include "game_drawable.hpp"

using namespace sf;

enum itemType { Reset,Solve,Back };

class Item : public Game_Drawable {
protected:
    RectangleShape boundary;
    Sprite sprite;
    Texture texture;
    Vector2f pos;
public:
    itemType Type;
    void setBasics(RenderWindow *window,Vector2f pos,std::string textureFile);
    Item(RenderWindow *window,Vector2f size,std::string textureFile,itemType T,Vector2f pos=Vector2f(0,0));
    void setTextureRect(bool hover=0);
    virtual void draw();
    void adjustSprite();
    virtual void setPosition(Vector2f pos);
    Item(){}
    bool contains(Vector2i pos);
};
