#include <vector>
#include <iostream>
#include "include/grid.hpp"
#include "include/node.hpp"
#include "include/menu.hpp"
#include "include/level_menu.hpp"
#include "include/text_input.hpp"
double GameWidth = 500;
double GameHeight = 700;
bool playButtonClicked=0;

using namespace std;
state currentState;

int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(GameWidth, GameHeight), "A Way Out", sf::Style::Close);
    
    currentState = inMenu;

    int N = 8;
    int M = 5;

    MainMenu menu(&window, "A Way Out", 150, sf::Vector2f(GameWidth / 2.0, GameHeight - 150), 15);
    Level_Select_Menu level(&window, "Select Type", 150, sf::Vector2f(GameWidth / 2.0 - 70, GameHeight - 150), 15);

    Grid grid(N, M, &window);
    level.GameGrid = &grid;
    sf::Image icon;
    icon.loadFromFile("Assets/icon.png"); // File/Image/Pixel
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    bool isWindowFocused = true;

    while (window.isOpen())
    {
        if(playButtonClicked){
            level.updateDimension(N, M);
            grid.regenGrid(N, M);
            playButtonClicked = 0;
        }

        sf::Event event;
        while (window.pollEvent(event))
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
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Q)
                {
                    window.close();
                }
            }
            if (currentState==inLevelSelect && sf::Event::TextEntered)
            {
                level.getTextInput(event.text.unicode);
            }
        }

        window.clear();

        if (currentState == endProgram)
        {
            break;
        }

        if (currentState == inMenu)
        {
            if (isWindowFocused)
            {
                menu.action();
            }
            menu.draw();
        }

        else if (currentState == inLevelSelect)
        {
            if (isWindowFocused)
            {
                level.action();
            }
            level.draw();
        }

        else if (currentState == inPlay)
        {
            if (isWindowFocused)
            {
                grid.takeInput();
            }

            grid.draw();

            if (grid.isGameSolved())
            {
                std::cout << "Done"
                          << "\n";
                return 0;
            }
        }
        window.display();
    }

    return 0;
}
