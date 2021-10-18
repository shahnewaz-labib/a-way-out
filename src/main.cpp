#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <iostream>
#include "include/grid.hpp"
#include "include/node.hpp"
#include "include/menu.hpp"
double GameWidth = 500;
double GameHeight = 700;

using namespace std;
state currentState;

int main(){
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(GameWidth,GameHeight), "A Way Out", sf::Style::Close);

    currentState = inMenu;

    int N = 8;
    int M = 5;

    Menu menu(&window);

    Grid grid(N, M, &window);
    Node::setGameGrid(&grid);
//     sf::Vector2f gridOffset(50,50);
// 
//     grid.setBoundary(gridOffset, sf::Vector2f(window.getSize())-gridOffset);
//     grid.setBoxColor(sf::Color(94,83,83));
//     grid.setBoundaryColor(sf::Color(94,83,83));

//     grid.show(); // numbers
    grid.adjustNodes();

    sf::Image icon;
    icon.loadFromFile("Assets/icon.png"); // File/Image/Pixel
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    bool isWindowFocused = true;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::GainedFocus) {
                isWindowFocused = true;
            }
            if(event.type == sf::Event::LostFocus) {
                isWindowFocused = false;
            }

            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Q) {
                    window.close();
                }
            }
        }

        window.clear();

        if(currentState == endProgram){
            break;
        }

        if(currentState == inMenu) {
            if(isWindowFocused) {
                menu.action();
            }
            menu.draw();
        }
        
        else if(currentState == inPlay) {
            if(isWindowFocused) {
                grid.takeInput();
            }

            grid.draw();

            if(grid.isGameSolved()){
                std::cout<<"Done"<<"\n";
                return 0;
            }
        }

        window.display();
    }

    return 0;
}
