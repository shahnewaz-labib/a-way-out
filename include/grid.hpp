#ifndef GRID_HPP
#define GRID_HPP
#include <vector>
#include <stdlib.h>
#include <iostream>
class Grid {
private:
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    // Right , Up , Left , Down

    std::vector<std::vector<int>> g;
public:
    inline bool valid(int x, int y, int N, int M);
    std::vector<std::vector<int>> generate(int N, int M);
    std::vector<std::vector<int>> findGoodGrid(int N, int M);
    Grid(int n, int m);

    class row
    {
        Grid &_a;
        int _i;
        public:
        row(Grid &a,int i) : _a(a),_i(i){}
        int operator[](int j) {return _a.g[_i][j];}
    };
    row operator[](int i)
    {  
        return row(*this,i);
    }

};
#endif

/*
1. has a 2D int grid
2. ctor generates/finds the best grid
*/