#include "grid.hpp"

inline bool Grid::valid(int x, int y, int N, int M) {
    return !(x < 0 or x >= N or y < 0 or y >= M);
}

std::vector<std::vector<int>> Grid::generate(int N, int M)
{
	std::vector<std::vector<int>> genGrid(N, std::vector<int>(M, -1));

	std::vector<std::vector<int>> startPos = { {0, M-1}, {0, N-1} };

	int x = startPos[0][rand() % 2], y = startPos[1][rand() % 2], cnt = 1, mx = -1;
	//cout << x << " " << y << "\n";
	genGrid[x][y] = 0;

	while (true)
	{
		int nx, ny;
		bool stuck = true;
		std::vector<int> ok;

		for (int i = 0; i < 4; i++)
		{
			nx = x + dx[i];
			ny = y + dy[i];
			if (valid(nx, ny, N, M) and genGrid[nx][ny] == -1)
			{
				stuck = false;
				ok.emplace_back(i);
			}
		}

		if (stuck) {
			mx = std::max(mx, cnt-1);
			break;
		}

		int pos = rand() % ok.size();
		x += dx[ok[pos]];
		y += dy[ok[pos]];
		//cout << x << " " << y << "\n";
		genGrid[x][y] = cnt++;
	}

	for(int i = 0; i < N; ++i) {
		for(int j = 0; j < M; ++j) {
			if(genGrid[i][j] != -1) {
				genGrid[i][j] = (mx - genGrid[i][j]);
			}
		}
	}

	return genGrid;
}

std::vector<std::vector<int>> Grid::findGoodGrid(int N, int M)
{
	int prevBadness = 1e9 + 7, badness;
	std::vector<std::vector<int>> grid(N, std::vector<int>(M, -1));

	for (int T = 0; T < 1000; ++T)
	{
		badness = 0;
		std::vector<std::vector<int>> tempGrid = generate(N, M);
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				if (tempGrid[i][j] == -1)
				{
					int blockBadness = 1;
					for (int k = 0; k < 4; ++k)
					{
						if (valid(i + dx[k], j + dy[k], N, M) and tempGrid[i + dx[k]][j + dy[k]] == -1)
							blockBadness *= 2;
					}
					badness += blockBadness;
				}
			}
		}
		if (badness < prevBadness)
		{
			grid = tempGrid;
			prevBadness = badness;
		}
	}
    return grid;
	std::cout << "Final badness " << prevBadness << "\n";
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			if (grid[i][j] != -1)
				std::cout << grid[i][j] << "\t";
			else
				std::cout << "#\t";
		}
		std::cout << "\n";
	}
	return grid;
}

Grid::Grid(int n, int m) {
    g = findGoodGrid(n, m);
}
