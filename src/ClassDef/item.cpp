#include "../include/item.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>

Item::Item(RenderWindow *window,Vector2f pos,Vector2f size,Texture T){
    this->window = window;
    boundary.setSize(size);
    boundary.setPosition(pos);
    boundary.setFillColor(Color::Transparent);
    sprite.setPosition(pos);
    texture = T;
    auto ts = Vector2f(T.getSize());
    auto bs = boundary.getSize();
    sprite.setScale(bs.x/ts.x,bs.y/(ts.y/2.0));
    sprite.setTexture(texture);
    setTextureRect();
}

void Item::setTextureRect(bool hover){
    auto ts = Vector2f(texture.getSize());
    if(hover){
        sprite.setTextureRect(IntRect(0,ts.y/2.0,ts.x,ts.y/2.0));
//         sprite.setTextureRect(IntRect(0,512,512,1024));
    }
    else{
//         sprite.setTextureRect(IntRect(0,ts.x,ts.x,ts.y));
        sprite.setTextureRect(IntRect(0,0,ts.x,ts.y/2.0));
    }
}

void Item::draw(){
//     window->draw(boundary);
    window->draw(sprite);
}
