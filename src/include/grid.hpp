#pragma once

#include <iostream>
#include <vector>

class Grid {
private:
	std::vector <std::vector<int>> grid;
	int n, m;
	static int dx[], dy[];
public:
	Grid(int n, int m);
	Grid(int n, int m, bool dummy, int tries);

	class Row {
	private:
		Grid& _g;
		int _x;
	public:
		Row(Grid& g, int x);
		int& operator[] (int y);
	};

	void show();
	bool valid(int x, int y);
	int& at(int x, int y);

	static Grid generateGrid(int n, int m);
	void assignGoodGrid(int tries);

	Row operator[] (int x);
};
