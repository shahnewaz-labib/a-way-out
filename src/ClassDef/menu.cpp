#include "../include/menu.hpp"
#include "../include/game.hpp"
#include "../include/item.hpp"
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
    this->titlePos_y = titlePos_y;
    sourceCode.loadFromFile("Assets/SourceCodePro-SemiBoldItalic.ttf");
    liberationMono.loadFromFile("Assets/LiberationMono-Regular.ttf");
    adjustTittle(sf::Vector2f(window->getSize().x/2.0,titlePos_y),titleString);
    addButtons();
    adjustButtons(buttonPos - sf::Vector2f(0,Buttons[0]->getSize().y/2.0), padding);
}

void MainMenu::addButtons(){
    int padding = 15;
    Buttons.push_back(new Button(game,Exit,window,"Exit"));
    Buttons.push_back(new Button(game,About,window, "About"));
    Buttons.push_back(new Button(game,Level_Select,window, "Select Level"));
    Buttons.push_back(new Button(game,Play,window, "Play"));
    Items.push_back(new Item(window, sf::Vector2f(90.0, 45.0), "Assets/toggle.png", itemType::DayNight, sf::Vector2f(game->Width - padding - 45.0, game->Height - padding - 22.5)));
}


void Menu::adjustTittle(sf::Vector2f pos,std::string titleString,int size){
    title = sf::Text(titleString, sourceCode, size);
    title.setFillColor(game->getTextColor());
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
        btn->setTextColor(game->curTextCol);
        btn->setFontSize(40);
        btn->setLetterSpacing(.75);
        btn->fitBox();
        btn->setPosition(pos);
        pos.y -= btn->getSize().y + padding;
    }  
}

void Menu::draw() {

    window->clear(game->getBGCol());
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

    for(auto item:Items) {
        if(item->contains(mousePos) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            while(sf::Mouse::isButtonPressed(sf::Mouse::Left));
            game->toggleDayNight();
            item->setTextureRect(!game->day);
            title.setFillColor(game->getTextColor());
        }
    }
}



Menu::~Menu() {
    for(auto btn:Buttons)
        delete btn;
    for(auto item:Items) 
        delete item;
}

void MainMenu::setAboutPageText(){
    std::string t = " A Way Out is a puzzle game where the\n player has to get to an end point from\n a starting point following a path\n that fills the whole 2D grid,\n in technical terms, the player\n has to find a hamiltonian path\n when the cells of the grid are\n nodes of a graph.";
    adjustTittle(sf::Vector2f(window->getSize())/2.0f,t,20);

    Item backBtn = Item(window,sf::Vector2f(40,40),"Assets/back.png",Back,sf::Vector2f(50,50));
    window->draw(title);

    if(backBtn.contains(sf::Mouse::getPosition(*window))){
        backBtn.setTextureRect(1);
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            adjustTittle(sf::Vector2f(window->getSize().x/2.0,titlePos_y), "A Way Out",62);
            window->draw(title);
            game->setState(state::inMenu);
        }
    } else {
        backBtn.setTextureRect();
    }

    backBtn.draw();
}
