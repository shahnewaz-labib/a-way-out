#include "../include/grid.hpp"
#include "../include/game.hpp"
#include "../include/menu.hpp"

sf::Color Game::dayBGCol = sf::Color(216, 226, 233, 255);
sf::Color Game::dayHoverCol = sf::Color(69, 72, 130, 255);
sf::Color Game::dayTextCol = sf::Color::Black;
sf::Color Game::nightBGCol = sf::Color(18, 18, 18, 255);
sf::Color Game::nightHoverCol = sf::Color(27, 57, 251, 255);
sf::Color Game::nightTextCol = sf::Color::White;



Game::Game(double Width,double Height):Width(Width),Height(Height) {
    curBGCol = dayBGCol;
    curHoverCol = dayHoverCol;
    curTextCol = dayTextCol;

    bool day = true;
    srand(time(NULL));

    window = new sf::RenderWindow (sf::VideoMode(Width, Height), "A Way Out", sf::Style::Close);
    menu = new MainMenu(this,window, "A Way Out", 150, sf::Vector2f(Width / 2.0, Height - 150), 15);
    level = new Level_Select_Menu(this,window, "Select Type", 150, sf::Vector2f(Width / 2.0 - 70, Height - 150), 15);

    grid = new Grid(N, M, this,window);

    sf::Image icon;
    icon.loadFromFile("Assets/icon.png"); // File/Image/Pixel
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    day = true;
}

void Game::toggleDayNight() {
    day = !day;
    curBGCol = day? dayBGCol : nightBGCol;
    curHoverCol = day? dayHoverCol : nightHoverCol;
    curTextCol = day? dayTextCol : nightTextCol;
}
sf::Color Game::getBGCol() {
    return curBGCol;
}
sf::Color Game::getHoverColor() {
    return curHoverCol;
}

sf::Color Game::getTextColor() {
    return curTextCol;
}

sf::Color Game::getInvertedTextColor() {
    return day ? sf::Color::White : sf::Color::Black;
}

void Game::play(){
    while (window->isOpen())
    {
        if(playButtonClicked){
            level->updateDimension(N, M);
            grid->regenGrid(N, M);
            playButtonClicked = 0;
        }

        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::GainedFocus)
            {
                isWindowFocused = true;
            }
            if (event.type == sf::Event::LostFocus)
            {
                isWindowFocused = false;
            }

            if (event.type == sf::Event::Closed)
            {
                window->close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Q)
                {
                    window->close();
                }
            }
            if (currentState == state::inLevelSelect && sf::Event::TextEntered)
            {
                level->getTextInput(event.text.unicode);
            }
        }

        window->clear();

        if (currentState == state:: endProgram)
        {
            break;
        }

        if (currentState == state:: inMenu)
        {
            if (isWindowFocused)
            {
                menu->action();
            }
            menu->draw();
        }

        else if (currentState == state:: inLevelSelect)
        {
            if (isWindowFocused)
            {
                level->action();
            }
            level->draw();
        }

        else if (currentState == state:: inPlay)
        {
            if (isWindowFocused)
            {
                grid->takeInput();
            }

            grid->draw();

            if (grid->isGameSolved())
            {
                switch(level->getCurrentSelected()){
                    case Level:
                        level->setCurrentLevel(level->getCurrentLevel()+1);
                        break;
                    default:
                        break;
                }
//                 currentState = state::inPlay;
                playButtonClicked = 1;
            }
        }
        window->display();
    }
}

void Game::quit(){
    currentState = state::endProgram;
}

void Game::setState(state st){
    currentState = st;
}
