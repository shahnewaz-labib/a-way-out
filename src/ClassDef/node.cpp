#include "../include/node.hpp"
#include "../include/grid.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

Grid* Node::GameGrid=NULL;

void Node::CreateNode(int i,int j,sf::Color C=sf::Color::White){
    shape->setOrigin(GameGrid->tileSize/2.0,GameGrid->tileSize/2.0);
    shape->setPosition(sf::Vector2f( (j+1)*(GameGrid->tileSize+GameGrid->tileGap) - GameGrid->tileSize/2.0,(i+1)*(GameGrid->tileGap+GameGrid->tileSize) - GameGrid->tileSize/2.0) + GameGrid->OffSet);
    shape->setFillColor(C);
}

void Node::setOutline(sf::Color C, float thickness){
    shape->setOutlineColor(C);
    shape->setOutlineThickness(thickness);
}

VisitableNode::VisitableNode(int i,int j,sf::Color C){
    shape = new sf::CircleShape();
    dynamic_cast<sf::CircleShape*>(shape)->setRadius(GameGrid->tileSize/2.0);
    CreateNode(i,j,C);
}

ObstacleNode::ObstacleNode(int i,int j,sf::Color C){
    shape = new sf::RectangleShape();
    dynamic_cast<sf::RectangleShape*>(shape)->setSize(sf::Vector2f(GameGrid->tileSize,GameGrid->tileSize));
    CreateNode(i,j,C);
}
