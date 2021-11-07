#include "../include/button.hpp"
#include "../include/game.hpp"
#include <SFML/System/Vector2.hpp>

bool day = 0;

void Button::centerText()
{
    sf::FloatRect textRect = txt.getLocalBounds();
    txt.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    txt.setPosition(sf::Vector2f(x,y));
}


Button::Button(buttonType T,sf::RenderWindow *_win, std::string _txt) : Game_Drawable(_win)
{
    Type = T;

//     box.setSize(_size);
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
void Button::setFont(sf::Font& _ft) { ft = _ft; txt.setFont(_ft); }
void Button::setFontSize(unsigned int _size) { txt.setCharacterSize(_size); }
void Button::setFillColor(sf::Color _col) { box.setFillColor(_col); }
void Button::setOutlineColor(sf::Color _col) { box.setOutlineColor(_col); }
void Button::setTextColor(sf::Color _col) { txt.setFillColor(_col); }
void Button::setLetterSpacing(double x) { txt.setLetterSpacing(x); }
void Button::setPosition(sf::Vector2f _pos)
{
    x = _pos.x;
    y = _pos.y;
    box.setPosition(sf::Vector2f(x, y));
    centerText();
}
void Button::fitBox()
{
    box.setSize(sf::Vector2f(txt.getLocalBounds().width + 15.0f, txt.getLocalBounds().height + 15.0f));
    width = box.getSize().x;
    height = box.getSize().y;
    box.setOrigin(sf::Vector2f(width / 2.0f, height / 2.0f));
    centerText();
}

bool Button::checkHover(sf::Vector2i mousePos) {
    if(box.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        box.setFillColor(Game::getHoverColor());
        txt.setFillColor(Game::getInvertedTextColor());
        return true;
    }
    else {
        box.setFillColor(Game::getBGCol());
        txt.setFillColor(Game::getTextColor());
        return false;
    }
}

std::string Button::getText() const {
    return txt.getString();
}

buttonType Button::getButtonType() {
    return Type;
}

sf::Vector2f Button::getSize(){
    return box.getSize();
}

void Button::draw()
{
    window->draw(box);
    window->draw(txt);
}

sf::Vector2f Button::getPosition() {
    return  box.getPosition();
}
