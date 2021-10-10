#include "../include/menu.hpp"

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
        item->setFont(liberationMono);
        item->setFontSize(40);
        item->setLetterSpacing(0.75);
        item->fitBox();
    }  
}

void Menu::action() {
    while (window->isOpen())
    {
        mousePos = sf::Mouse::getPosition(*window);
        while (window->pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed) {
                window->close();
            }
        }

        window->clear(getBGCol());
        window->draw(title);

        for(auto item:menuItems)
            item->draw();

        for(auto item:menuItems)
            item->checkHover(mousePos);
        
        window->display();
    }
}
Menu::~Menu() {
    for(auto item:menuItems)
        delete item;
}
