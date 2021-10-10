#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "include/grid.hpp"
#include "include/node.hpp"
#include "include/menu.hpp"
double GameWidth = 550;
double GameHeight = 700;

using namespace std;
state currentState;

int main(){
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(GameWidth,GameHeight), "A Way Out", sf::Style::Close);

    currentState = inMenu;

    int N = 6;
    int M = 4;

    Menu menu(&window);

    Grid grid(N, M, &window);
    Node::setGameGrid(&grid);

    grid.scaleItems();
    grid.show(); // numbers
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
                // cout << "gained focus\n";
                isWindowFocused = true;
            }
            if(event.type == sf::Event::LostFocus) {
                // cout << "Lost focus\n";
                isWindowFocused = false;
            }

            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Q) {
                    // cout << "q pressed. Quitting.\n";
                    window.close();
                
                }
            }
        }

        window.clear();

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
