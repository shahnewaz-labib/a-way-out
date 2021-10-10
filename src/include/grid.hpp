#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
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
    double tileSize,tileGap;
    double factor = 0.8;
    double lineHeight;
    double lineWidth;
    sf::Vector2f OffSet=sf::Vector2f(0,0);
    void scaleItems(sf::RenderWindow&,int,int);

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
