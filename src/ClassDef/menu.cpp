#include "../include/menu.hpp"

extern state currentState;

Menu::Menu(sf::RenderWindow* window) : window(window) {
    sourceCode.loadFromFile("Assets/SourceCodePro-SemiBoldItalic.ttf");
    liberationMono.loadFromFile("Assets/LiberationMono-Regular.ttf");
    title = sf::Text("A Way Out", sourceCode, 62);
    title.setFillColor(getTextColor());
    title.setPosition(150, 150);
    title.setLetterSpacing(0.75);
    menuItems.push_back(new Button(window, sf::Vector2f(110.0f, 50.0f), "Play", sf::Vector2f(255.0f, 470.0f)));
    menuItems.push_back(new Button(window, sf::Vector2f(110.0f, 50.0f), "Level Select", sf::Vector2f(170.0f, 525.0f)));
    menuItems.push_back(new Button(window, sf::Vector2f(110.0f, 50.0f), "About", sf::Vector2f(240.0f, 575.0f)));

    for(auto item : menuItems) {
        dynamic_cast<Button*>(item)->setFont(liberationMono);
        dynamic_cast<Button*>(item)->setFontSize(40);
        dynamic_cast<Button*>(item)->setLetterSpacing(0.75);
        dynamic_cast<Button*>(item)->fitBox();
    }  
}

void Menu::draw() {

    window->clear(getBGCol());
    window->draw(title);

    for(auto item:menuItems)
        item->draw();
}

void Menu::action() {
    mousePos = sf::Mouse::getPosition(*window);
    for(auto item:menuItems) {
        if(dynamic_cast<Button*>(item)->checkHover(mousePos) and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if(dynamic_cast<Button*>(item)->getText() == "Play") 
                currentState = inPlay;
            else if(dynamic_cast<Button*>(item)->getText() == "Level Select")
                currentState = inLevelSelect;
            else if(dynamic_cast<Button*>(item)->getText() == "About")
                currentState = inAbout;
        }
    }
}

Menu::~Menu() {
    for(auto item:menuItems)
        delete item;
}
