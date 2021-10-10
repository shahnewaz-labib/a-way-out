#pragma once
#include "button.hpp"

enum state {inMenu, inPlay, inAbout, inLevelSelect};

class Menu {
private:
    sf::RenderWindow* window;
    std::vector <Game_Drawable*> menuItems;
    sf::Text title;
    sf::Font sourceCode, liberationMono;
    sf::Event ev;
    sf::Vector2i mousePos;
    //static sf::Color dayBGCol = sf::Color(216, 226, 233, 255), dayHoverColor = sf::Color(69, 72, 130, 255), dayTextColor = sf::Color::Black;
public:
    Menu(sf::RenderWindow* window);
    void draw();
    void action();
    ~Menu();
};
