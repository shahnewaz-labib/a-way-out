#include "../include/level_menu.hpp"
extern state currentState;


Level_Select_Menu::Level_Select_Menu(sf::RenderWindow *window,std::string titleString,float titlePos_y,sf::Vector2f buttonPos,int padding) {
    set(window, titleString, titlePos_y, buttonPos, padding);
    ft.loadFromFile("Assets/SourceCodePro-SemiBoldItalic.ttf");
    currentTypeText.setFont(sourceCode);
    currentTypeText.setCharacterSize(30);
    currentTypeText.setString("Current Type : "+getCurrentTypeString());
    
    sf::Vector2f pos = title.getPosition();
    pos.y += title.getLocalBounds().height/2.0 + padding*3;
    centerText(currentTypeText, pos);

    adjustTextBox();
}

void Level_Select_Menu::adjustTextBox(){
    int padding = 10;
    int chrSize = 33;

    sf::Vector2f btnPos = Buttons[2]->getPosition();
    sf::Vector2f pos = btnPos + sf::Vector2f(Buttons[2]->getSize().x/2.0 + padding,-Buttons[2]->getSize().y/2.0);
    tb.push_back( new TextBox(ft, pos, chrSize, sf::Color::White, 4,1,100, 0) );
    
    float diff = Buttons[2]->getSize().y-tb[0]->getSize().y;
    if(diff<0) diff = 0;
    pos += sf::Vector2f(0,diff/2.0);
    tb[0]->setPosition(pos);

    tb[0]->setText("1");

    btnPos = Buttons[1]->getPosition();
    pos = btnPos + sf::Vector2f(Buttons[1]->getSize().x/2.0 + padding,-Buttons[2]->getSize().y/2.0+diff/2.0);

    tb.push_back( new TextBox(ft,pos,chrSize,sf::Color::White,3,5,12,0) );
    tb[1]->setText("6");

    pos += sf::Vector2f(tb[1]->getSize().x+padding,0);
    tb.push_back( new TextBox(ft,pos,chrSize,sf::Color::White,3,5,12,0) ) ;
    tb[2]->setText("8");
}

void Level_Select_Menu::draw(){
    Menu::draw();
    for(int i=0;i<tb.size();i++){
        tb[i]->drawTo(*window);
    }
    window->draw(currentTypeText);
}

void Level_Select_Menu::turnOffExcept(int index){
    for(int i=0;i<tb.size();i++){
        if(i!=index){
            tb[i]->selected(0);
            tb[i]->getValue();
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

std::string Level_Select_Menu::getCurrentTypeString(){
    switch (currentSelected) {
        case Dimension:
            return "Dimension";
        case Level:
            return "Level";
        default:
            return "Random";
    }
}

void Level_Select_Menu::action(){
    mousePos = sf::Mouse::getPosition(*window);
    for(auto btn:Buttons) {
        if(btn->checkHover(mousePos) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            switch (btn->getButtonType()) {
                case BackToMenu:
                    while(sf::Mouse::isButtonPressed(sf::Mouse::Left));
                    for(auto &i:tb) i->getValue(); // rectification
                    currentState = inMenu;
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

    updateCurrentTypeText();
}


void Level_Select_Menu::addButtons(){
    Buttons.push_back(new Button(BackToMenu,window,"Menu"));
    Buttons.push_back(new Button(Dimension,window,"Dimension"));
    Buttons.push_back(new Button(Level,window,"Level"));
    Buttons.push_back(new Button(Random,window,"Random"));
}


void Level_Select_Menu::updateCurrentTypeText(){
    currentTypeText.setString("Current Type : "+getCurrentTypeString());
    centerText(currentTypeText, currentTypeText.getPosition());
}


void Level_Select_Menu::updateDimension(int &N, int &M){
    if(currentSelected == Dimension){
        N = tb[1]->getValue();
        M = tb[2]->getValue();
    }
    else if(currentSelected == Level){
        M = std::min(12,tb[0]->getValue()+4);
        N = M + 2; 
    }
    else if(currentSelected == Random){
        N = rand() % 7 + 5;  
        M = rand() % 7 + 5;
    }
}
