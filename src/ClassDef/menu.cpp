#include "../include/menu.hpp"
#include <SFML/System/Vector2.hpp>

extern state currentState;

Menu::Menu(sf::RenderWindow* window) : window(window) {
    sourceCode.loadFromFile("Assets/SourceCodePro-SemiBoldItalic.ttf");
    liberationMono.loadFromFile("Assets/LiberationMono-Regular.ttf");
    int wx = window->getSize().x;
    int wy = window->getSize().y;
    int padding = 15;

    title = sf::Text("A Way Out", sourceCode, 62);
    title.setFillColor(getTextColor());
    title.setLetterSpacing(0.75);
    auto tmp = title.getLocalBounds();
    title.setOrigin(tmp.width/2.0,tmp.height/2.0);
    title.setPosition(wx/2.0, 150);

    menuButtons.push_back(new Button(Exit,window,"Exit"));
    menuButtons.push_back(new Button(About,window, "About"));
    menuButtons.push_back(new Button(Level_Select,window, "Select Level"));
    menuButtons.push_back(new Button(Play,window, "Play"));

    sf::Vector2f pos = sf::Vector2f(wx/2.0,wy-menuButtons[0]->getSize().y/2.0-100);

    for(auto btn : menuButtons) {
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

    for(auto btn:menuButtons)
        btn->draw();
}

void Menu::action() {
    mousePos = sf::Mouse::getPosition(*window);
    for(auto btn:menuButtons) {
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
            }
        }
    }
}

Menu::~Menu() {
    for(auto btn:menuButtons)
        delete btn;
}
