#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <vector>
class Node;

class Grid {
private:
	std::vector <std::vector<int>> grid;
	std::vector <std::vector<bool>> visited;
    std::vector <sf::Vector2i> visitedPath;
    std::vector <sf::RectangleShape> LinePath;
    sf::Vector2i startingCell;
    sf::RenderWindow *window;

    int n, m, visitedNodes=1;
    int numberOfVisitableNodes;
    double tileSize,tileGap;
    double factor = 0.8;
    double lineHeight;
    double lineWidth;
    
    sf::Vector2f OffSet=sf::Vector2f(0,0);
    std::vector <std::vector<Node*>>Nodes;
    sf::RectangleShape boundary,gridBox;
    // gridBox is inside boundary

public:

    static int dx[], dy[];
	Grid(int n, int m, sf::RenderWindow *window);
	Grid(int n, int m, sf::RenderWindow *window,sf::Vector2f upperLeftCorner,sf::Vector2f bottomRightCorner);
    void setBoundary(sf::Vector2f upperLeftCorner,sf::Vector2f bottomRightCorner);
    // changing boundary would require to run scaleItems() and adjustNodes()
    void setBoxColor(sf::Color fillColor,sf::Color outlineColor=sf::Color::Transparent,float outLineThickness=0);
    void setBoundaryColor(sf::Color fillColor,sf::Color outlineColor=sf::Color::Transparent,float outLineThickness=0);
    static bool isAdjacentCell(sf::Vector2i prevPos,sf::Vector2i curPos);
    sf::RectangleShape ConnectTwoNodes(sf::Vector2i prevPos,sf::Vector2i curPos);
    void scaleItems();
    void adjustNodes();
    void takeInput();
    void draw();
    bool isGameSolved(){ return visitedNodes==numberOfVisitableNodes; }

	void show();
	bool valid(int x, int y);

	std::vector<std::vector<int>> generateGrid(int n, int m);
	void assignGoodGrid(int tries);
    ~Grid();

    friend class Node;
    friend class VisitableNode;
    friend class ObstacleNode;
};
