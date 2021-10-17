#include "../include/button.hpp"

bool day = 0;

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


void Button::centerText()
{
    sf::FloatRect textRect = txt.getLocalBounds();
    txt.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    txt.setPosition(sf::Vector2f(box.getPosition().x + width / 2.0f, box.getPosition().y + height / 2.0f));
}


Button::Button(sf::RenderWindow *_win, sf::Vector2f _size, std::string _txt, sf::Vector2f _pos) : Game_Drawable(_win)
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
void Button::setFont(sf::Font& _ft) { ft = _ft; txt.setFont(_ft); }
void Button::setFontSize(unsigned int _size) { txt.setCharacterSize(_size); }
void Button::setFillColor(sf::Color _col) { box.setFillColor(_col); }
void Button::setOutlineColor(sf::Color _col) { box.setOutlineColor(_col); }
void Button::setTextColor(sf::Color _col) { txt.setFillColor(_col); }
void Button::setLetterSpacing(double x) { txt.setLetterSpacing(x); }
void Button::setPosition(sf::Vector2f _pos, OriginMode _mode)
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
void Button::fitBox()
{
    box.setSize(sf::Vector2f(txt.getLocalBounds().width + 5.0f, txt.getLocalBounds().height + 5.0f));
    width = box.getSize().x;
    height = box.getSize().y;
    centerText();
}

bool Button::checkHover(sf::Vector2i mousePos) {
    if(box.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
        box.setFillColor(getHoverColor());
        txt.setFillColor(getInvertedTextColor());
        return true;
    }
    else {
        box.setFillColor(getBGCol());
        txt.setFillColor(getTextColor());
        return false;
    }
}

std::string Button::getText() const {
    return txt.getString();
}

void Button::draw()
{
    window->draw(box);
    window->draw(txt);
}

