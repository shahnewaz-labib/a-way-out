#include <SFML/Graphics.hpp>
#include "grid.cpp"
#include <vector>
using namespace std;

int main()
{
  srand(time(NULL));
  int N = 10;
  int M = 10;
  sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!", sf::Style::Close);
  vector<vector<int>> grid = findGoodGrid(N, M);

  sf::RectangleShape shape[N][M];
  for (int i = 0; i < N; ++i)
  {
    for (int j = 0; j < M; ++j)
    {
      shape[i][j].setSize(sf::Vector2f(50.0f, 50.0f));
      if (grid[i][j] == -1)
      {
        shape[i][j].setFillColor(sf::Color::Green);
        shape[i][j].setOutlineThickness(2.0f);
        shape[i][j].setOutlineColor(sf::Color::Cyan);
      }
      else if (grid[i][j] == 0)
      {
        shape[i][j].setFillColor(sf::Color::Blue);
      }
      else
      {
        shape[i][j].setOutlineThickness(2.0f);
        shape[i][j].setOutlineColor(sf::Color::Cyan);
      }
    }
  }
  for (int i = 0; i < N; ++i)
  {
    for (int j = 0; j < M; ++j)
    {
      shape[i][j].setPosition(sf::Vector2f(50.0f * i, 50.0f * j));
    }
  }
  // shape.setFillColor(sf::Color::Green);
  // shape.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));
  // shape.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    for (int i = 0; i < N; ++i)
    {
      for (int j = 0; j < M; ++j)
      {
        window.draw(shape[i][j]);
      }
    }

    window.display();
  }

  return 0;
}