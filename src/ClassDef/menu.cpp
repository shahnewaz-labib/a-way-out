#include "../include/menu.hpp"

extern state currentState;

MainMenu::MainMenu(sf::RenderWindow *window,std::string titleString,float titlePos_y,sf::Vector2f buttonPos,int padding) {
    set(window, titleString, titlePos_y, buttonPos, padding);
}

Level_Select_Menu::Level_Select_Menu(sf::RenderWindow *window,std::string titleString,float titlePos_y,sf::Vector2f buttonPos,int padding) {
    set(window, titleString, titlePos_y, buttonPos, padding);
}


void Menu::set(sf::RenderWindow *window,std::string titleString,float titlePos_y,sf::Vector2f buttonPos,int padding) {
    this->window = window;
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

void Level_Select_Menu::addButtons(){
    Buttons.push_back(new Button(BackToMenu,window,"Menu"));
    Buttons.push_back(new Button(Random,window,"Dimension"));
    Buttons.push_back(new Button(Random,window,"Level"));
    Buttons.push_back(new Button(Random,window,"Random"));
}

void Menu::adjustTittle(sf::Vector2f pos,std::string titleString){
    title = sf::Text(titleString, sourceCode, 62);
    title.setFillColor(getTextColor());
    title.setLetterSpacing(0.75);
    auto tmp = title.getLocalBounds();
    title.setOrigin(tmp.width/2.0,tmp.height/2.0);
    title.setPosition(pos);
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

void Level_Select_Menu::action(){
    mousePos = sf::Mouse::getPosition(*window);
    for(auto btn:Buttons) {
        if(btn->checkHover(mousePos) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            switch (btn->getButtonType()) {
                case BackToMenu:
                    while(sf::Mouse::isButtonPressed(sf::Mouse::Left));
                    currentState = inMenu;
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
