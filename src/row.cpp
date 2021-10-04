#include <row.hpp>


Row::Row(Grid& g, int x) : _g(g), _x(x)
{}

int& Row::operator[] (int y) {
	return _g.at(_x, y);
}