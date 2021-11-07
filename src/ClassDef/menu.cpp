#include "../include/menu.hpp"
#include "../include/game.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cstdlib>

extern state currentState;

MainMenu::MainMenu(Game *game,sf::RenderWindow *window,std::string titleString,float titlePos_y,sf::Vector2f buttonPos,int padding) {
    set(game,window, titleString, titlePos_y, buttonPos, padding);
}

void Menu::set(Game *game,sf::RenderWindow *window,std::string titleString,float titlePos_y,sf::Vector2f buttonPos,int padding) {
    this->window = window;
    this->padding = padding;
    this->game = game;
    sourceCode.loadFromFile("Assets/SourceCodePro-SemiBoldItalic.ttf");
    liberationMono.loadFromFile("Assets/LiberationMono-Regular.ttf");
    adjustTittle(sf::Vector2f(window->getSize().x/2.0,titlePos_y),titleString);
    addButtons();
    adjustButtons(buttonPos - sf::Vector2f(0,Buttons[0]->getSize().y/2.0), padding);
}

void MainMenu::addButtons(){
    int padding = 200;
    Buttons.push_back(new Button(Exit,window,"Exit"));
    Buttons.push_back(new Button(About,window, "About"));
    Buttons.push_back(new Button(Level_Select,window, "Select Level"));
    Buttons.push_back(new Button(Play,window, "Play"));
    Items.push_back(new Item(window, sf::Vector2f(100.0, 50.0), "Assets/toggle.png", itemType::DayNight, sf::Vector2f(game->Width - padding - 30.0, game->Height - padding - 15.0)));
}


void Menu::adjustTittle(sf::Vector2f pos,std::string titleString){
    title = sf::Text(titleString, sourceCode, 62);
    title.setFillColor(getTextColor());
    title.setLetterSpacing(0.75);
    centerText(title, pos);
}

void Menu::centerText(sf::Text &txt, sf::Vector2f pos){
    auto tmp = txt.getLocalBounds();
    txt.setOrigin(tmp.left+tmp.width/2.0,tmp.top+tmp.height/2.0);
    txt.setPosition(pos);
}

void Menu::adjustButtons(sf::Vector2f pos,int padding){
    for(auto btn : Buttons) {
        btn->setFont(liberationMono);
        btn->setFontSize(40);
        btn->setLetterSpacing(.75);
        btn->fitBox();
        btn->setPosition(pos);
        pos.y -= btn->getSize().y + padding;
    }  
}

void Menu::draw() {

    window->clear(getBGCol());
    window->draw(title);

    for(auto btn:Buttons)
        btn->draw();

    for(auto item:Items)
        item->draw();
}

void MainMenu::action() {
    mousePos = sf::Mouse::getPosition(*window);
    for(auto btn:Buttons) {
        if(btn->checkHover(mousePos) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            switch (btn->getButtonType()) {
                case Play:
                    game->playButtonClicked = 1;
                    game->setState(state::inPlay);
                    break;
                case Level_Select:
                    game->setState(state::inLevelSelect);
                    break;
                case About:
                    game->setState(state::inAbout);
                    break;
                case Exit:
                    game->setState(state::endProgram);
                    break;
                default:
                    break;
            }
        }
    }
}



Menu::~Menu() {
    for(auto btn:Buttons)
        delete btn;
}
