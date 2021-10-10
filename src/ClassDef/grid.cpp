#include "../include/grid.hpp"
#include "../include/node.hpp"
#include <SFML/Window/Mouse.hpp>
#include <vector>
#include <iostream>
using namespace std;

Grid::Grid(int n, int m, sf::RenderWindow *W) : n(n), m(m), window(W) {
	grid.resize(n, vector<int>(m, -1));
    Nodes.resize(n,vector<Node*>(m));
    visited.resize(n, vector<bool>(m, 0));
	assignGoodGrid(1000);
}

void Grid::show() {
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (grid[i][j] != -1)
				cout << grid[i][j] << "\t";
			else
				cout << "#\t";
		}
		cout << "\n";
	}
}

bool Grid::valid(int x, int y) {
	return ((x >= 0 and x < n) and (y >= 0 and y < m));
}

vector<vector<int>> Grid::generateGrid(int n, int m) {
    vector<vector<int>>newGrid(n, vector<int>(m, -1));
	vector < vector<int> > possibleStartPos = { {0, n-1}, {0, m-1} };
	int x = possibleStartPos[0][rand() % 2], y = possibleStartPos[1][rand() %2], cnt = 1, mx = -1, nx, ny;
	bool stuck; 
	vector<int> ok;
	newGrid[x][y] = 0;
	while (true)
	{
		stuck = true;
		ok.clear();

		for (int i = 0; i < 4; ++i)
		{
			nx = x + Grid::dx[i];
			ny = y + Grid::dy[i];
			if (valid(nx, ny) and newGrid[nx][ny] == -1)
			{
				stuck = false;
				ok.emplace_back(i);
			}
		}

		if (stuck) {
			mx = max(mx, cnt-1);
			break;
		}

		int pos = rand() % ok.size();
		x += Grid::dx[ok[pos]];
		y += Grid::dy[ok[pos]];
		newGrid[x][y] = cnt++;
	}

	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if(newGrid[i][j] != -1) {
				newGrid[i][j] = (mx - newGrid[i][j]);
			}
		}
	}

	return newGrid;
}

void Grid::assignGoodGrid(int tries = 100) {
	int prevBadness = 1e9 + 7, badness, threshold = n+m;

	for (int T = 0; T < tries; ++T)
	{
		badness = 0;
		auto tempGrid = generateGrid(n, m);
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < m; ++j)
			{
				if (tempGrid[i][j] == -1)
				{
					int blockBadness = 1;
					for (int k = 0; k < 4; ++k)
					{
						if (valid(i + dx[k], j + Grid::dy[k]) and tempGrid[i + Grid::dx[k]][j + Grid::dy[k]] == -1)
							blockBadness *= 2;
					}
					badness += blockBadness;
				}
			}
		}

		if (badness < prevBadness and badness > threshold)
		{
			grid = tempGrid;
			prevBadness = badness;
		}
	}

    numberOfVisitableNodes = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(grid[i][j]!=-1)
                numberOfVisitableNodes++;
        }
    }

	cout << "Final badness " << prevBadness << "\n";
}

void Grid::scaleItems(){
    sf::Vector2u windowSize = window->getSize();

    auto getAdjustedTileSize = [&](double W,double N) -> double{
        return W/(N*(1.0+factor+factor/N));
    };

    tileSize = min(getAdjustedTileSize(windowSize.x,m),getAdjustedTileSize(windowSize.y,n));
    tileGap = factor*tileSize;
    lineHeight = tileSize+tileGap;
    lineWidth = 8;

    OffSet.x = (windowSize.x-(m*(tileSize+tileGap)+tileGap))/2.0; 
    OffSet.y = (windowSize.y-(n*(tileSize+tileGap)+tileGap))/2.0;
}



bool Grid::isAdjacentCell(sf::Vector2i prevPos,sf::Vector2i curPos){
    for(int i=0;i<4;i++){
        if(curPos == prevPos+sf::Vector2i(Grid::dx[i],Grid::dy[i]))
            return 1;
    }
    return 0;
}


int Grid::dx[] = {1, 0, -1, 0};
int Grid::dy[] = {0, 1, 0, -1};

sf::RectangleShape Grid::ConnectTwoNodes(sf::Vector2i prevPos,sf::Vector2i curPos){
    int h = lineHeight;
    int w = lineWidth;

    sf::RectangleShape R;
    int i1 = prevPos.x, j1 = prevPos.y;
    int i2 = curPos.x, j2 = curPos.y;

    // i -- Row, j -- Column

    double Y,X,F;

    if(i1 == i2){ // Horizontal
        Y = i1*(tileSize+tileGap) + tileGap + tileSize/2.0 - lineWidth/2.0;
        F = min(j1,j2);
        X = (F+1)*(tileSize+tileGap) - tileSize/2.0;
        swap(h,w);
    } else { // Vertical
        X = j1*(tileSize+tileGap) + tileGap + tileSize/2.0 - lineWidth/2.0;
        F = min(i1,i2);
        Y = (F+1)*(tileSize+tileGap) - tileSize/2.0;
    }
    R.setSize(sf::Vector2f(w,h));
    R.setPosition(sf::Vector2f(X,Y)+OffSet);
    return R;
}

void Grid::adjustNodes(){
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (grid[i][j] == -1) //Obstacle
            {
                Nodes[i][j] = new ObstacleNode(i,j);
                Nodes[i][j]->setOutline();
            }
            else if (grid[i][j] == 0) // Source
            {
                Nodes[i][j] = new VisitableNode(i,j,sf::Color::Blue);
                visitedPath.emplace_back(sf::Vector2i(i,j));
                startingCell=sf::Vector2i(i,j);
                visited[i][j] = 1;
            }
            else if(grid[i][j] == numberOfVisitableNodes-1){ // Finish Node
                Nodes[i][j] = new VisitableNode(i,j,sf::Color::Cyan);
            } 
            else // Normal Node
            {
                Nodes[i][j] = new VisitableNode(i,j);
//                 Nodes[i][j]->setOutline();
            }

        }
    }

}

void Grid::takeInput(){
    sf::Vector2i pos = sf::Mouse::getPosition(*window);
    pos.x /= (tileSize+tileGap+OffSet.x);
    pos.y /= (tileSize+tileGap+OffSet.y);
    swap(pos.x,pos.y);

    if(valid(pos.x, pos.y)){
        int i = pos.x, j = pos.y; // Clicked Node
        int pi=visitedPath.back().x,
            pj=visitedPath.back().y; // Previous Node

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(grid[i][j] !=- 1 && isAdjacentCell(visitedPath.back(), pos) && !visited[i][j]){
                Nodes[i][j]->setColor(sf::Color::Red);
                visited[i][j] = 1;
                visitedNodes++;
                if(visitedPath.size()>1){ // not Source Node
                    Nodes[pi][pj]->setColor(sf::Color::Yellow);
                }
                LinePath.emplace_back(ConnectTwoNodes(visitedPath.back(), pos));
                visitedPath.emplace_back(pos);
            }
        } 

        else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            if(visited[i][j] && visitedPath.size()>1){
                while(visitedPath.back() != pos) {
                    auto last = visitedPath.back();
                    Nodes[last.x][last.y]->setColor(sf::Color::White);
                    visited[last.x][last.y] = false;
                    visitedPath.pop_back();
                    LinePath.pop_back();
                    visitedNodes--;
                }
                if(pos != startingCell) {
                    Nodes[i][j]->setColor(sf::Color::Red);
                }
            }
        }

    }
}

void Grid::draw(){
    for(auto i:LinePath){
        window->draw(i);
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            window->draw(*(Nodes[i][j]->shape));
        }
    }
}
