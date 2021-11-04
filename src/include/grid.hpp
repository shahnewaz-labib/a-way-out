#pragma once
#include "item.hpp"
#include <vector>
class Node;

class Grid {
private:
	std::vector <std::vector<int>> grid;
	std::vector <std::vector<bool>> visited;
    std::vector <sf::Vector2i> visitedPath;
    std::vector <sf::RectangleShape> LinePath;
    std::vector <Item*> buttons;
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
    Item *reset,*solve;

public:
    class row
    {
        Grid &_a;
        int _i;
        public:
        row(Grid &a,int i) : _a(a),_i(i){}
        int operator[](int j) {return _a.grid[_i][j];}
    };
    row operator[](int i)
    {  
        return row(*this,i);
    }

    static int dx[], dy[];
	Grid(int N, int M, sf::RenderWindow *window);
// 	Grid(int N, int M, sf::RenderWindow *window,sf::Vector2f upperLeftCorner,sf::Vector2f bottomRightCorner);
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
    void dfs(std::vector<std::vector<bool>> &vis, std::vector<std::vector<int>> &tempGrid, int x, int y);
	void assignGoodGrid(int tries);
    ~Grid();
    void adjustHeaders();
    void removePath(sf::Vector2i pos);
    void addPath(sf::Vector2i pos);
    void solveGame();

    void regenGrid(int n,int m,int tries=1000);

    friend class Node;
    friend class VisitableNode;
    friend class ObstacleNode;
};
