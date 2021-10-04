#pragma once

#include <grid.hpp>

class Row {
private:
	Grid& _g;
	int _x;
public:
	Row(Grid& g, int x);
	int& operator[] (int y);
}