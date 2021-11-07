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
    bool day;
    void setState(state st);
    static sf::Color dayBGCol = sf::Color(216, 226, 233, 255), dayHoverColor = sf::Color(69, 72, 130, 255), dayTextColor = sf::Color::Black;
    static sf::Color nightBGCol = sf::Color(18, 18, 18, 255), nightHoverColor = sf::Color(27, 57, 251, 255), nightTextColor = sf::Color::White;
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


