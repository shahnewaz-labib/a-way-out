#pragma once
#include "game_drawable.hpp"

class Button : public Game_Drawable
{
private:
    sf::RectangleShape box;
    sf::Text txt;
    sf::Font ft;

    void centerText();

public:
    enum OriginMode
    {
        Center,
        UpperLeft
    };
    Button(sf::RenderWindow *_win, sf::Vector2f _size, std::string _txt, sf::Vector2f _pos);
    void setFont(sf::Font& _ft);
    void setFontSize(unsigned int _size);
    void setFillColor(sf::Color _col);
    void setOutlineColor(sf::Color _col);
    void setTextColor(sf::Color _col);
    void setLetterSpacing(double x);
    void setPosition(sf::Vector2f _pos, OriginMode _mode);
    void fitBox();
    bool checkHover(sf::Vector2i mousePos);
    void draw();
    std::string getText() const;
};

sf::Color getBGCol();
sf::Color getHoverColor();
sf::Color getTextColor();
sf::Color getInvertedTextColor();