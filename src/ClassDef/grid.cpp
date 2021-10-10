#include "../include/grid.hpp"
#include <SFML/System/Vector2.hpp>
#include <vector>
using namespace std;

Grid::Grid(int n, int m) : n(n), m(m) {
	grid.resize(n, vector<int>(m, -1));
	assignGoodGrid(1000);
}

Grid::Grid(int n , int m , bool dummy = false, int tries = 1000): n(n), m(m) {
	grid.resize(n, vector<int>(m, -1));
	if(!dummy) {
		assignGoodGrid(tries);
	}
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

int& Grid::at(int x, int y) {
	return grid[x][y];
}

Grid Grid::generateGrid(int n, int m) {
	Grid newGrid(n, m, true);
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
			if (newGrid.valid(nx, ny) and newGrid[nx][ny] == -1)
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
		Grid tempGrid = Grid::generateGrid(n, m);
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < m; ++j)
			{
				if (tempGrid[i][j] == -1)
				{
					int blockBadness = 1;
					for (int k = 0; k < 4; ++k)
					{
						if (this->valid(i + dx[k], j + Grid::dy[k]) and tempGrid[i + Grid::dx[k]][j + Grid::dy[k]] == -1)
							blockBadness *= 2;
					}
					badness += blockBadness;
				}
			}
		}

		if (badness < prevBadness and badness > threshold)
		{
			*this = tempGrid;
			prevBadness = badness;
		}
	}

	cout << "Final badness " << prevBadness << "\n";
}

void Grid::scaleItems(sf::RenderWindow &window,int N,int M){
    sf::Vector2u windowSize = window.getSize();

    auto getAdjustedTileSize = [&](double W,double N) -> double{
        return W/(N*(1.0+factor+factor/N));
    };

    tileSize = min(getAdjustedTileSize(windowSize.x,M),getAdjustedTileSize(windowSize.y,N));
    tileGap = factor*tileSize;
    lineHeight = tileSize+tileGap;
    lineWidth = 8;

    OffSet.x = (windowSize.x-(M*(tileSize+tileGap)+tileGap))/2.0; 
    OffSet.y = (windowSize.y-(N*(tileSize+tileGap)+tileGap))/2.0;
}

Grid::Row::Row(Grid& g, int x) : _g(g), _x(x)
{}
int& Grid::Row::operator[] (int y) {
	return _g.at(_x, y);
}

Grid::Row Grid::operator[] (int x) {
	return Row(*this, x);
}

int Grid::dx[] = {1, 0, -1, 0};
int Grid::dy[] = {0, 1, 0, -1};
