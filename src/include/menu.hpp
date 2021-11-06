#pragma once
#include "button.hpp"
#include "text_input.hpp"
#include "grid.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <string>
class Game;

enum class state {inMenu, inPlay, inAbout, inLevelSelect, endProgram};

class Menu {
protected:
    Game *game;
    sf::RenderWindow* window;
    std::vector <Button*> Buttons;
    sf::Text title;
    sf::Font sourceCode, liberationMono;
    sf::Event ev;
    sf::Vector2i mousePos;
    int padding;
    //static sf::Color dayBGCol = sf::Color(216, 226, 233, 255), dayHoverColor = sf::Color(69, 72, 130, 255), dayTextColor = sf::Color::Black;
public:
//     Menu(sf::RenderWindow* window,std::string titleString,float titlePos,sf::Vector2f buttonPos,int padding);
    void set(Game *game,sf::RenderWindow* window,std::string titleString,float titlePos,sf::Vector2f buttonPos,int padding);
    virtual void draw();
    virtual void addButtons() = 0;
    virtual void action() = 0;
    void adjustButtons(sf::Vector2f pos,int padding);
    void adjustTittle(sf::Vector2f pos,std::string titleString);
    void centerText(sf::Text &txt,sf::Vector2f pos);
    virtual ~Menu();
};

class MainMenu : public Menu {
public:
    MainMenu(Game *game,sf::RenderWindow* window,std::string titleString,float titlePos,sf::Vector2f buttonPos,int padding);
    void addButtons();
    void action();
};
