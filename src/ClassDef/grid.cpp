#include "../include/grid.hpp"
#include "../include/node.hpp"
#include "../include/menu.hpp"
#include "../include/game.hpp"
#include <iostream>
using namespace std;

Grid::Grid(int n, int m, Game *game,sf::RenderWindow *W): game(game), window(W){
    Node::setGameGrid(this);
    setBoundary(sf::Vector2f(0,0), sf::Vector2f(window->getSize()));
    boundary.setFillColor(sf::Color::Transparent);
    gridBox.setFillColor(sf::Color::Transparent);
    regenGrid(n, m);

    adjustHeaders();
}

void Grid::regenGrid(int N, int M,int tries){
    n = N, m = M;
	grid.assign(n, vector<int>(m, -1));
    Nodes.assign(n,vector<Node*>(m));
    visited.assign(n, vector<bool>(m, 0));
    visitedPath.clear();
    LinePath.clear();
    assignGoodGrid(tries);
    scaleItems();
    adjustNodes();
}


void Grid::setBoundary(sf::Vector2f upperLeftCorner, sf::Vector2f bottomRightCorner){
    boundary.setPosition(upperLeftCorner);
    boundary.setSize(bottomRightCorner-upperLeftCorner);
}

void Grid::setBoxColor(sf::Color fillColor, sf::Color outlineColor, float outLineThickness){
    gridBox.setFillColor(fillColor);
    gridBox.setOutlineColor(outlineColor);
    gridBox.setOutlineThickness(outLineThickness);
}

void Grid::setBoundaryColor(sf::Color fillColor, sf::Color outlineColor, float outLineThickness){
    boundary.setFillColor(fillColor);
    boundary.setOutlineColor(outlineColor);
    boundary.setOutlineThickness(outLineThickness);
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

void Grid::dfs(std::vector<std::vector<bool>>& vis, std::vector<std::vector<int>>& tempGrid, int x, int y) {
    vis[x][y] = 1;
    for(int k=0; k < 4; ++k) {
        if(valid(x + dx[k], y + dy[k]) and tempGrid[x + dx[k]][y + dy[k]] == -1 and !vis[x + dx[k]][y + dy[k]])
            dfs(vis, tempGrid, x + dx[k], y + dy[k]);
    }
}

void Grid::assignGoodGrid(int tries = 1000) {
	double prevBadness = 1e9 + 7, badness, threshold = m + n + (m*n)/(double)(m+n), groups;

	for (int T = 0; T < tries; ++T)
	{
		badness = 0, groups = 0;
		auto tempGrid = generateGrid(n, m);
        std::vector<vector<bool>> vis(n, vector<bool>(m, 0));

        for(int i=0; i < n; ++i) {
            for(int j=0; j < m; ++j) {
                if(tempGrid[i][j] == -1 and !vis[i][j]) {
                    ++groups;
                    dfs(vis, tempGrid, i, j);
                }
            }
        }

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

        if(groups == 0)
            continue;

		if (badness/groups < prevBadness and badness > threshold)
		{
			grid = tempGrid;
			prevBadness = badness/groups;
		}
	}

    numberOfVisitableNodes = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(grid[i][j]!=-1)
                numberOfVisitableNodes++;
        }
    }

// 	cout << "Final badness " << prevBadness << "\n";
}

void Grid::scaleItems(){
    auto getAdjustedTileSize = [&](double W,double N) -> double{
        return W/(N*(1.0+factor+factor/N));
    };

    sf::Vector2f gridSize = boundary.getSize();

    tileSize = min(getAdjustedTileSize(gridSize.x,m),getAdjustedTileSize(gridSize.y,n));
    tileGap = factor*tileSize;
    lineHeight = tileSize+tileGap;
    lineWidth = 8;

    OffSet.x = (gridSize.x-(m*(tileSize+tileGap)+tileGap))/2.0; 
    OffSet.y = (gridSize.y-(n*(tileSize+tileGap)+tileGap))/2.0;
    OffSet += boundary.getPosition();

    gridBox.setPosition(OffSet);
    gridBox.setSize(sf::Vector2f(m*tileSize+(m+1)*tileGap,n*tileSize+(n+1)*tileGap));
}


int Grid::dx[] = {1, 0, -1, 0};
int Grid::dy[] = {0, 1, 0, -1};


bool Grid::isAdjacentCell(sf::Vector2i prevPos,sf::Vector2i curPos){
    for(int i=0;i<4;i++){
        if(curPos == prevPos+sf::Vector2i(Grid::dx[i],Grid::dy[i]))
            return 1;
    }
    return 0;
}


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
            if(Nodes[i][j]!=nullptr) delete Nodes[i][j];
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
//                 Nodes[i][j]->setOutline(sf::Color::Black,1);
            }

        }
    }

}

void Grid::removePath(sf::Vector2i pos){
    if(visited[pos.x][pos.y] && visitedPath.size()>1){
        while(visitedPath.back() != pos) {
            auto last = visitedPath.back();
            Nodes[last.x][last.y]->setColor(sf::Color::White);
            visited[last.x][last.y] = false;
            visitedPath.pop_back();
            LinePath.pop_back();
            visitedNodes--;
        }
        if(pos != startingCell) {
            Nodes[pos.x][pos.y]->setColor(sf::Color::Red);
        }
    }
}

void Grid::addPath(sf::Vector2i pos){
    int i=pos.x, j=pos.y;
    int pi=visitedPath.back().x,
       pj=visitedPath.back().y; // Previous Node

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

void Grid::solveGame(){
    removePath(startingCell);
    int i = startingCell.x, j = startingCell.y;
    
    while(grid[i][j]<=numberOfVisitableNodes-3){
        int ni,nj;
        for(int k=0;k<4;k++){
            ni = i+dx[k];
            nj = j+dy[k];
            if(valid(ni,nj) && grid[i][j]+1==grid[ni][nj]){
                i = ni, j=nj;
                break;
            }
        }

        addPath(sf::Vector2i(i,j));
    }

}

void Grid::takeInput(){
    sf::Vector2i pos = sf::Mouse::getPosition(*window);

    for(auto i:buttons){
        if(i->contains(pos)){
            i->setTextureRect(1);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                switch (i->Type) {
                    case itemType::Reset:
                        removePath(startingCell);
                        break;
                    case itemType::Solve:
                        solveGame();
                        break;
                    case itemType::Back:
                        game->setState(state::inMenu);
                        break;
                }
            }
            return;
        } else {
            i->setTextureRect();
        }
    }

    if(!gridBox.getGlobalBounds().contains(sf::Vector2f(pos))) return;
    pos.x = (pos.x-OffSet.x)/(tileSize+tileGap);
    pos.y = (pos.y-OffSet.y)/(tileSize+tileGap);
    swap(pos.x,pos.y);

    if(!valid(pos.x, pos.y)) return;

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        addPath(pos);
    } 

    else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
        removePath(pos);
    }

}

void Grid::draw(){
    window->draw(boundary);
    window->draw(gridBox);

    for(auto i:buttons){
        i->draw();
    }

    for(auto i:LinePath){
        window->draw(i);
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            window->draw(*(Nodes[i][j]->shape));
        }
    }
}


Grid::~Grid(){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            delete Nodes[i][j];
        }
    }
    for(auto &i:buttons){
        delete i;
    }
}

void Grid::adjustHeaders(){
    float padding = 20;
    sf::Vector2f size = sf::Vector2f(30,30);
    int wx = window->getSize().x;
    int wy = window->getSize().y;
    setBoundary(sf::Vector2f(0,size.y+padding), sf::Vector2f(wx,wy));
    sf::Vector2f pos = sf::Vector2f(wx-size.x/2.0-padding,padding+size.y/2.0);
    
    buttons.push_back(new Item(window,size,"Assets/reset.png",Reset,pos));

    pos.x -= padding + size.x;
    buttons.push_back(new Item(window,size,"Assets/solve.png",Solve,pos));

    buttons.push_back(new Item(window,size,"Assets/back.png",Back,sf::Vector2f(padding+size.x/2.0,pos.y)));
}
