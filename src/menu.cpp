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
#define WIN_HEIGHT 720
#define WIN_WIDTH 600

bool day = true;

sf::Color getBGCol() {
    return day ? sf::Color(216, 226, 233, 255) : sf::Color::Black;
}

sf::Color getHoverColor() {
    return day ? sf::Color(69, 72, 130, 255) : sf::Color::White;
}

sf::Color getTextColor() {
    return day ? sf::Color::Black : sf::Color::White;
}

sf::Color getInvertedTextColor() {
    return day ? sf::Color::White : sf::Color::Black;
}

class Game_Drawable
{
protected:
    float x, y;
    float width, height;
    sf::RenderWindow *window;

public:
    Game_Drawable(sf::RenderWindow *_win) : window(_win) {}
    virtual void Draw() = 0;
    virtual void setFont(sf::Font&) {}
    virtual void setFontSize(unsigned int) {}
    virtual void setLetterSpacing(double) {}
    virtual void fitBox() {}
    virtual void checkHover(sf::Vector2i) {}
};

class Button : public Game_Drawable
{
private:
    sf::RectangleShape box;
    sf::Text txt;
    sf::Font ft;

    void centerText()
    {
        sf::FloatRect textRect = txt.getLocalBounds();
        txt.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        txt.setPosition(sf::Vector2f(box.getPosition().x + width / 2.0f, box.getPosition().y + height / 2.0f));
    }

public:
    enum OriginMode
    {
        Center,
        UpperLeft
    };
    Button(sf::RenderWindow *_win, sf::Vector2f _size, string _txt, sf::Vector2f _pos) : Game_Drawable(_win)
    {
        width = _size.x;
        height = _size.y;
        x = _pos.x;
        y = _pos.y;

        box.setSize(_size);
        box.setPosition(_pos);
        box.setOutlineThickness(0.0f);
        box.setOutlineColor(sf::Color::Black);
        if (!ft.loadFromFile("Assets/SourceCodePro-SemiBoldItalic.ttf"))
        {
            sf::err() << "Couldn't load font\n";
        }
        txt.setFont(ft);
        txt.setString(_txt);
        txt.setFillColor(sf::Color::Black);

        centerText();
    }
    void setFont(sf::Font& _ft) { ft = _ft; txt.setFont(_ft); }
    void setFontSize(unsigned int _size) { txt.setCharacterSize(_size); }
    void setFillColor(sf::Color _col) { box.setFillColor(_col); }
    void setOutlineColor(sf::Color _col) { box.setOutlineColor(_col); }
    void setTextColor(sf::Color _col) { txt.setFillColor(_col); }
    void setLetterSpacing(double x) { txt.setLetterSpacing(x); }
    void setPosition(sf::Vector2f _pos, OriginMode _mode)
    {
        x = _pos.x;
        y = _pos.y;
        if (_mode == Center)
        {
            box.setOrigin(sf::Vector2f(width / 2.0f, height / 2.0f));
        }
        else if (_mode == UpperLeft)
        {
            box.setOrigin(sf::Vector2f(0.0f, 0.0f));
        }
        box.setPosition(sf::Vector2f(x, y));
        centerText();

        //resetting origin for consistancy in other functions
        box.setOrigin(sf::Vector2f(0.0f, 0.0f));
    }
    void fitBox()
    {
        box.setSize(sf::Vector2f(txt.getLocalBounds().width + 5.0f, txt.getLocalBounds().height + 5.0f));
        width = box.getSize().x;
        height = box.getSize().y;
        centerText();
    }

    void checkHover(sf::Vector2i mousePos) {
        if(box.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            box.setFillColor(getHoverColor());
            txt.setFillColor(getInvertedTextColor());

        }
        else {
            box.setFillColor(getBGCol());
            txt.setFillColor(getTextColor());
        }
    }

    void Draw()
    {
        window->draw(box);
        window->draw(txt);
    }
};

class Menu {
private:
    sf::RenderWindow* window;
    vector <Game_Drawable*> menuItems;
    sf::Text title;
    sf::Font sourceCode, liberationMono;
    sf::Event ev;
    sf::Vector2i mousePos;
    //static sf::Color dayBGCol = sf::Color(216, 226, 233, 255), dayHoverColor = sf::Color(69, 72, 130, 255), dayTextColor = sf::Color::Black;
public:
    Menu(sf::RenderWindow* window) : window(window) {
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

    void action() {
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
                item->Draw();

            for(auto item:menuItems)
                item->checkHover(mousePos);
            
            window->display();
        }
    }
    ~Menu() {
        for(auto item:menuItems)
            delete item;
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "A Way Out", sf::Style::Close);
    sf::Image icon;
    icon.loadFromFile("Assets/icon.png"); // File/Image/Pixel
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Menu menu(&window);
    menu.action();
}
