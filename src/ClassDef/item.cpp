#include "../include/item.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>
#include <iostream>

void Item::setBasics(RenderWindow *window,Vector2f pos,std::string textureFile){
    this->window = window;
    this->pos = pos;
    texture.loadFromFile(textureFile);
}

void Item::adjustSprite(){ 
    auto ts = Vector2f(texture.getSize());
    auto bs = boundary.getSize();
    sprite.setTexture(texture);
    sprite.setScale(bs.x/ts.x,bs.y/(ts.y/2.0));
    sprite.setPosition(pos-bs/2.0f); // Not the center
    setTextureRect();
}

Item::Item(RenderWindow *window,Vector2f size,std::string textureFile,Vector2f pos){
    setBasics(window,pos,textureFile);
    boundary.setOrigin(size/2.0f);
    boundary.setSize(size);
    boundary.setPosition(pos);
    boundary.setFillColor(Color::Transparent);
    adjustSprite();
}

void Item::setTextureRect(bool hover){
    auto ts = Vector2f(texture.getSize());
    if(hover){
        sprite.setTextureRect(IntRect(0,ts.y/2.0,ts.x,ts.y/2.0));
    }
    else{
        sprite.setTextureRect(IntRect(0,0,ts.x,ts.y/2.0));
    }
}
void Item::setPosition(Vector2f pos){
    this->pos = pos;
    boundary.setPosition(pos);
    sprite.setPosition(pos - boundary.getSize()/2.0f);
}

bool Item::contains(Vector2f pos){
    return boundary.getGlobalBounds().contains(pos);
}

void Item::draw(){
    window->draw(boundary);
    window->draw(sprite);
}
