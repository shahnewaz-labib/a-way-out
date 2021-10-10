#include "include/menu.hpp"
using namespace std;

#define WIN_HEIGHT 720
#define WIN_WIDTH 600


int main()
{
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "A Way Out", sf::Style::Close);
    sf::Image icon;
    icon.loadFromFile("Assets/icon.png"); // File/Image/Pixel
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Menu menu(&window);
    menu.action();
}