#include "../include/menu.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

extern state currentState;

MainMenu::MainMenu(sf::RenderWindow *window,std::string titleString,float titlePos_y,sf::Vector2f buttonPos,int padding) {
    set(window, titleString, titlePos_y, buttonPos, padding);
}

Level_Select_Menu::Level_Select_Menu(sf::RenderWindow *window,std::string titleString,float titlePos_y,sf::Vector2f buttonPos,int padding) {
    set(window, titleString, titlePos_y, buttonPos, padding);
    ft.loadFromFile("Assets/SourceCodePro-SemiBoldItalic.ttf");
    adjustTextBox();
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
    Buttons.push_back(new Button(Dimension,window,"Dimension"));
    Buttons.push_back(new Button(LevelBtn,window,"Level"));
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
                    currentSelected = BackToMenu;
                    break;
                 default:
                    currentSelected = btn->getButtonType();
                    break;
            }
        }
    }

    for(int i=0;i<tb.size();i++){
        if(tb[i]->contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            tb[i]->selected(1);
            turnOffExcept(i);
            return;
        }
    }
}

Menu::~Menu() {
    for(auto btn:Buttons)
        delete btn;
}

void Level_Select_Menu::adjustTextBox(){
    int padding = 10;
    int chrSize = 33;

    sf::Vector2f btnPos = Buttons[2]->getPosition();
    sf::Vector2f pos = btnPos + sf::Vector2f(Buttons[2]->getSize().x/2.0 + padding,-Buttons[2]->getSize().y/2.0);
    tb.push_back( new TextBox(Level,ft, pos, chrSize, sf::Color::White, 4,1,100, 0) );
    
    float diff = Buttons[2]->getSize().y-tb[0]->getSize().y;
    if(diff<0) diff = 0;
    pos += sf::Vector2f(0,diff/2.0);
    tb[0]->setPosition(pos);

    tb[0]->setText("1");

    btnPos = Buttons[1]->getPosition();
    pos = btnPos + sf::Vector2f(Buttons[1]->getSize().x/2.0 + padding,-Buttons[2]->getSize().y/2.0+diff/2.0);

    tb.push_back( new TextBox(Dim1,ft,pos,chrSize,sf::Color::White,3,5,12,0) );
    tb[1]->setText("6");

    pos += sf::Vector2f(tb[1]->getSize().x+padding,0);
    tb.push_back( new TextBox(Dim2,ft,pos,chrSize,sf::Color::White,3,5,12,0) ) ;
    tb[2]->setText("8");
}

void Level_Select_Menu::draw(){
    Menu::draw();
    for(int i=0;i<tb.size();i++){
        tb[i]->drawTo(*window);
    }
}

void Level_Select_Menu::turnOffExcept(int index){
    for(int i=0;i<tb.size();i++){
        if(i!=index){
            tb[i]->selected(0);
        }
    }
}

void Level_Select_Menu::getTextInput(int ch){
    for(int i=0;i<tb.size();i++){
        if(tb[i]->isOn()){
            tb[i]->typedOn(ch);
        }
    }
}
