#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <vector>
#include <iostream>
#include "include/grid.hpp"
using namespace std;

sf::Color dayBGCol = sf::Color(sf::Color(216, 226, 233, 255));
sf::Color dayTextColor = sf::Color::Black;

class Drawable {
protected:
	int x, y;
public:
	virtual void Draw() = 0;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 800), "A Way Out", sf::Style::Close);
    sf::Image icon;
    icon.loadFromFile("Assets/icon.png"); // File/Image/Pixel
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    vector<sf::Text> texts;
    sf::Font sourceCode;
    sourceCode.loadFromFile("Assets/SourceCodePro-SemiBoldItalic.ttf");
    sf::Text title("A Way Out", sourceCode, 62);
    title.setFillColor(dayTextColor);
    title.setPosition(130, 150);
    title.setLetterSpacing(0.75);
    while (window.isOpen()) {
    	window.clear(dayBGCol);
    	window.draw(title);
    	window.display();
    }
}

