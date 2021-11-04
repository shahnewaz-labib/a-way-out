#include "../include/menu.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

extern state currentState;

MainMenu::MainMenu(sf::RenderWindow *window,std::string titleString,float titlePos_y,sf::Vector2f buttonPos,int padding) {
    set(window, titleString, titlePos_y, buttonPos, padding);
}



void Menu::set(sf::RenderWindow *window,std::string titleString,float titlePos_y,sf::Vector2f buttonPos,int padding) {
    this->window = window;
    this->padding = padding;
    sourceCode.loadFromFile("Assets/SourceCodePro-SemiBoldItalic.ttf");
    liberationMono.loadFromFile("Assets/LiberationMono-Regular.ttf");
    adjustTittle(sf::Vector2f(window->getSize().x/2.0,titlePos_y),titleString);
    addButtons();
    adjustButtons(buttonPos - sf::Vector2f(0,Buttons[0]->getSize().y/2.0), padding);
}

void MainMenu::addButtons(){
    Buttons.push_back(new Button(Exit,window,"Exit"));
    Buttons.push_back(new Button(About,window, "About"));
    Buttons.push_back(new Button(Level_Select,window, "Select Level"));
    Buttons.push_back(new Button(Play,window, "Play"));
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
}

void MainMenu::action() {
    mousePos = sf::Mouse::getPosition(*window);
    for(auto btn:Buttons) {
        if(btn->checkHover(mousePos) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            switch (btn->getButtonType()) {
                case Play:
                    extern bool playButtonClicked;
                    playButtonClicked = 1;
                    currentState = inPlay; break;
                case Level_Select:
                    currentState = inLevelSelect; break;
                case About:
                    currentState = inAbout; break;
                case Exit:
                    currentState = endProgram; break;
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
