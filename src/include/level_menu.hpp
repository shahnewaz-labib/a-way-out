#pragma once
#include "../include/menu.hpp"

class Level_Select_Menu : public Menu {
    sf::Text currentTypeText;
    std::vector<TextBox*>tb;
    buttonType currentSelected;
    sf::Font ft;
public:
    Grid* GameGrid;
    Level_Select_Menu(sf::RenderWindow* window,std::string titleString,float titlePos,sf::Vector2f buttonPos,int padding);
    std::string getCurrentTypeString();
    void updateCurrentTypeText();
    void addButtons();
    void action();
    void adjustTextBox();
    void getTextInput(int ch);
    void draw();
    void turnOffExcept(int index);
    void updateDimension(int &N,int &M);
};
