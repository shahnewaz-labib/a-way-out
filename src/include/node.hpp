#pragma once
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shape.hpp>
#include "grid.hpp"

using namespace sf;

class Node{
protected:
    sf::Shape *shape;
public:
    static Grid *GameGrid;
    void CreateNode(int i,int j,sf::Color C);
    void setOutline(sf::Color C=sf::Color::Cyan,float thickness=2);
    static void setGameGrid(Grid *G){ GameGrid=G; }
    void setColor(sf::Color C){ shape->setFillColor(C); }
    friend class Grid;
};

class VisitableNode :public Node {
public:
    VisitableNode(int i,int j,sf::Color=sf::Color::White);
};

class ObstacleNode :public Node {
public:
    ObstacleNode(int i,int j,sf::Color=sf::Color::Green);
};
