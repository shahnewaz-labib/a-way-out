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
    bool playButtonClicked, day;
    void setState(state st);
    static sf::Color dayBGCol, dayHoverColor, dayTextColor;
    static sf::Color nightBGCol, nightHoverColor, nightTextColor;
    sf::Color curBGCol, curHoverCol, curTextColor;
public:
    Game(double Width=500,double Height=700);
    void play();
    void quit();
    void toggleDayNight();
    friend MainMenu;
    friend Level_Select_Menu;
    friend Grid;
};


