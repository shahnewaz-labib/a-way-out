#pragma once
#include "button.hpp"
#include "../include/text_input.hpp"
#include <SFML/Window/Event.hpp>

enum state {inMenu, inPlay, inAbout, inLevelSelect, endProgram};

class Menu {
protected:
    sf::RenderWindow* window;
    std::vector <Button*> Buttons;
    sf::Text title;
    sf::Font sourceCode, liberationMono;
    sf::Event ev;
    sf::Vector2i mousePos;
    //static sf::Color dayBGCol = sf::Color(216, 226, 233, 255), dayHoverColor = sf::Color(69, 72, 130, 255), dayTextColor = sf::Color::Black;
public:
//     Menu(sf::RenderWindow* window,std::string titleString,float titlePos,sf::Vector2f buttonPos,int padding);
    void set(sf::RenderWindow* window,std::string titleString,float titlePos,sf::Vector2f buttonPos,int padding);
    virtual void draw();
    virtual void addButtons() = 0;
    virtual void action() = 0;
    void adjustButtons(sf::Vector2f pos,int padding);
    void adjustTittle(sf::Vector2f pos,std::string titleString);
    virtual ~Menu();
};

class MainMenu : public Menu {
public:
    MainMenu(sf::RenderWindow* window,std::string titleString,float titlePos,sf::Vector2f buttonPos,int padding);
    void addButtons();
    void action();
};

class Level_Select_Menu : public Menu {
public:
    std::vector<TextBox*>tb;
    buttonType currentSelected = BackToMenu;
    sf::Font ft;
    Level_Select_Menu(sf::RenderWindow* window,std::string titleString,float titlePos,sf::Vector2f buttonPos,int padding);
    void addButtons();
    void action();
    void adjustTextBox();
    void getTextInput(sf::Event &event);
    void draw();
    void turnOffExcept(int index);
};;
