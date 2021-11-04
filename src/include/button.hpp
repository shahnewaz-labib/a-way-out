#pragma once
#include "game_drawable.hpp"
#include <SFML/System/Vector2.hpp>

enum buttonType { Play,Level_Select,About,Exit,Random,Level,Dimension,BackToMenu };

class Button : public Game_Drawable
{
private:
    buttonType Type;
    sf::RectangleShape box;
    sf::Text txt;
    sf::Font ft;

    void centerText();

public:
    Button(buttonType T,sf::RenderWindow *_win, std::string _txt);
    void setFont(sf::Font& _ft);
    void setFontSize(unsigned int _size);
    void setFillColor(sf::Color _col);
    void setOutlineColor(sf::Color _col);
    void setTextColor(sf::Color _col);
    void setLetterSpacing(double x);
    void setPosition(sf::Vector2f _pos); // Center
    void fitBox();
    bool checkHover(sf::Vector2i mousePos);
    void draw();
    sf::Vector2f getPosition();
    sf::Vector2f getSize();
    std::string getText() const;
    buttonType getButtonType(); 
};

sf::Color getBGCol();
sf::Color getHoverColor();
sf::Color getTextColor();
sf::Color getInvertedTextColor();
