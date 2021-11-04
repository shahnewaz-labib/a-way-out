#pragma once
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27


class TextBox
{
private:
  sf::Vector2f pos;
  sf::RectangleShape boundary;
  sf::Text textbox;
  std::ostringstream text;
  bool isSelected = false;
  int limit;
  int max,min;

  void typeText(int ch);
  void backspace();

public:
  bool isOn();
  bool contains(sf::Vector2i pos);
  sf::Vector2f getSize();

  TextBox(sf::Font &font, sf::Vector2f pos, int size, sf::Color color, int lim, int min,int max,bool sel);

  void adjustTextBox();
  int getValue();
  void setPosition(sf::Vector2f pos);
  void selected(bool sel);
  std::string getText();
  void setText(std::string txt);
  void drawTo(sf::RenderWindow &window);
  void typedOn(int ch);
};
