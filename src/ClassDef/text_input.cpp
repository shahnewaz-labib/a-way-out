#include "../include/text_input.hpp"


void TextBox:: typeText(int ch)
{
    text << (char)ch;
    textbox.setString(text.str());
}

void TextBox:: backspace()
{
    std::string temp = text.str();
    temp.pop_back();
    text.str("");
    text << temp;
    textbox.setString(text.str() + '_');
}

bool TextBox::isOn() { return isSelected; }
bool TextBox::contains(sf::Vector2i pos){
    return boundary.getGlobalBounds().contains(sf::Vector2f(pos));
}
sf::Vector2f TextBox::getSize(){
    return boundary.getSize();
}

inputType TextBox::getType(){
    return Type;
}

TextBox::TextBox(inputType Type,sf::Font &font, sf::Vector2f pos, int size, sf::Color color, int lim, std::string min,std::string max,bool sel):max(max),min(min),pos(pos),limit(lim),Type(Type)
{
    int padding = 10;
    textbox.setFont(font);
    textbox.setCharacterSize(size);
    textbox.setFillColor(color);
    isSelected = sel;

    setText(std::string(lim,'9'));
    auto tmp = textbox.getLocalBounds();
    boundary.setSize(sf::Vector2f(tmp.width+padding,tmp.height+padding*2));
    boundary.setPosition(pos);

    if (sel)
    {
        textbox.setString("_");
    }
    else
    {
        textbox.setString("");
    }

    boundary.setFillColor(sf::Color::Blue);
}

void TextBox:: adjustTextBox(){
    auto tmp = textbox.getLocalBounds();
    textbox.setOrigin(tmp.left+tmp.width/2.0,tmp.top+tmp.height/2.0);
    textbox.setPosition(boundary.getPosition()+sf::Vector2f(boundary.getSize())/2.0f);
}

void TextBox:: setPosition(sf::Vector2f pos){
    this->pos = pos;
    boundary.setPosition(pos);
    adjustTextBox();
}

void TextBox:: selected(bool sel)
{
    isSelected = sel;
    if (sel)
    {
        textbox.setString(text.str() + '_');
    }
    else
    {
        textbox.setString(text.str());
    }
}

std::string TextBox::getText()
{
    return text.str();
}

void TextBox:: setText(std::string txt)
{
    text.str(txt);
    textbox.setString(text.str());
    adjustTextBox();
}

void TextBox:: drawTo(sf::RenderWindow &window)
{
    window.draw(boundary);
    window.draw(textbox);
}

void TextBox:: typedOn(sf::Event &input)
{
    if (isSelected)
    {
        int ch = input.text.unicode;

        if (ch >='0' && ch<='9')
        {
            if (text.str().length() < (size_t)limit)
            {
                typeText(ch);
            }
            else {
                setText(max);
            }
        }
        else if (ch == DELETE_KEY)
        {
            if(text.str().length()>0)
                backspace();
            else
                setText(min);
        }

    }
}
