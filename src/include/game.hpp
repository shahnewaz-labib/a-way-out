#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include <iostream>
#include "grid.hpp"
#include "node.hpp"
#include "menu.hpp"
#include "level_menu.hpp"
#include "text_input.hpp"

class Game {
    double Width,Height;
    state currentState=state::inMenu;
    int N=8,M=6;
    bool isWindowFocused = true;
    sf::RenderWindow *window;
    MainMenu *menu;
    Level_Select_Menu *level;
    Grid *grid;
    bool playButtonClicked;
    void setState(state st);
    bool day;
    static sf::Color dayBGCol, dayHoverCol, dayTextCol;
    static sf::Color nightBGCol, nightHoverCol, nightTextCol;
    sf::Color curBGCol, curHoverCol, curTextCol;
public:
    Game(double Width=500,double Height=700);
    void play();
    void quit();
    void toggleDayNight();
    friend MainMenu;
    friend Level_Select_Menu;
    friend Grid;
    friend Menu;
    sf::Color getBGCol();
    sf::Color getHoverColor();
    sf::Color getTextColor();
    sf::Color getInvertedTextColor();
    sf::Color getPathColor();
    sf::Color getHeadColor();
    sf::Color getVisNodeColor();
};


