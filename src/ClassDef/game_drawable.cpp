#include "../include/game_drawable.hpp"


Game_Drawable::Game_Drawable(sf::RenderWindow *_win) : window(_win) {}

void Game_Drawable::getBoundary(sf::Vector2f pos, sf::Vector2f size){
    x = pos.x;
    y = pos.y;
    width = size.x;
    height = size.y;
}
